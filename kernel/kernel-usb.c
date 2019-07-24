/************************************************************************/
/* Quellcode zum Buch                                                   */
/*                     Linux Treiber entwickeln                         */
/* (4. Auflage) erschienen im dpunkt.verlag                             */
/* Copyright (c) 2004-2015 Juergen Quade und Eva-Katharina Kunst        */
/*                                                                      */
/* This program is free software; you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation; either version 2 of the License, or    */
/* (at your option) any later version.                                  */
/*                                                                      */
/* This program is distributed in the hope that it will be useful,      */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         */
/* GNU General Public License for more details.                         */
/*                                                                      */
/************************************************************************/
#include <linux/init.h>
#include <linux/module.h>

#include <linux/ioctl.h>
#include <linux/mutex.h> /* mutexes */
#include <linux/slab.h>  /* kmalloc() */
#include <linux/usb.h>   /* USB stuff */

#include <linux/uaccess.h> /* copy_*_user */

#define USB_VENDOR_ID 0x16c0
#define USB_DEVICE_ID 0x05dc

static wait_queue_head_t wq_write;
// static wait_queue_head_t wq_read;
static atomic_t bytes_that_can_be_written = ATOMIC_INIT(0); /* anpassen */
// static atomic_t bytes_available=ATOMIC_INIT(0);           /* anpassen */
// #define READ_POSSIBLE  (atomic_read(&bytes_available)!=0)
#define WRITE_POSSIBLE (atomic_read(&bytes_that_can_be_written) != 0)

struct usb_device *dev;
static DEFINE_MUTEX(ulock);

static ssize_t usbcheck_read(struct file *instanz, char *buffer, size_t count,
                             loff_t *ofs) {
  char pbuf[20];
  int retval;
  __u8 *status = kmalloc(sizeof(__u16) * count, GFP_KERNEL);

  __u8 *bulk_buf = kmalloc(sizeof(__u8) * 7, GFP_KERNEL);
  if (copy_from_user(bulk_buf, buffer, 7)) {
    return -EFAULT;
  }

  __u16 value = (*(bulk_buf + 2) << 8) + *(bulk_buf + 1);
  __u16 index = (*(bulk_buf + 4) << 8) + *(bulk_buf + 3);

  mutex_lock(&ulock); /* Jetzt nicht disconnecten... */
  retval = usb_control_msg(
      dev, usb_rcvctrlpipe(dev, 0), bulk_buf[0],
      // USB_DIR_IN | USB_TYPE_STANDARD | USB_RECIP_INTERFACE,
      USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_IN, value, index,
      (char *)status, sizeof(status), 5 * HZ);

  if (retval < 0) {
    count = -EIO;
    goto read_out;
  }
  snprintf(pbuf, sizeof(pbuf), "%s\n", (char *)status);
  if (strlen(pbuf) < count)
    count = strlen(pbuf);
  if (retval > count) {
    retval = count;
  }
  memset(buffer, 0, count + 1);
  copy_to_user(buffer, status, retval);
read_out:
  mutex_unlock(&ulock);
  kfree(status);
  return retval;
}

#define MAX_PKT_SIZE 8
#define ML_CTRL_VALUE 0x0
#define ML_CTRL_INDEX 0x0

static ssize_t pen_write(struct file *f, const char __user *buf, size_t cnt,
                         loff_t *off) {
  // char pbuf[20];
  int retval;
  // int wrote_cnt = (cnt - MAX_PKT_SIZE);
  __u8 *bulk_buf = kmalloc(sizeof(__u8) * cnt, GFP_KERNEL);


  if (copy_from_user(bulk_buf, buf, cnt)) {
    return -EFAULT;
  }

  __u8 *raw_data = bulk_buf + 5;
  __u16 value = (*(bulk_buf + 2) << 8) + *(bulk_buf + 1);
  __u16 index = (*(bulk_buf + 4) << 8) + *(bulk_buf + 3);

  printk("Driver get command %d", *buf);
  // printk("Driver data %s", raw_data);

  /* Write the data into the bulk endpoint */
  retval =
      usb_control_msg(dev, usb_sndctrlpipe(dev, 0), bulk_buf[0],
                      USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_OUT, value,
                      index, raw_data, cnt - 5, HZ * 5);
  if (retval < 0) {
    printk(KERN_ERR "usb_control_msg returned %d\n", retval);
    return retval;
  }
  // snprintf(pbuf, sizeof(pbuf), "bulk_buf=%d\n", *bulk_buf);
  // copy_from_user(bulk_buf, buf, 1);
  // printk("Driver Send command %d", *buf);
  return retval;
}

ssize_t usbcheck_write(struct file *instance, const char __user *buffer,
                       size_t max_bytes_to_write, loff_t *offset) {
  size_t to_copy, not_copied;
  char kernelmem[128]; /* Groesse anpassen */

  if (!WRITE_POSSIBLE && (instance->f_flags & O_NONBLOCK)) {
    /* Hardware/Treiber ist nicht bereit, die Daten zu schreiben
     * und der Zugriff erfolgt im Nonblockingmode
     */
    return -EAGAIN;
  }

  if (wait_event_interruptible(wq_write, WRITE_POSSIBLE)) {
    /* waehrend des Schlafens durch ein Signal unterbrochen */
    return -ERESTARTSYS;
  }
  to_copy =
      min((size_t)atomic_read(&bytes_that_can_be_written), max_bytes_to_write);
  not_copied = copy_from_user(kernelmem, buffer, to_copy);
  /* Daten koennen jetzt in die Hardware geschrieben werden
   * ...
   */
  atomic_sub(to_copy - not_copied, &bytes_that_can_be_written);
  *offset += to_copy - not_copied;
  return to_copy - not_copied;
}

static int usbcheck_open(struct inode *devicefile, struct file *instanz) {
  return 0;
}

static struct file_operations usb_fops = {
    .owner = THIS_MODULE,
    .open = usbcheck_open,
    .read = usbcheck_read,
    .write = pen_write,
};

static struct usb_device_id usbid[] = {
    {
        USB_DEVICE(USB_VENDOR_ID, USB_DEVICE_ID),
    },
    {} /* Terminating entry */
};

struct usb_class_driver class_descr = {
    .name = "usbcheck", .fops = &usb_fops, .minor_base = 16,
};

static int usbcheck_probe(struct usb_interface *interface,
                          const struct usb_device_id *id) {
  dev = interface_to_usbdev(interface);
  printk("usbcheck: 0x%4.4x|0x%4.4x, if=%p\n", dev->descriptor.idVendor,
         dev->descriptor.idProduct, interface);
  if (dev->descriptor.idVendor == USB_VENDOR_ID &&
      dev->descriptor.idProduct == USB_DEVICE_ID) {
    if (usb_register_dev(interface, &class_descr)) {
      return -EIO;
    }
    printk("got minor= %d\n", interface->minor);
    return 0;
  }
  return -ENODEV;
}

static void usbcheck_disconnect(struct usb_interface *iface) {
  /* Ausstehende Auftraege muessen abgearbeitet sein... */
  mutex_lock(&ulock);
  usb_deregister_dev(iface, &class_descr);
  mutex_unlock(&ulock);
}

static struct usb_driver usbcheck = {
    .name = "usbcheck",

    .id_table = usbid,
    .probe = usbcheck_probe,
    .disconnect = usbcheck_disconnect,
};

static int __init usbcheck_init(void) {
  if (usb_register(&usbcheck)) {
    printk("usbcheck: unable to register usb driver\n");
    return -EIO;
  }
  return 0;
}

static void __exit usbcheck_exit(void) { usb_deregister(&usbcheck); }

module_init(usbcheck_init);
module_exit(usbcheck_exit);
MODULE_LICENSE("GPL");

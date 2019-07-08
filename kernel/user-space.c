#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_DEVICE "/dev/usbcheck"
#define DEFAULT_DURATION 800

#define ML_STOP 0x00
#define ML_READ_BYTE 0x02
#define ML_WRITE_BYTE 0x03
#define ML_LED 0x30
#define ML_LEDON 0x31
#define ML_FIRE 0x03

#define ML_FIRE_DELAY 5000

typedef struct {
  char cmd;
  uint16_t value;
  char index;
  char data[2];
} usb_msg_t;

void send_cmd(int fd, char *cmd, int count) {
  int retval = 0;

  retval = write(fd, cmd, count);
  if (retval < 0)
    fprintf(stderr, "could not send command to fd=%d\n", fd);
}

static void usage(char *name) {
  fprintf(
      stderr,
      "\nusage: %s [-mbslrudfch] [-t <msecs>]\n\n"
      "  -m      missile launcher [/dev/usbcheck]\n"
      "  -s      stop\n"
      "  -l      turn LED on or off: 0 => Off, 1 => On\n"
      "  -r      turn LED on\n"
      "  -u      read data from avr\n"
      "  -d      write data to avr\n"
      "  -f      fire\n"
      "  -b      blink leds\n"
      "  -t      specify send_cmdment duration in milli seconds\n"
      "  -c      calibrate the missile launcher axes\n"
      "  -h      display this help\n\n"
      "notes:\n"
      "* it is possible to combine the directions of the two axes, e.g.\n"
      "  '-lu' send_cmds the missile launcher up and left at the same time.\n"
      "",
      name);
  exit(1);
}

int main(int argc, char *argv[]) {
  char c;
  int fd;
  char *cmd = malloc(sizeof(usb_msg_t));
  int cvalue;
  char buffer[20];
  int duration = DEFAULT_DURATION;
  char *dev = DEFAULT_DEVICE;
  char *data;
  usb_msg_t usb_msg = {ML_WRITE_BYTE, 0x33, 0x34, ""};

  opterr = 0;
  if (argc < 2)
    usage(argv[0]);

  while ((c = getopt(argc, argv, "m:bsl:ru:d:fcht:")) != -1) {
    switch (c) {
    case 'm':
      dev = optarg;
      break;
    case 'l':
      cvalue = atoi(optarg);

      cmd[0] = ML_LED;
      if (cvalue == 0)
        cmd[1] = 0;
      else
        cmd[1] = 1;
      break;
    case 'r':
      cmd[0] = ML_LEDON;
      break;
    case 'u':
      usb_msg.cmd = ML_READ_BYTE;
      usb_msg.value = 0x33;
      usb_msg.index = 0x34;
      usb_msg.data[0] = 0;
      memcpy(buffer, (const char *)&usb_msg, sizeof(usb_msg_t));
      cvalue = atoi(optarg);
      printf("Open device %s\n", dev);
      fd = open(dev, O_RDWR);
      if (fd == -1) {
        perror("open");
        exit(1);
      }

      printf("Send command %i\n", cmd[0]);
      int retval = 0;

      retval = read(fd, buffer, cvalue);
      if (retval < 0)
        fprintf(stderr, "could not send command to fd=%d\n", fd);
      close(fd);
      // if (retval != 16)
      fprintf(stderr, "number of bytes read = %d\n", retval);
      printf("receive: %s\n", buffer);

      close(fd);

      return EXIT_SUCCESS;
      break;
    case 'd':
      usb_msg.cmd = ML_WRITE_BYTE;
      usb_msg.value = 0x3233;
      usb_msg.index = 0x0034;
      strncpy(usb_msg.data, optarg, 2);
      memcpy(cmd, (const char *)&usb_msg, sizeof(usb_msg_t));
      // cvalue = atoi(optarg);

      printf("Open device %s\n", dev);
      fd = open(dev, O_RDWR);
      if (fd == -1) {
        perror("open");
        exit(1);
      }

      printf("Send command %i\n", cmd[0]);
      send_cmd(fd, cmd, 2 + 4 + 1);
      close(fd);
      // // if (retval != 16)
      // fprintf(stderr, "number of bytes read = %d\n", retval);
      // printf("receive: %s\n", buffer);

      // close(fd);
      return EXIT_SUCCESS;

      // // cmd = "optarg";
      // strcpy(cmd, optarg);
      // cmd[0] = ML_WRITE_BYTE;
      break;
    case 'f':
      cmd[0] = ML_FIRE;
      break;
    case 'b':
      cmd[0] = ML_LED;
      break;
    case 's':
      cmd[0] = ML_STOP;
      break;
    case 't':
      duration = atoi(optarg);
      break;
    case 'c': /*
                      retval = ioctl(fd, ML_IOCTCALIBRATE, ML_CALIBRATE_FULL);
                      if (retval < 0)
                              perror("ioctl");
                      */
      break;
    case '?':
      if (optopt == 'u')
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      else if (optopt == 'l')
        fprintf(stderr, "Option -%c requires an argument: On = 1, Off = 0.\n",
                optopt);
      else if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
    default:
      usage(argv[0]);
    }
  }

  printf("Open device %s\n", dev);
  fd = open(dev, O_RDWR);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  printf("Send command %i\n", cmd[0]);
  send_cmd(fd, cmd, 3);

  // if (cmd & ML_FIRE)
  //  duration = ML_FIRE_DELAY;
  // else if (cmd == ML_READ_BYTE || cmd == ML_WRITE_BYTE)
  //  duration /= 2;
  // usleep(duration * 1000);

  // send_cmd(fd, ML_STOP);

  close(fd);

  return EXIT_SUCCESS;
}

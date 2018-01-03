/**
 * Project: AVR ATtiny USB Tutorial at http://codeandlife.com/
 * Author: Joonas Pihlajamaa, joonas.pihlajamaa@iki.fi
 * Inspired by V-USB example code by Christian Starkjohann
 * Copyright: (C) 2012 by Joonas Pihlajamaa
 * License: GNU GPL v3 (see License.txt)
 */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>

#include "usbdrv.h"

#define F_CPU 12000000L
#include <util/delay.h>

#define USB_LED_OFF 0x30
#define USB_LED_ON 0x31
#define USB_DATA_OUT 2
#define USB_DATA_WRITE 3
#define USB_DATA_IN 0x34

static uchar replyBuf[20] = "Hello, USB!";
static uchar dataReceived = 0, dataLength = 0; // for USB_DATA_IN

// this gets called when custom control message is received
USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
  usbRequest_t *rq = (void *)data; // cast data to correct type

  switch (rq->bRequest)
  { // custom command is in the bRequest field
  case USB_LED_ON:
    PORTD |= (1 << PD5); // turn LED on
    return 0;
  case USB_LED_OFF:
    PORTD &= ~(1 << PD5); // turn LED off
    return 0;
  case USB_DATA_OUT: // send data to PC
    usbMsgPtr = &(replyBuf[rq->wIndex.bytes[0]]);
    return sizeof(replyBuf) - rq->wIndex.bytes[0];
  case USB_DATA_WRITE: // modify reply buffer
    replyBuf[4] = rq->wValue.bytes[0];
    replyBuf[5] = rq->wValue.bytes[1];
    replyBuf[6] = rq->wIndex.bytes[0];
    replyBuf[7] = rq->wIndex.bytes[1];
    return 0;
  case USB_DATA_IN: // receive data from PC
    dataLength = (uchar)rq->wLength.word;
    dataReceived = 0;

    if (dataLength > sizeof(replyBuf)) // limit to buffer size
      dataLength = sizeof(replyBuf);

    PORTD ^= (1 << PD5); // turn LED on
    return USB_NO_MSG;   // usbFunctionWrite will be called now

  default:
    PORTD ^= (1 << PD5); // turn LED on
  }

  return 0; // should not get here
}

// This gets called when data is sent from PC to the device
USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len)
{
  uchar i;

  for (i = 0; dataReceived < dataLength && i < len; i++, dataReceived++)
    replyBuf[dataReceived] = data[i];

  return (dataReceived == dataLength); // 1 if we received it all, 0 if not
}

int main()
{
  uchar i;

  DDRD = (1 << PD5);   // PD5 as output
  PORTD |= (1 << PD5); // turn LED on

  wdt_enable(WDTO_1S); // enable 1s watchdog timer

  usbInit();

  usbDeviceDisconnect(); // enforce re-enumeration
  for (i = 0; i < 250; i++)
  {              // wait 500 ms
    wdt_reset(); // keep the watchdog happy
    _delay_ms(2);
  }
  usbDeviceConnect();

  sei(); // Enable interrupts after re-enumeration

  while (1)
  {
    wdt_reset(); // keep the watchdog happy
    usbPoll();
  }

  return 0;
}
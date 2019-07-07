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

#ifndef F_CPU
#define F_CPU 12000000L
#endif

#include <util/delay.h>

#define USB_LED 0x30
#define USB_LED_ON 0x31
#define USB_DATA_READ 2
#define USB_DATA_WRITE 3

#define MESSAGE_LENGTH 8
#define RCLK PD4
#define DATA PD6
#define SRCLK PD5

uchar replyBuf[20] = "Hello,USB!";
int len;

/* The following variables store the status of the current data transfer */
volatile uchar currentAddress;
volatile uchar bytesRemaining;

// this gets called when custom control message is received
USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
  usbRequest_t *rq = (void *)data; // cast data to correct type

  switch (rq->bRequest)
  { // custom command is in the bRequest field
  case USB_LED_ON:
    PORTD |= (1 << PD5); // turn LED on
    return 0;
  case USB_LED:
    if (rq->wValue.bytes[0])
      PORTD |= (1 << PD5); // turn LED on
    else
      PORTD &= ~(1 << PD5); // turn LED off
    return 0;
  case USB_DATA_READ:           // send data to PC
    DDRB = 0x00;
    PORTB = 0xff;
    len = 20;                   // we return up to 64 bytes
    if (len > rq->wLength.word) // if the host requests less than we have
      len = rq->wLength.word;   // return only the amount requested
    usbMsgPtr = replyBuf;       // tell driver where the buffer starts
    return len;                 // tell driver how many bytes to send
  case USB_DATA_WRITE:          // receive data from PC
    bytesRemaining = (uchar)rq->wLength.word;
    if (bytesRemaining > 20)
      bytesRemaining = 20;
    currentAddress = 0;
    PORTD ^= (1 << PD5); // turn LED on
    return USB_NO_MSG;

  default:
    PORTD ^= (1 << PD5); // turn LED on
  }

  return 0; // should not get here
}

/* usbFunctionWrite() is called when the host sends a chunk of data to the
 * device. For more information see the documentation in usbdrv/usbdrv.h.
 */
USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len)
{
  if (bytesRemaining == 0)
    return 1; /* end of transfer */
  if (len > bytesRemaining)
    len = bytesRemaining;
  for (int i = 0; i < len; ++i)
  {
    replyBuf[currentAddress + i] = data[i];
  }
  currentAddress += len;
  bytesRemaining -= len;
  return bytesRemaining == 0; /* return 1 if this was the last chunk */
}

void vfd_write_byte(uint8_t byte)
{
    int i = MESSAGE_LENGTH;
    do
    {
        if (byte & 0x01)
            PORTD |= (1 << DATA);
        else
            PORTD &= ~(1 << DATA);

        PORTD &= ~(1 << SRCLK);
        byte = byte >> 1;
        i--;

        PORTD |= (1 << SRCLK);
    } while (i > 0);
}

int main()
{
  uchar i;

  DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6);
  PORTD |= (1 << PD4) | (1 << PD5) | (1 << PD6);

  wdt_enable(WDTO_1S); // enable 1s watchdog timer

  usbInit();

  usbDeviceDisconnect(); // enforce re-enumeration
  for (i = 0; i < 250; i++)
  {              // wait 500 ms
    wdt_reset(); // keep the watchdog happy
    _delay_ms(2);
  }
  usbDeviceConnect();

  sei();               // Enable interrupts after re-enumeration
  PORTD |= (1 << PD5); // turn LED on

  while (1)
  {
    wdt_reset(); // keep the watchdog happy
    usbPoll();
  }
  return 0;
}
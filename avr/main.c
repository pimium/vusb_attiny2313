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
#define USB_DATA_READ_DEVICE_CODE 4

#define MESSAGE_LENGTH 8
#define RCLK PD4
#define DATA PD1
#define SRCLK PD0

#define RAM_WE 0x80
#define RAM_OE 0x40
#define RAM_A9 0x20
#define RAM_CE PD5

void vfd_write_byte(uint8_t byte);

uchar replyBuf[20] = "Hello,USB!";
int len;
uint8_t address[2];

/* The following variables store the status of the current data transfer */
volatile uchar bytesRemaining;

// this gets called when custom control message is received
USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
    usbRequest_t *rq = (void *)data; // cast data to correct type
    uint8_t choice = RAM_A9;

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

    case USB_DATA_READ_DEVICE_CODE: // send data to PC
        choice = 0;
    case USB_DATA_READ: // send data to PC

        PORTD |= (1 << RAM_CE);
        DDRB = 0x00;
        PORTB = 0xFF;

        PORTD &= ~(1 << SRCLK);
        PORTD |= (1 << RCLK);
        PORTD &= ~(1 << RCLK);
        vfd_write_byte(RAM_OE | RAM_WE | choice);
        vfd_write_byte(rq->wValue.bytes[1]);
        vfd_write_byte(rq->wValue.bytes[0]);
        PORTD |= (1 << RCLK);

        PORTD &= ~(1 << SRCLK);
        PORTD |= (1 << RCLK);
        PORTD &= ~(1 << RCLK);
        vfd_write_byte(RAM_WE | choice);
        vfd_write_byte(rq->wValue.bytes[1]);
        vfd_write_byte(rq->wValue.bytes[0]);
        PORTD &= ~(1 << RAM_CE);
        PORTD |= (1 << RCLK);

        PORTD &= ~(1 << SRCLK);
        PORTD |= (1 << RCLK);
        PORTD &= ~(1 << RCLK);

        replyBuf[0] = PINB;

        vfd_write_byte(RAM_OE | RAM_WE | choice);
        vfd_write_byte(rq->wValue.bytes[1]);
        vfd_write_byte(rq->wValue.bytes[0]);
        PORTD |= (1 << RCLK);
        PORTD |= (1 << RAM_CE);
        usbMsgPtr = replyBuf;
        return 1;

    case USB_DATA_WRITE: // receive data from PC
        bytesRemaining = (uchar)rq->wLength.word;
        address[1] = rq->wValue.bytes[1];
        address[0] = rq->wValue.bytes[0];

        return USB_NO_MSG;

    default:
        return 0;
    }

    return 0; // should not get here
}

/* usbFunctionWrite() is called when the host sends a chunk of data to the
 * device. For more information see the documentation in usbdrv/usbdrv.h.
 */
USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len)
{
    PORTD |= (1 << RAM_CE);
    DDRB = 0xFF;
    PORTB = data[0];

    PORTD &= ~(1 << SRCLK);
    PORTD |= (1 << RCLK);
    PORTD &= ~(1 << RCLK);
    vfd_write_byte(RAM_OE | RAM_A9);
    vfd_write_byte(address[1]);
    vfd_write_byte(address[0]);
    PORTD |= (1 << RCLK);

    PORTD &= ~(1 << SRCLK);
    PORTD |= (1 << RCLK);
    PORTD &= ~(1 << RCLK);
    vfd_write_byte(RAM_OE | RAM_WE | RAM_A9);
    vfd_write_byte(address[1]);
    vfd_write_byte(address[0]);

    PORTD &= ~(1 << RAM_CE);

    PORTD |= (1 << RCLK);

    PORTD &= ~(1 << SRCLK);
    PORTD |= (1 << RCLK);
    PORTD &= ~(1 << RCLK);
    vfd_write_byte(RAM_OE | RAM_A9);
    vfd_write_byte(address[1]);
    vfd_write_byte(address[0]);
    PORTD |= (1 << RCLK);

    PORTD |= (1 << RAM_CE);

    return 1; /* return 1 if this was the last chunk */
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
    PORTD &= ~(1 << SRCLK);
    wdt_reset();
}

int main()
{
    uchar i;

    DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD0) | (1 << PD1);
    PORTD |= (1 << PD4) | (1 << PD5) | (1 << PD0) | (1 << PD1);

    wdt_enable(WDTO_1S); // enable 1s watchdog timer

    usbInit();

    usbDeviceDisconnect(); // enforce re-enumeration
    for (i = 0; i < 250; i++)
    {                // wait 500 ms
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
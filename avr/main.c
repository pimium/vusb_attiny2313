
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>

#include "usbdrv.h"

#define F_CPU 12000000L
#include <util/delay.h>

USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
  return 0; // do nothing for now
}

int main()
{
  uchar i;

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
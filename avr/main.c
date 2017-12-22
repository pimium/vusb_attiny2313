#include <avr/io.h>

#define F_CPU 1000000UL  // 1 MHz

#define USB_CFG_IOPORTNAME      D
#define USB_CFG_DMINUS_BIT      3
#define USB_CFG_DPLUS_BIT       2
#define USB_CFG_CLOCK_KHZ       12000

#define USB_CFG_IS_SELF_POWERED         0
#define USB_CFG_MAX_BUS_POWER           50

#define  USB_CFG_VENDOR_ID       0xc0, 0x16 /* = 0x16c0 */
#define  USB_CFG_DEVICE_ID       0xdc, 0x05 /* = 0x05dc */

#define USB_CFG_DEVICE_VERSION  0x00, 0x01

#define USB_CFG_VENDOR_NAME     'c', 'o', 'd', 'e', 'a', 'n', 'd', 'l', 'i', 'f', 'e', '.', 'c', 'o', 'm'
#define USB_CFG_VENDOR_NAME_LEN 15

#define USB_CFG_DEVICE_NAME     'U', 'S', 'B', 'e', 'x', 'a', 'm', 'p', 'l', 'e'
#define USB_CFG_DEVICE_NAME_LEN 10

#include <util/delay.h>

int main() {
        DDRB |= 1; // LED on PB0
        
        while(1) {
                PORTB |= 1; // Turn LED on
                _delay_ms(500);
                PORTB &= ~1; // Turn LED off
                _delay_ms(500);
        }

        return 1;
}
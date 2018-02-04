##########################################################################
# "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware
# license):
# <dev@layer128.net> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and
# you think this stuff is worth it, you can buy me a be(ve)er(age) in
# return. (I don't like beer much.)
#
# Matthias Kleemann
##########################################################################
#include_directories(../../)
add_avr_library(
        v-usblib
        usbdrvasm.S
        usbdrv.c
        usbdrv.h
        oddebug.c
        oddebug.h
        usbportability.h
)
#
#add_avr_executable(
#        ${PROJECT_NAME}
#        usbdrvasm.S
#        main.c
#        usbdrv.c
#        usbdrv.h
#        oddebug.c
#        oddebug.h
#        usbportability.h
#        usbconfig.h
#)

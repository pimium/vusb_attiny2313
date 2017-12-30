# Makefile
# zum Beispielcode aus dem Buch
# Linux-Treiber entwickeln - Eine systematsiche Einfuehrung
# in die Geraetetreiber- und Kernelprogrammierung.
# 
# 4. Auflage, erschienen im dpunkt-Verlag, 2015
#
# Um saemtlichen Beispielcode zu generieren muessen
# Sie nur "make" eintippen. Je nach eingesetzter
# Kernelversion laesst sich unter Umstaenden nicht
# jedes Modul fehlerfrei compilieren. Loeschen Sie das
# problematische File zunaechst aus der Liste und
# rufen Sie dann "make" erneut auf.
#
# Einige der Quellcodedateien sind nur auf dem Raspberry Pi
# lauffaehig.
#
# So 18. Okt 11:16:30 CEST 2015
#
# GPL
# (c) 2015, J. Quade, E. Kunst

ifneq ($(KERNELRELEASE),)
obj-m	:= \
	kernel-usb.o

else
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

default:
	$(MAKE)	-C $(KDIR)	M=$(PWD) modules
endif

clean:
	rm -f *~ *.o *.ko *.dwo .*.dwo
	rm -f .built_in.o.cmd built_in.o
	rm -f .*.cmd *.ko *.mod.c
	rm -rf .tmp_versions modules.order Module.symvers

# Uncomment the following to enable debug.
DEBUG = y

ifeq ($(DEBUG),y)
	DBGFLAGS = -O -g -DML_DEBUG
else
	DBGFLAGS = -O2
endif

ccflags-y += $(DBGFLAGS)


ifneq ($(KERNELRELEASE),)
	obj-m := kernel-usb.o

else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm *.symvers
	
endif

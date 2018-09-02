ifneq ($(KERNELRELEASE),) # kbuild part of makefile
CFLAGS_rtc_ds1307_custom.o := -DDEBUG
obj-m := rtc_ds1307_custom.o
else # normal makefile
KDIR ?= ~/repos/linux

default: module
module:
	$(MAKE) -C $(KDIR) M=$(PWD)  modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) C=1 clean

CC = $(CROSS_COMPILE)gcc
CFLAGS = -O2 -Wall

.PHONY: module clean app
endif

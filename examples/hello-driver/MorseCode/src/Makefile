# University of Fribourg
# Operating Systems - Bachelor Course 2007-2008
#
# Makefile for kernel module mymodule.c
# Important: Please ensure that there are no directories with spaces within 
# the names in the path, or compilation will fail.
#
# To build the module just type 'make'
# To load the module type (as root) 'insmod mymodule.ko'
# To unload the module type (as root) 'rmmod mymodule.ko'

KERNEL_VERSION=$(shell uname -r)
KERNEL_SOURCE=/lib/modules/$(KERNEL_VERSION)/build

obj-m += keymorse.o

modules:
	$(MAKE) -C $(KERNEL_SOURCE) modules SUBDIRS=$(CURDIR)

clean:
	rm -f .*.cmd *.o *.ko *.mod.c *.symvers
	
load: keymorse.ko
	insmod keymorse.ko	
        
unload:
	rmmod keymorse.ko        

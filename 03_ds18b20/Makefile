KERDIR = /home/alientek/rk3568_linux_sdk/kernel
PWD = $(shell pwd)
obj-m = dp1802.o


all:
	$(MAKE) -C $(KERDIR) M=$(PWD)  modules
clean:
	rm -rf *.order *.ko *.o *.mod.c *.sy*

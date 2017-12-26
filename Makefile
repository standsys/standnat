obj-m += standnat.o
standnat-objs := main.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	cp standnat.ko  /lib/modules/$(shell uname -r)/extra
	depmod

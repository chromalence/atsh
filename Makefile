CC = gcc
CFLAGS = -Os -nostdlib -static -fno-asynchronous-unwind-tables -fno-stack-protector
LDFLAGS = -Wl,--build-id=none -Wl,-nmagic -s

shot: main.c sys.S
	$(CC) $(CFLAGS) main.c syscalls.s $(LDFLAGS) -o atsh

clean:
	rm -f atsh

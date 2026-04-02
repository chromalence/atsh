CC = gcc
CFLAGS = -Os -nostdlib -static -fno-asynchronous-unwind-tables -fno-stack-protector
LDFLAGS = -Wl,--build-id=none -Wl,-nmagic -s

atsh: main.c calls.S
	$(CC) $(CFLAGS) main.c calls.S $(LDFLAGS) -o atsh

clean:
	rm -f atsh

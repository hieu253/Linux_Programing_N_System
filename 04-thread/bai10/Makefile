.PHONY: all clean

CFLAGS := -pthread
all:
	gcc -o exam1 singlethread.c $(CFLAGS)
	gcc -o exam2 multithread.c $(CFLAGS)

clean:
	rm -rf exam1
	rm -rf exam2
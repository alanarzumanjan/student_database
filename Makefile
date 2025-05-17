TARGET=main

obj_file=$(TARGET).o
compile=$(TARGET).c

CC=gcc
CFLAGS=-lm

compile:
	$(CC) $(compile) -o $(obj_file)
	./$(obj_file)

.PHONY: clean all

clean:
	rm -f *.o

program_name=main
obj_file=$(program_name).o
program=$(program_name).c
CC=gcc
CFLAGS=-lm

program:
	$(CC) $(program) -o $(obj_file)
	./$(obj_file)

add:
	git add .
	git add Makefile
	git commit -a -m "mama"
	git push

.PHONY: clean all

clean:
	rm -f *.o
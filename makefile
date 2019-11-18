ifeq ($(path),)
	runCommand = ./dirinfo
else
	runCommand = ./dirinfo $(path)
endif

all: main.o
	gcc -o dirinfo main.o

main.o: main.c
	gcc -c main.c

run:
	$(runCommand)

clean:
	rm *.o
	rm dirinfo

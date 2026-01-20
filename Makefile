CC = gcc
CFLAGS = -Wall -Wextra -g

all: spim

spim: project.o spimcore.o
	$(CC) $(CFLAGS) -o spim project.o spimcore.o

project.o: project.c spimcore.h
	$(CC) $(CFLAGS) -c project.c

spimcore.o: spimcore.c spimcore.h
	$(CC) $(CFLAGS) -c spimcore.c

clean:
	rm -f *.o spim

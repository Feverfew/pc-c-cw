CFLAGS = -Wextra -Wall
CC = gcc

all: main.o graphing.o arduino-serial-lib.o
	$(CC) $(CFLAGS) $? -o program -lm

clean: 
	rm *.o ./program

main.o: main.c graphing.h arduino-serial-lib.h
	$(CC) $(CFLAGS) -c main.c 

graphing.o: 
	$(CC) $(CFLAGS) -c graphing.c

arduino-serial-lib.o: 
	$(CC) $(CFLAGS) -c arduino-serial-lib.c

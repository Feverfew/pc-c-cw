CFLAGS = -Wextra -Wall -g
CC = gcc
EXEC = program

all: main.o graphing.o arduino-serial-lib.o
	$(CC) $(CFLAGS) $? -o $(EXEC) -lm

clean: 
	rm *.o ./$(EXEC) data.dat liveplot.gnu

main.o: main.c graphing.h
	$(CC) $(CFLAGS) -c main.c 

graphing.o: graphing.c arduino-serial-lib.h
	$(CC) $(CFLAGS) -c graphing.c

arduino-serial-lib.o: arduino-serial-lib.c
	$(CC) $(CFLAGS) -c arduino-serial-lib.c

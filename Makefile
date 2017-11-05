#C3980 Assignment 3 Makefile

CC=gcc -Wall -std=c11 -pthread
CLIB=-lgps

dcgps: dcgps.o gps-utils.o gpsprint.o
		$(CC) -o dcgps dcgps.o gps-utils.o gpsprint.o $(CLIB)

clean:
		rm -f *.o core.* dcgps

dcgps.o:
		$(CC) -c dcgps.c

gps-utils.o:
		$(CC) -c gps-utils.c

gpsprint.o:
		$(CC) -c gpsprint.c

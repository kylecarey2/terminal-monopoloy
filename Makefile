# Created by: Kyle Carey
# Variables
CC = g++
CFLAGS = -g -Wall -std=c++11

a.out: die.o die.h property.o property.h player.o player.h board.o board.h monopoly.o
	$(CC) $(CFLAGS) EXECS/die.o EXECS/property.o EXECS/player.o EXECS/board.o EXECS/monopoly.o -o playedOut.out

die.o: die.cc die.h
	$(CC) -c $(CFLAGS) die.cc -o EXECS/die.o

monopoly.o: monopoly.cc die.h
	$(CC) -c $(CFLAGS) monopoly.cc -o EXECS/monopoly.o

property.o: property.cc property.h
	$(CC) -c $(CFLAGS) property.cc -o EXECS/property.o

player.o: player.cc player.h
	$(CC) -c $(CFLAGS) player.cc -o EXECS/player.o

board.o: board.cc board.h
	$(CC) -c $(CFLAGS) board.cc -o EXECS/board.o

clean:
	rm EXECS/*.o 

play:
	./a.out
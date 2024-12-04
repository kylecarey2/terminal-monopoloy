# Variables
CC = g++
CFLAGS = -g -Wall -std=c++11

a.out: die.o die.h monopoly.o
	$(CC) $(CFLAGS) EXECS/die.o EXECS/monopoly.o -o a.out

die.o: die.cc die.h
	$(CC) -c $(CFLAGS) die.cc -o EXECS/die.o

monopoly.o: monopoly.cc die.h
	$(CC) -c $(CFLAGS) monopoly.cc -o EXECS/monopoly.o

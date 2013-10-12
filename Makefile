#Makefile

CC = g++

CFLAGS = -O3 -Wall
#CFLAGS = -g -Wall

all:calc

calc: SearchDesign.cpp HPModel2D.cpp Algorithm.cpp DataStructure.cpp
	$(CC) $(CFLAGS) -o calc SearchDesign.cpp HPModel2D.cpp Algorithm.cpp DataStructure.cpp

clean:
	$(RM) calc

# Makefile for the List Manipulator assignment

OBJS = term_control.o Lexer.o error_handling.o vecmanip.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic -ansi $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o cstore

main.o: main.cpp Lexer.h error_handling.h vecmanip.h term_control.h
	$(CC) -c $(CFLAGS) main.cpp

# vecmanip makes use of error handling routines
vecmanip.o: error_handling.o  vecmanip.h vecmanip.cpp
	$(CC) -c $(CFLAGS) vecmanip.cpp

# error handling routines make use of terminal control routines
error_handling.o : term_control.o error_handling.h error_handling.cpp
	$(CC) -c $(CFLAGS) error_handling.cpp

# the Lexer is fairly independent
Lexer.o : Lexer.h Lexer.cpp
	$(CC) -c $(CFLAGS) Lexer.cpp

# this object file is at the "lowest level"
term_control.o : term_control.h term_control.cpp
	$(CC) -c $(CFLAGS) term_control.cpp

clean:
	rm -f *.o a.out main vecmanip

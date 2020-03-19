PROGRAM = Elimination
CC      = gcc
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include -std=c99
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o draw.o 
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(PROGRAM)  main.o draw.o $(LDLIBS)

draw.o: draw.c function.h
	$(CC) $(LDFLAGS) $(CFLAGS) -c draw.c -o draw.o

main.o: main.c
	$(CC) $(LDFLAGS) $(CFLAGS) -c main.c -o main.o

.PHONY: clean 

clean:
	-rm *.o $(PROGRAM) 

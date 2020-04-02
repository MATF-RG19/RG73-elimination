PROGRAM = Elimination
CC      = gcc
CFLAGS  = -g -ansi -Wall -I/usr/X11R6/include -I/usr/pkg/include -std=c99
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o draw.o image.o textures.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(PROGRAM)  main.o draw.o image.o textures.o $(LDLIBS)

image.o: image.c image.h
	$(CC) $(LDFLAGS) $(CFLAGS) -c image.c -o image.o

textures.o: textures.c image.h functions.h
	$(CC) $(LDFLAGS) $(CFLAGS) -c textures.c -o textures.o

draw.o: draw.c functions.h
	$(CC) $(LDFLAGS) $(CFLAGS) -c draw.c -o draw.o

main.o: main.c functions.h image.h
	$(CC) $(LDFLAGS) $(CFLAGS) -c main.c -o main.o

.PHONY: clean 

clean:
	-rm *.o $(PROGRAM) 

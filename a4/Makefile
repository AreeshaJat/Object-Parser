CC = gcc

CFLAGS =  $(shell python2-config --cflags) -fPIC
LDFLAGS = $(shell python2-config --ldflags)

default: a1

a1: a1.o wavefront.o ppm.o
	$(CC) -w a1.o wavefront.o ppm.o -o a1 $(LDFLAGS)
	
a1.o: a1.c wavefront.h ppm.h
	$(CC) -w -c a1.c $(CFLAGS)
	
wavefront.o: wavefront.c wavefront.h
	$(CC) -w -c wavefront.c $(CFLAGS)
	
ppm.o: ppm.c ppm.h
	$(CC) -w -c ppm.c $(CFLAGS)

clean:
	rm -f a1 *.o

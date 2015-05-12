C=cc
#CC=c++
CC=g++

CFLAGS= -g -c -I../include
VPATH=./main

OBJ = main.o lstruan.o


all :  test

test : $(OBJ)
	$(C) -o $@ $(OBJ) 
	#$(CC) -o $@ $(OBJ) 
	mv test ../bin
	rm -f *.o


%.o : %.c
	$(C) $(CFLAGS) $<

%.o : %.cpp
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o *.so *.a

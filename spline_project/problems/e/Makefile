CC = g++

CFLAGS = -Wall -g

OBJ = problem_e.o ../../xtspline.o ../../xtlapack.o ../../xtreader.o

EXEC = problem_e

all: $(EXEC)

$(EXEC): problem_e.o
	$(CC) $(OBJ) -o $(EXEC)

problem_e.o: problem_e.cpp ../../xtspline.h
	$(CC) $(CFLAGS) -c problem_e.cpp

clean:
	rm -f $(OBJ) $(EXEC)

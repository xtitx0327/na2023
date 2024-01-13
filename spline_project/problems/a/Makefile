CC = g++

CFLAGS = -Wall -g

OBJ = problem_a.o ../../xtspline.o ../../xtlapack.o ../../xtreader.o

EXEC = problem_a

all: $(EXEC)

$(EXEC): problem_a.o
	$(CC) $(OBJ) -o $(EXEC)

problem_a.o: problem_a.cpp ../../xtspline.h
	$(CC) $(CFLAGS) -c problem_a.cpp

clean:
	rm -f $(OBJ) $(EXEC)

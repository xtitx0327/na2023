CC = g++

CFLAGS = -Wall -g

OBJ = problem_d.o ../../xtspline.o ../../xtlapack.o ../../xtreader.o

EXEC = problem_d

all: $(EXEC)

$(EXEC): problem_d.o
	$(CC) $(OBJ) -o $(EXEC)

problem_d.o: problem_d.cpp ../../xtspline.h
	$(CC) $(CFLAGS) -c problem_d.cpp

clean:
	rm -f $(OBJ) $(EXEC)

CC = g++
SOURCE = examples/test.cpp
CFLAG = -m32 -Wall -Wextra
OBJ = target/test


example:
	$(CC) $(SOURCE) -o $(OBJ) $(CFLAG)
	./$(OBJ)

clean:
	rm -rf target/*

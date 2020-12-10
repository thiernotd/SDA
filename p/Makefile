CC= gcc
CXXFLAGS= -Wall --pedantic -O3

CPP_O_FILE = arbreCouvrantMin.o citiesReader.o main.o
LIB = -lm

all: $(CPP_O_FILE)
	$(CC) $(CXXFLAGS) -o main.exe arbreCouvrantMin.c citiesReader.o main.o $(LIB)
clean:
	rm -rf *.o *.exe
	rm -rf *~

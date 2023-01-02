#Instructions de compilation de la librairie ProjetLO21
CXX = gcc
CFLAGS = -Wall -Werror -fpic -pedantic -shared

SOURCE = individu.o population.o
TARGET = libProjetLO21.so

CLEANCMD = rm -rf *.o *.so

$(TARGET): $(SOURCE) 
	$(CXX) $(CFLAGS) $(SOURCE) -o $(TARGET)

clean:
	$(CLEANCMD)
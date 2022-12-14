CXX = gcc
CFLAGS = -Wall -Werror -fpic -pedantic -shared

SOURCE = individu.o population.o
TARGET = ProjetLO21

CLEANCMD = rm -rf *.o *.so

$(TARGET): $(SOURCE) 
	$(CXX) $(CFLAGS) $(SOURCE) -o lib$(TARGET).so

clean:
	$(CLEANCMD)
main: population.o individu.o main.o
	gcc -o main population.o individu.o main.o -lm

population.o: population.c
	gcc -o population.o -c population.c -Wall -pedantic -lm

individu.o: individu.c
	gcc -o individu.o -c individu.c -Wall -pedantic -lm

main.o: main.c population.h individu.h
	gcc -o main.o -c main.c -Wall -pedantic -lm

clean:
	rm -rf *.o main

run:
	./main
#Instructions de compilation du programme de test de la librairie ProjetLO21
CXX = gcc
CFLAGS = -Wall -Werror -pedantic

EXESOURCE = main.c cli.c
EXECUTABLE = main
LIBNAME = ProjetLO21
LIBDIR = ./libs/ProjetLO21/

EXPORTCMD = LD_LIBRARY_PATH=$(LIBDIR)
CLEANCMD = rm -rf main

$(EXECUTABLE): $(LIBDIR) $(EXESOURCE)
	cd $(LIBDIR) && make
	$(CXX) $(EXESOURCE) -I$(LIBDIR) -L$(LIBDIR) -l$(LIBNAME) -lm -o $(EXECUTABLE)

run: $(EXECUTABLE)
	$(EXPORTCMD) ./$(EXECUTABLE)

check: $(EXECUTABLE)
	$(EXPORTCMD) valgrind ./$(EXECUTABLE)

clean: $(LIBDIR)
	$(CLEANCMD) && cd $(LIBDIR) && make clean
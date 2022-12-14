CXX = gcc
CFLAGS = -Wall -Werror -pedantic

EXESOURCE = main.c cli.c
EXECUTABLE = main
LIBNAME = ProjetLO21
LIBDIR = lib

EXPORTCMD = LD_LIBRARY_PATH=$(LIBDIR)
CLEANCMD = rm -rf main

$(EXECUTABLE): $(LIBDIR)
	cd $(LIBDIR) && make
	$(CXX) $(EXESOURCE) -I$(LIBDIR) -L$(LIBDIR) -l$(LIBNAME) -lm -o $(EXECUTABLE) 

run: $(EXECUTABLE)
	$(EXPORTCMD) ./$(EXECUTABLE)

check: $(EXECUTABLE)
	$(EXPORTCMD) valgrind ./$(EXECUTABLE)

clean:
	$(CLEANCMD) && cd $(LIBDIR) && make clean
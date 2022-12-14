CXX = gcc
CFLAGS = -Wall -Werror -fpic -pedantic

LIBSOURCE = individu.o population.o affichage.o
EXECUTABLE = main
LIBNAME = ProjetLO21
LIBTARGET := lib$(LIBNAME:=.so)

EXPORTCMD = LD_LIBRARY_PATH=.
CLEANCMD = rm -rf *.o *.so main

$(EXECUTABLE): $(EXECUTABLE).o $(LIBTARGET) 
	$(CXX) $(EXECUTABLE).o -l$(LIBNAME) -lm -L. -o $(EXECUTABLE) 

$(LIBTARGET): $(LIBSOURCE) 
	$(CXX) $(CFLAGS) -shared $(LIBSOURCE) -o $(LIBTARGET)

.c.o:
	$(CXX) $(CFLAGS) -c -o $@ $<

run: $(EXECUTABLE)
	$(EXPORTCMD) ./$(EXECUTABLE)

check: $(EXECUTABLE)
	$(EXPORTCMD) valgrind  ./$(EXECUTABLE)

clean:
	$(CLEANCMD)
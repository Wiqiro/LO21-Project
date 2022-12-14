CXX = gcc
CFLAGS = -Wall -Werror -fpic -pedantic 
LIBSDIR = -L. -L/usr/lib
INCLUDEDIR = -I. -I/usr/include

LIBNAME = projetlo21
LIBTARGET :=lib$(LIBNAME:=.so)

EXPORTCMD = LD_LIBRARY_PATH=.
CLEANCMD = rm -rf *.o *.so main

LIBSOURCE = individu.o population.o affichage.o

EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(EXECUTABLE).o $(LIBTARGET) 
	$(CXX) $(EXECUTABLE).o -l$(LIBNAME) $(LIBSDIR) -o $(EXECUTABLE) -lm

$(LIBTARGET): $(LIBSOURCE) 
	$(CXX) $(CFLAGS) -shared $(LIBSOURCE) -o $(LIBTARGET)

.c.o:
	$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<

run: $(EXECUTABLE)
	$(EXPORTCMD) ./$(EXECUTABLE)

check: $(EXECUTABLE)
	$(EXPORTCMD) valgrind  ./$(EXECUTABLE)

clean: 
	$(CLEANCMD)
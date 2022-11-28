CXX = gcc
CFLAGS = -Wall -Werror -fpic -pedantic 
LIBSDIR = -L.
INCLUDEDIR = -I.

LIBCORENAME = projet

EXPORT = sh export.sh
LIBTARGET :=lib$(LIBCORENAME:=.so)
LIBSDIR += -L/usr/lib
INCLUDEDIR += -I/usr/include
CLEANCMD = rm -rf *.o *.so main

LIBSOURCE = individu population affichage
LIBSOURCECFILE = $(LIBSOURCE:=.c)
LIBSOURCEOFILE = $(LIBSOURCE:=.o)

EXESOURCE = main
TARGET = $(EXESOURCE)
EXESOURCECFILE = $(EXESOURCE:=.c)
EXESOURCEOFILE = $(EXESOURCE:=.o)

all: $(TARGET)

$(TARGET): $(EXESOURCEOFILE) $(LIBTARGET) 
	$(CXX) $(EXESOURCEOFILE) -l$(LIBCORENAME) $(LIBSDIR) -o $(TARGET) -lm

$(LIBTARGET): $(LIBSOURCEOFILE) 
	$(CXX) $(CFLAGS) -shared $(LIBSOURCEOFILE) -o $(LIBTARGET)

.c.o:
	$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<

run: $(TARGET)
	$(EXPORT) $(TARGET)

clean: 
	$(CLEANCMD)
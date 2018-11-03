IDIR =.
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =.

LIBS=-lm

_DEPS = head.h func.h lista.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = func.o main.o lista.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tp1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

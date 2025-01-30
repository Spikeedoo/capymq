IDIR =../include
CC=gcc
CFLAGS_BASE=-I$(IDIR)
CFLAGS_DEBUG = $(CFLAGS_BASE) -g -O0 # Debug symbols, no optimization
CFLAGS_RELEASE = $(CFLAGS_BASE) -O2 # Optimized for performance

ODIR=obj
LDIR =../lib

LIBS=

OUTFILE_DEBUG=../bin/capymq_debug
OUTFILE_RELEASE=../bin/capymq

_DEPS = conn.h reqproto.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o conn.o reqproto.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Debug Build
debug: CFLAGS = $(CFLAGS_DEBUG)
debug: $(OBJ)
	$(CC) -o $(OUTFILE_DEBUG) $^ $(CFLAGS) $(LIBS)

# Release Build
release: CFLAGS = $(CFLAGS_RELEASE)
release: $(OBJ)
	$(CC) -o $(OUTFILE_RELEASE) $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
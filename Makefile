TARGETS=hydro

.PHONY: all beautiful clean scan

# put your make.inc here
include make.inc

INC = -I$(HDF_INC)
LIB = -L$(HDF_LIB) -lhdf5 -lhdf5_hl -lm

EXCLUDE=
SOURCES=$(filter-out $(EXCLUDE), $(wildcard *.c))
OBJECTS=$(SOURCES:.c=.o)

all: $(TARGETS)

hydro: $(OBJECTS)
	@echo "--> hydro"
	@$(CC) $(CFLAGS) -o hydro.x $(OBJECTS) $(LIB)

.c.o:
	@echo CC $<
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -f $(OBJECTS) hydro.x

beautiful: $(SOURCES)
	clang-format -i $<

scan:
	scan-build make

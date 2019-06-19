TARGET=libregex.a
STATIC=ar rcs

IDIR=./include
SDIR=./src
BDIR=./bin

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	ifeq ($(shell which gcc-8), /usr/local/bin/gcc-8)
		CC=gcc-8#MacOS GNU gcc, not clang
		CTIMER=
	else
		CC=clang
		CTIMER=
	endif
else
	CC=gcc#GNU gcc
	CTIMER=-lrt
endif

OBJ=$(BDIR)/regex.o

all: $(BDIR)/$(TARGET)

$(BDIR)/$(TARGET): $(OBJ)
	$(STATIC) $@ $^

$(BDIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

.PHONY: clean

clean:
	rm -rf ./bin/*

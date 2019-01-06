CC = g++
TARGET = bin/main
SRCDIR = src
BUILDDIR = build


INCLUDEDIR = include
INCFLAGS = -I$(INCLUDEDIR)
SRC = main.cpp
BUILD = main.o
CFLAGS = -g

all: $(TARGET)

$(TARGET): $(BUILDDIR)/$(BUILD)
	$(CC) $(CFLAGS) $< -o $(TARGET)
$(BUILDDIR)/$(BUILD): $(SRCDIR)/$(SRC)
	$(CC) $(INCFLAGS) $(CFLAGS) $< -c -o $@

clean:
	rm $(BUILDDIR)/$(BUILD)

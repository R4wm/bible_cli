CXX = g++
CFLAGS = -Wall -Werror

INCLUDE = -I/usr/local/include
LDLIBS = -lcurl


SOURCES = src/main.cc
OUT = bible_cli

all: build

build: $(SOURCES)
	$(CXX) -o $(OUT) $(INCLUDE) $(CFLAGS) $(SOURCES)

AR = ar
CC = g++

.PHONY: lib
lib:
	cd src && $(CC) -g -O3 -c *.cpp && ar crs lib.a *.o

.PHONY: editor
editor:
	cd editor && $(CC) -g -O3 *.cpp ../src/lib.a `wx-config --libs` `wx-config --cxxflags` -o editor.out

.PHONY: test
test:
	cd test && $(CC) -g -O3 main.cpp ../src/lib.a -o test.out

.PHONY: clean
clean:
	cd src && rm -f *.o *.a
	cd test && rm -f *.out
	cd editor && rm -f *.out

.PHONY: all
all:
	make clean
	make lib
	make editor
	make test

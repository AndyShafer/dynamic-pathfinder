AR = ar
CC = g++

.PHONY: lib
lib:
	cd target && $(CC) -g -O3 -c ../dypf/main/src/*.cpp && ar crs lib/dypf.a *.o && cp ../dypf/main/src/*.h include

.PHONY: editor
editor:
	cd target && $(CC) -g -O3 ../editor/main/src/*.cpp lib/dypf.a -I ./include `wx-config --libs` `wx-config --cxxflags` -o editor.out

.PHONY: test
test:
	cd target && $(CC) -g -O3 ../dypf/test/src/main.cpp lib/dypf.a -I ./include -o test.out

.PHONY: clean
clean:
	cd target && rm -f *.o *.out
	cd target/lib && rm -f *.a
	cd target/include && rm -f *.h

.PHONY: all
all:
	make clean
	make lib
	make editor
	make test

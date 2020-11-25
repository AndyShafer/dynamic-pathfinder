AR = ar
CC = g++
EM = em++

.PHONY: lib
lib:
	cd target && $(CC) -g -O3 -c ../dypf/main/src/*.cpp && ar crs lib/dypf.a *.o && cp ../dypf/main/src/*.h include

.PHONY: editor
editor: lib
	cd target && $(CC) -g -O3 ../editor/main/src/*.cpp lib/dypf.a -I ./include `wx-config --libs` `wx-config --cxxflags` -o editor.out

.PHONY: test
test: lib
	cd target && $(CC) -g -O3 ../dypf/test/src/main.cpp lib/dypf.a -I ./include -o test.out

.PHONY: web
web:
	cd target && $(EM) --bind ../dypf/main/src/*.cpp ../dypf/main/src/web-bindings/*.cpp -o dypf.js

.PHONY: clean
clean:
	cd target && rm -f *.o *.out *.js *.wasm
	cd target/lib && rm -f *.a
	cd target/include && rm -f *.h

.PHONY: all
all: clean lib web editor test

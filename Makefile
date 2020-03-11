AR = ar
CC = g++

.PHONY: lib
lib:
	cd src && $(CC) -c *.cpp && ar crs lib.a *.o

.PHONY: test
test:
	cd test && $(CC) main.cpp ../src/lib.a -o test.out

.PHONY: clean
clean:
	cd src && rm -f *.o *.a
	cd test && rm -f *.out

.PHONY: all
all:
	make clean
	make lib
	make test

INC=-I/usr/local/include/CUnit
LIB=-L/usr/local/lib

all: strformat.c testcase.c
	gcc -g2 -O0 -fprofile-arcs -ftest-coverage -o test ${INC} ${LIB} $^ -lcunit

CC = gcc -std=c++17 -g 
OS = $(shell uname)

MODEL = Model.cc parser.cc
VALIDATOR = validator_lib/exprtk.hpp

ifeq ($(OS), Linux)
CHECKFLAGS = -lgtest -lgtest_main -lrt -lm -lstdc++ -pthread 
else
CHECKFLAGS =  -lm -lpthread  -lstdc++
endif

all: build_test

build_test:
	$(CC) $(FLAGS) $(MODEL) $(VALIDATOR) -o test $(CHECKFLAGS)
	./test

clean:
	rm -rf report \
	lib_s21_matrix_oop.a \
	report.info \
	*.gcda \
	*.gcno \
	s21_matrix_oop.o \
	test.dSYM \
	test \
	test_*

CARGS = gcc -std=c++17 -g -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)

FILES = model/*.cc

APP_ARCHIVE = Archive_SmartCalc_v2.0

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -lgtest_main -lrt -lm -lstdc++ -pthread
else
	CHECK_FLAGS = -lgtest -lgtest_main -lm -lpthread  -lstdc++
endif

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: install

tests:
	$(CARGS) tests.cc $(FILES) $(CHECK_FLAGS) -o unit_test
	./unit_test

install: uninstall
	mkdir build
	cp -rf SmartCalc_v2-0.pro build
	cp -rf model build
	cp -rf main.cc build
	cp -rf view build
	cp -rf controller build
	cd build && qmake SmartCalc_v2-0.pro
	make -C build
	cd build && make clean
	open ./build/SmartCalc_v2-0.app/Contents/MacOS/SmartCalc_v2-0

uninstall:
	rm -rf build

dist:
	rm -rf $(APP_ARCHIVE)/
	mkdir $(APP_ARCHIVE)
	mkdir $(APP_ARCHIVE)/src/
	cp -r build/SmartCalc_v2-0.app $(APP_ARCHIVE)/src/SmartCalc_v2-0.app
	tar -cvzf $(APP_ARCHIVE).tgz $(APP_ARCHIVE)/
	rm -rf $(APP_ARCHIVE)

dvi:
	$(OPEN_CMD) dvi.txt

to_style:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./model/*.cc
	clang-format -i ./model/*.h
	clang-format -i ./controller/*.cc
	clang-format -i ./controller/*.h
	clang-format -i ./view/*.cc
	clang-format -i ./view/*.h
	clang-format -i *.cc
	rm -rf .clang-format

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n ./model/*.cc
	clang-format -n ./model/*.h
	clang-format -n ./controller/*.cc
	clang-format -n ./controller/*.h
	clang-format -n ./view/*.cc
	clang-format -n ./view/*.h
	clang-format -n *.cc
	rm -rf .clang-format


leaks: tests
	CK_FORK=no leaks --atExit -- ./unit_test

valgrind: tests
	 CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./unit_test
	 make clean

docker_check: 
	docker build -t "valgrind:1.0" .
	docker run --rm -v $(PWD):/tmp -w /tmp valgrind:1.0


clean:
	rm -rf build*
	rm -rf *.o *.gcno *.gcda *.a *.info report .clang-format *.out *.dSYM *.Identifier *.stash
	rm -rf $(APP_ARCHIVE).tgz
	rm -f unit_test
	rm -f gcov_test
	rm -f out
	rm -f *.gcov
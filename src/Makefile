CC=gcc
CFLAGS= -Wall -Werror -Wextra -lm
SOURCES = MyString.c parce.c stack.c abdujaffine.c
SOURCES_TEST = parseTest.c
OUTFILE_TEST = parce_test
OS=$(shell uname)
INSTALL_DIR=SmartView
DIR=.

TEST_FLAGS = -fprofile-arcs -ftest-coverage


ifeq ($(OS), Linux)
	TFLAGS = -lcheck -lm -lpthread -lrt -lsubunit -D_GNU_SOURCE
	QMAKE=qmake6
	OPT=-spec linux-g++ CONFIG+=qtquickcompiler
	BUILD_DIR=build-SmartView-Desktop_x86_darwin_generic_mach_o_64bit-Release
	DIR=
	LIBS=-lcheck -lpthread -lrt -lm -lsubunit
else
	TFLAGS = -lcheck -lm
	QMAKE=qmake
	OPT=CONFIG+=qtquickcompiler
	BUILD_DIR=build-SmartView-Desktop_x86_darwin_generic_mach_o_64bit-Release/
	DIR=
	LIBS=-lcheck -lm
endif

all: build

build: clean
	$(QMAKE) -o $(BUILD_DIR)/Makefile ./2dTyan/2dTyan.pro $(OPT)
	make -C $(BUILD_DIR)/ first

rebuild: clean all

install: build
	@mkdir -p /Users/$(shell whoami)/Desktop/$(INSTALL_DIR)
	@cp -r $(BUILD_DIR)$(DIR)2dTyan.app /Users/$(shell whoami)/Desktop/$(INSTALL_DIR)
	@open /Users/$(shell whoami)/Desktop/$(INSTALL_DIR)
	rm -rf a.out *.tgz *.o *.a *.gcda *.gcno *.info *.info report build* *.cfg SmartViewgu

run:
	open /Users/$(shell whoami)/Desktop/$(INSTALL_DIR)/2dTyan.app

uninstall:
	@rm -rf /Users/$(shell whoami)/Desktop/$(INSTALL_DIR)

dist: clean
	tar -czf "romi_SmartView.tgz" forms headers sources *.pro Makefile

dvi:
	open ../documentation/main.html

tests: gcov_report

gcov_report: clean
	gcc --coverage $(SOURCES) $(SOURCES_TEST) -o test $(TFLAGS)
	./test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c
	clang-format -n 2dTyan/*.cpp
	clang-format -n *.h
	clang-format -n 2dTyan/*.h
	rm .clang-format

stylefix:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c
	clang-format -i 2dTyan/*.cpp
	clang-format -i *.h
	clang-format -i 2dTyan/*.h
	rm .clang-format

clean:
	rm -rf a.out *.tgz *.o *.a *.gcda *.gcno *.info *.info report build* *.cfg SmartViewgu

CC0=gcc -g
CC1=gcc -g
CFLAGS=-c
LDFLAGS= #-Wall -Wextra -Werror
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC1 += -D OS_MAC
else
	CC1 += -D OS_LINUX
endif

all: clean s21_decimal.a test  

test: s21_decimal.a test.c
ifeq ($(OS), Darwin)
	$(CC0) $(LDFLAGS) -o test test.c s21_decimal.a -lcheck
	./test
else
	gcc test.c s21_decimal.a -o test -lcheck -lsubunit -lrt -lpthread -lm
	./test
endif

s21_decimal.a: overflow.o s21_decimal.o 
	ar rcs s21_decimal.a overflow.o s21_decimal.o 
	ranlib $@
	cp $@ lib$@
	
s21_decimal.o: s21_decimal.c
	$(CC1) $(LDFLAGS) -c -o s21_decimal.o s21_decimal.c

overflow.o: overflow_decimal.c
	$(CC1) $(LDFLAGS) -c -o overflow.o overflow_decimal.c

clean:
	rm -rf test *.a *.o *.out fizz *.gc* *.info report

rebuild: clean all


style:
	python3 ../materials/linters/cpplint.py *.c *.h

gcov_report: 
ifeq ($(OS), Darwin)
	$(CC1) --coverage $(LDFLAGS) test.c s21_decimal.c overflow_decimal.c -o test -lcheck
else
	$(CC1) --coverage $(LDFLAGS) test.c s21_decimal.c overflow_decimal.c -o test -lcheck -lsubunit -lrt -lpthread -lm
endif
	./test
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info

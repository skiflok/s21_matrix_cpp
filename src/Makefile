CC=gcc -std=c11
CFLAGS=-Wall -Wextra -Werror
GCOV_LIBS=--coverage
BUILD_PATH=./
SOURCES=s21_matrix.c
H=s21_matrix.h
LIBO=s21_matrix.o
LIBA=s21_matrix.a
EXE=test.out

OS = $(shell uname)

ifeq ($(OS), Darwin)
	TST_LIBS=-lcheck -lm
else
	TST_LIBS=-lcheck -pthread -lrt -lm -D_GNU_SOURCE -lsubunit -lpthread -g
endif

all: s21_matrix.a

clean:
	rm -rf *.a && rm -rf *.o *.out
	rm -rf *.info && rm -rf *.gcda && rm -rf *.gcno &&  rm -rf *.gcov
	rm -rf report/ && rm -rf *.

test: s21_matrix.a
	$(CC) $(CFLAGS) test.c -L. $(LIBA) $(TST_LIBS) -o $(BUILD_PATH)$(EXE)
	$(BUILD_PATH)$(EXE)

mytest: clean
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE)
	$(BUILD_PATH)$(EXE)

rebuild: clean all

s21_matrix.a: clean
	$(CC) $(CFLAGS) -c $(SOURCES) -o $(BUILD_PATH)$(LIBO)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

gcov_report: s21_matrix.a
	$(CC) $(CFLAGS) $(GCOV_LIBS) test.c $(SOURCES) $(LIBA) -L. $(LIBA) $(TST_LIBS) -o $(BUILD_PATH)$(EXE)
	$(BUILD_PATH)$(EXE)
	lcov -t "test" -c -d $(BUILD_PATH) --output-file $(BUILD_PATH)coverage.info
	genhtml $(BUILD_PATH)coverage.info --output-directory $(BUILD_PATH)report/
	open ./report/index.html

leaks:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt 	$(BUILD_PATH)$(EXE)

check:
	@echo
	@echo ===STYLE TEST===
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	rm CPPLINT.cfg


INC += -I../inc
LIB_PATH += -L../output
CC=gcc


## source files
TEST_SRC_DIR = ./src
TEST_SRC_FILES += $(wildcard $(TEST_SRC_DIR)/*.cpp)

## test source files
TEST_SRC_DIR = .
TEST_SRC_FILES += $(wildcard $(TEST_SRC_DIR)/*.c)

test:main.c chashmap_test.c clist_test.c ../src/clist.c ../src/chashmap.c ../src/cutil.c
	@$(CC) $(INC) $(LIB_PATH) -g  -O2 -o test main.c chashmap_test.c clist_test.c ../src/clist.c ../src/chashmap.c ../src/cutil.c -Wno-int-conversion -fprofile-arcs -ftest-coverage

.PHONY:report run clean

run:test
	./test

report:run
	lcov -d . -t test -o test.info -b . -c --rc lcov_branch_coverage=1
	lcov --extract test.info '*.c' -o finalresult.info --rc lcov_branch_coverage=1
	genhtml -o result finalresult.info --branch-coverage

memchk:test
	valgrind --tool=memcheck --leak-check=full ./test

clean:
	@rm -rf test ./result *.gcno *.gcda *.info

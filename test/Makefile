
INC += -I../inc
LIB_PATH += -L../output
CC=gcc

test:main.c chashmap_test.c clist_test.c ../src/clist.c ../src/chashmap.c
	@$(CC) $(INC) $(LIB_PATH) -g -o test main.c chashmap_test.c clist_test.c ../src/clist.c ../src/chashmap.c -Wno-int-conversion -fprofile-arcs -ftest-coverage

.PHONY:report run clean

run:test
	./test

report:run
	lcov -d . -t test -o test.info -b . -c
	lcov --extract test.info '*.c' -o finalresult.info
	genhtml -o result finalresult.info
	
clean:
	@rm -rf test ./result *.gcno *.gcda *.info


INC += -I../inc
LIB_PATH += -L../output
CC=gcc

test:libcwheel.a main.c chashmap_test.c clist_test.c
	@$(CC) $(INC) $(LIB_PATH) -g -o test main.c chashmap_test.c clist_test.c -Wno-int-conversion -lcwheel

libcwheel.a:
	cd .. && make
clean:
	@rm -rf test

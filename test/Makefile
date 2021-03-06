MD := @mkdir -p
RM := @rm -rf
LIB_PATH += -L../output
CC=gcc
INC += -I../inc

OUT_DIR := ./output
TARGET := $(OUT_DIR)/test

## source files
SRC_DIR = ../src
SRC_FILES += $(wildcard $(SRC_DIR)/*.c)

## test source files
TEST_SRC_DIR = .
TEST_SRC_FILES += $(wildcard $(TEST_SRC_DIR)/*.c)

## *.o 
OBJS += $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SRC_FILES))
OBJS += $(patsubst $(TEST_SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(TEST_SRC_FILES))


$(TARGET):$(OBJS)
	@$(CC) $(LIB_PATH) -g -Wl,--whole-archive -Wl,-O1 -Wl,-Map,$(OUT_DIR)/test.map -Wl,--no-whole-archive -fPIC $(OBJS) -o $(TARGET) -lgcov

## rule for source file
$(OUT_DIR)/%.o:$(SRC_DIR)/%.c
	@$(MD) $(OUT_DIR)
	$(CC) $(INC) -Wno-int-conversion -fprofile-arcs -ftest-coverage -c -g $< -o $@
	
## rule for test source file
$(OUT_DIR)/%.o:$(TEST_SRC_DIR)/%.c
	@$(MD) $(OUT_DIR)
	$(CC) $(INC) -Wno-int-conversion -c -g $< -o $@

.PHONY:report run clean memchk

run:$(TARGET)
	$(TARGET)

report:run
	lcov -d . -t test -o $(OUT_DIR)/test.info -b . -c --rc lcov_branch_coverage=1
	lcov --extract $(OUT_DIR)/test.info '*.c' -o $(OUT_DIR)/finalresult.info --rc lcov_branch_coverage=1
	genhtml -o $(OUT_DIR)/result $(OUT_DIR)/finalresult.info --branch-coverage

memchk:$(TARGET)
	valgrind --tool=memcheck --leak-check=full $(TARGET)

clean:
	@rm -rf ./output

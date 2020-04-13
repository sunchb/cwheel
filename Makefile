#  Define the command of tool
CC := gcc
AR := ar
MD := mkdir -p
RM := rm -rf

#		output files
OUT_DIR := ./output
TARGET := $(OUT_DIR)/libcwheel.a

#		source files
SRC_DIR = ./src
SRC_FILES += $(wildcard $(SRC_DIR)/*.c)

#		*.o
OBJS += $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SRC_FILES))

#		include path
INC_PATH += -I./inc/

$(TARGET):$(OBJS)
	@$(MD) $(OUT_DIR)
	@$(AR) rc $(TARGET) $(OBJS)

$(OUT_DIR)/%.o:$(SRC_DIR)/%.c
	@$(MD) $(OUT_DIR)
	@$(CC) $(INC_PATH) -c $< -o $@

.PHONY:clean
clean:
	@$(RM) $(OUT_DIR)

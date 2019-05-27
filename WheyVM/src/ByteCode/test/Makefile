
CC = gcc
CFLAGS = -O3 -Wall -std=c99

SRC_DIR = ../src
INC_DIR = ..
OBJ_DIR = ./out
MKDIR_P = mkdir -p

all: bytecode.out

$(OBJ_DIR):
	$(MKDIR_P) $(OBJ_DIR)
	

$(OBJ_DIR)/Constant.o : $(SRC_DIR)/Constant.c $(INC_DIR)/Constant.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Function.o : $(SRC_DIR)/Function.c $(INC_DIR)/Function.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/ByteCode.o : $(SRC_DIR)/ByteCode.c $(INC_DIR)/ByteCode.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/ByteCodeTest.o : ByteCodeTest.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

bytecode.out: $(OBJ_DIR)/ByteCodeTest.o $(OBJ_DIR)/ByteCode.o $(OBJ_DIR)/Function.o $(OBJ_DIR)/Constant.o
	$(CC) $^ -o $@ -lm

clean:
	rm -rf bytecode.out $(OBJ_DIR)

.PHONY: all clean

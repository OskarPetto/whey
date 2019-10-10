
CC = gcc
CFLAGS = -O3 -Wall -std=c11

SRC_DIR = ../src
INC_DIR = ..
OBJ_DIR = ./out
MKDIR_P = mkdir -p

all: class.out

$(OBJ_DIR):
	$(MKDIR_P) $(OBJ_DIR)
	

$(OBJ_DIR)/Constant.o : $(SRC_DIR)/Constant.c $(INC_DIR)/Constant.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Method.o : $(SRC_DIR)/Method.c $(INC_DIR)/Method.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Class.o : $(SRC_DIR)/Class.c $(INC_DIR)/Class.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/ClassTest.o : ClassTest.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

class.out: $(OBJ_DIR)/ClassTest.o $(OBJ_DIR)/Class.o $(OBJ_DIR)/Method.o $(OBJ_DIR)/Constant.o
	$(CC) $^ -o $@ -lm

clean:
	rm -rf class.out $(OBJ_DIR)

.PHONY: all clean

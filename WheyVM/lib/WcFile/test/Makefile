
CC = gcc
CFLAGS = -O3 -Wall -std=c99

SRC_DIR = ../src
INC_DIR = ..
OBJ_DIR = ./out
MKDIR_P = mkdir -p

all: wcfile.out

$(OBJ_DIR):
	$(MKDIR_P) $(OBJ_DIR)
	

$(OBJ_DIR)/Constant.o : $(SRC_DIR)/Constant.c $(INC_DIR)/Constant.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Function.o : $(SRC_DIR)/Function.c $(INC_DIR)/Function.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/WcFile.o : $(SRC_DIR)/WcFile.c $(INC_DIR)/WcFile.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/WcFileTest.o : WcFileTest.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

wcfile.out: $(OBJ_DIR)/WcFileTest.o $(OBJ_DIR)/WcFile.o $(OBJ_DIR)/Function.o $(OBJ_DIR)/Constant.o
	$(CC) $^ -o $@ -lm

clean:
	rm -rf wcfile.out $(OBJ_DIR)

.PHONY: all clean

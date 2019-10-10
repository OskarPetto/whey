
CC = gcc
CFLAGS = -O3 -Wall -std=c11

SRC_DIR = ../src
INC_DIR = ..
OBJ_DIR = ./out
MKDIR_P = mkdir -p

WHEY_SRC_DIR = ../../src
WHEY_INC_DIR = ../../

OBJECT_SRC_DIR = ../../Object/src
OBJECT_INC_DIR = ../../Object

CLASS_SRC_DIR = ../../Class/src
CLASS_INC_DIR = ../../Class

all: stack.out

$(OBJ_DIR):
	$(MKDIR_P) $(OBJ_DIR)

$(OBJ_DIR)/Types.o : $(WHEY_SRC_DIR)/Types.c $(WHEY_INC_DIR)/Types.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/Array.o : $(OBJECT_SRC_DIR)/Array.c $(OBJECT_INC_DIR)/Array.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Double.o : $(OBJECT_SRC_DIR)/Double.c $(OBJECT_INC_DIR)/Double.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Gc.o : $(OBJECT_SRC_DIR)/Gc.c $(OBJECT_INC_DIR)/Gc.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Integer.o : $(OBJECT_SRC_DIR)/Integer.c $(OBJECT_INC_DIR)/Integer.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Map.o : $(OBJECT_SRC_DIR)/Map.c $(OBJECT_INC_DIR)/Map.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Object.o : $(OBJECT_SRC_DIR)/Object.c $(OBJECT_INC_DIR)/Object.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Pair.o : $(OBJECT_SRC_DIR)/Pair.c $(OBJECT_INC_DIR)/Pair.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/String.o : $(OBJECT_SRC_DIR)/String.c $(OBJECT_INC_DIR)/String.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/Method.o : $(CLASS_SRC_DIR)/Method.c $(CLASS_INC_DIR)/Method.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/Stack.o : $(SRC_DIR)/Stack.c $(INC_DIR)/Stack.h $(INC_DIR)/Operand.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/StackTest.o : StackTest.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

stack.out: $(OBJ_DIR)/StackTest.o $(OBJ_DIR)/Stack.o $(OBJ_DIR)/Array.o $(OBJ_DIR)/Double.o $(OBJ_DIR)/Gc.o $(OBJ_DIR)/Integer.o $(OBJ_DIR)/Map.o $(OBJ_DIR)/Object.o $(OBJ_DIR)/Pair.o $(OBJ_DIR)/String.o $(OBJ_DIR)/Method.o $(OBJ_DIR)/Types.o
	$(CC) $^ -o $@ -lm

clean:
	rm -rf stack.out $(OBJ_DIR)

.PHONY: all clean

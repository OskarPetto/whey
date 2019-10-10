
CC = gcc
CFLAGS = -O3 -Wall -std=c11
LFLAGS = -lm

WHEY_SRC_DIR = ../../src
WHEY_INC_DIR = ../../

SRC_DIR = ../src
INC_DIR = ..
OBJ_DIR = ./out
MKDIR_P = mkdir -p

all: object.out

$(OBJ_DIR):
	$(MKDIR_P) $(OBJ_DIR)

$(OBJ_DIR)/Types.o : $(WHEY_SRC_DIR)/Types.c $(WHEY_INC_DIR)/Types.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/Array.o : $(SRC_DIR)/Array.c $(INC_DIR)/Array.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Double.o : $(SRC_DIR)/Double.c $(INC_DIR)/Double.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Gc.o : $(SRC_DIR)/Gc.c $(INC_DIR)/Gc.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Integer.o : $(SRC_DIR)/Integer.c $(INC_DIR)/Integer.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Map.o : $(SRC_DIR)/Map.c $(INC_DIR)/Map.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Object.o : $(SRC_DIR)/Object.c $(INC_DIR)/Object.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Pair.o : $(SRC_DIR)/Pair.c $(INC_DIR)/Pair.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/String.o : $(SRC_DIR)/String.c $(INC_DIR)/String.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/ObjectTest.o : ObjectTest.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

object.out: $(OBJ_DIR)/ObjectTest.o $(OBJ_DIR)/Array.o $(OBJ_DIR)/Double.o $(OBJ_DIR)/Gc.o $(OBJ_DIR)/Integer.o $(OBJ_DIR)/Map.o $(OBJ_DIR)/Object.o $(OBJ_DIR)/Pair.o $(OBJ_DIR)/String.o $(OBJ_DIR)/Types.o
	$(CC) $^ -o $@ ${LFLAGS}

clean:
	rm -rf object.out $(OBJ_DIR)

.PHONY: all clean

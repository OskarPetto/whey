
CC = gcc
CFLAGS = -O3 -Wall -std=c99

OPERAND_SRC_DIR = ./Operand/src
OPERAND_INC_DIR = ./Operand

WCFILE_SRC_DIR = ./WcFile/src
WCFILE_INC_DIR = ./WcFile

WHEYVM_SRC_DIR = ./src
WHEYVM_INC_DIR = .

OBJ_DIR = ./out

MKDIR_P = mkdir -p

all: wvm.out

$(OBJ_DIR):
	$(MKDIR_P) $(OBJ_DIR)

# ----------------------------------------------------------------------------------------------------------------------------

$(OBJ_DIR)/Array.o : $(OPERAND_SRC_DIR)/Array.c $(OPERAND_INC_DIR)/Array.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Double.o : $(OPERAND_SRC_DIR)/Double.c $(OPERAND_INC_DIR)/Double.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Gc.o : $(OPERAND_SRC_DIR)/Gc.c $(OPERAND_INC_DIR)/Gc.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Integer.o : $(OPERAND_SRC_DIR)/Integer.c $(OPERAND_INC_DIR)/Integer.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Map.o : $(OPERAND_SRC_DIR)/Map.c $(OPERAND_INC_DIR)/Map.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Object.o : $(OPERAND_SRC_DIR)/Object.c $(OPERAND_INC_DIR)/Object.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Pair.o : $(OPERAND_SRC_DIR)/Pair.c $(OPERAND_INC_DIR)/Pair.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/String.o : $(OPERAND_SRC_DIR)/String.c $(OPERAND_INC_DIR)/String.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ----------------------------------------------------------------------------------------------------------------------------

$(OBJ_DIR)/Constant.o : $(WCFILE_SRC_DIR)/Constant.c $(WCFILE_INC_DIR)/Constant.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/Function.o : $(WCFILE_SRC_DIR)/Function.c $(WCFILE_INC_DIR)/Function.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/WcFile.o : $(WCFILE_SRC_DIR)/WcFile.c $(WCFILE_INC_DIR)/WcFile.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ----------------------------------------------------------------------------------------------------------------------------

$(OBJ_DIR)/Frame.o : $(WHEYVM_SRC_DIR)/Frame.c $(WHEYVM_INC_DIR)/Frame.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/InstructionSet.o : $(WHEYVM_SRC_DIR)/InstructionSet.c $(WHEYVM_INC_DIR)/InstructionSet.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/WheyVM.o : $(WHEYVM_SRC_DIR)/WheyVM.c $(WHEYVM_INC_DIR)/WheyVM.h $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o : $(WHEYVM_SRC_DIR)/main.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ----------------------------------------------------------------------------------------------------------------------------

wvm.out: $(OBJ_DIR)/Array.o $(OBJ_DIR)/Double.o $(OBJ_DIR)/Gc.o $(OBJ_DIR)/Integer.o $(OBJ_DIR)/Object.o $(OBJ_DIR)/Map.o $(OBJ_DIR)/Pair.o $(OBJ_DIR)/String.o $(OBJ_DIR)/Constant.o $(OBJ_DIR)/Function.o $(OBJ_DIR)/WcFile.o $(OBJ_DIR)/Frame.o $(OBJ_DIR)/InstructionSet.o $(OBJ_DIR)/WheyVM.o $(OBJ_DIR)/main.o
	$(CC) $^ -o $@ -lm

clean:
	rm -rf wvm.out $(OBJ_DIR)

.PHONY: all clean


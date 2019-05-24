
CC = gcc
CFLAGS = -O3 -Wall -std=c99

SRC_DIR = ../src
INC_DIR = ..
OUT_DIR = out
COMMON_HEADER = $(INC_DIR)/Array.h $(INC_DIR)/Floating.h $(INC_DIR)/Gc.h $(INC_DIR)/Integer.h $(INC_DIR)/Map.h $(INC_DIR)/Object.h $(INC_DIR)/Pair.h $(INC_DIR)/String.h 

Array.o : $(SRC_DIR)/Array.c $(INC_DIR)/Object.h
	$(CC) $(CFLAGS) -c $^ 


Floating.o : $(SRC_DIR)/Floating.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 


Gc.o : $(SRC_DIR)/Gc.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 


Integer.o : $(SRC_DIR)/Integer.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 


Map.o : $(SRC_DIR)/Map.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 


Object.o : $(SRC_DIR)/Object.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 


Pair.o : $(SRC_DIR)/Pair.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 


String.o : $(SRC_DIR)/String.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 


ArrayTest.o: ArrayTest.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 

FloatingTest.o: FloatingTest.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 

GcTest.o: GcTest.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 

IntegerTest.o: IntegerTest.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 

MapTest.o: MapTest.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 

ObjectTest.o: ObjectTest.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 

PairTest.o: PairTest.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 

StringTest.o: StringTest.c $(COMMON_HEADER)
	$(CC) $(CFLAGS) -o $@ -c $^ 

arraytest: Array.o Floating.o Gc.o Integer.o Map.o Object.o Pair.o String.o ArrayTest.o
	$(CC) -o $@ $< 

floatingtest: Array.o Floating.o Gc.o Integer.o Map.o Object.o Pair.o String.o FloatingTest.o
	$(CC) -o $@ $< 

gctest: Array.o Floating.o Gc.o Integer.o Map.o Object.o Pair.o String.o GcTest.o
	$(CC) -o $@ $< 

integertest: Array.o Floating.o Gc.o Integer.o Map.o Object.o Pair.o String.o IntegerTest.o
	$(CC) -o $@ $< 

maptest: Array.o Floating.o Gc.o Integer.o Map.o Object.o Pair.o String.o MapTest.o
	$(CC) -o $@ $< 

objecttest: Array.o Floating.o Gc.o Integer.o Map.o Object.o Pair.o String.o ObjectTest.o
	$(CC) -o $@ $< 

pairtest: Array.o Floating.o Gc.o Integer.o Map.o Object.o Pair.o String.o PairTest.o
	$(CC) -o $@ $< 

stringtest: Array.o Floating.o Gc.o Integer.o Map.o Object.o Pair.o String.o StringTest.o
	$(CC) -o $@ $< 

.PHONY: clean arraytest floatingtest gctest integertest maptest objecttest pairtest stringtest


clean:
	rm -f arraytest floatingtest gctest integertest maptest objecttest pairtest stringtest *.o
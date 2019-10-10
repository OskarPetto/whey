import sys
import re
import struct

keywords = {
    "JUMP": "01",
    "JUMP_TRUE": "02",
    "JUMP_FALSE": "03",
    "LOAD": "04",
    "LOAD_ARGUMENT": "05",
    "STORE": "06",
    "CALL": "07",
    "RETURN": "08",
    "CONSTANT": "09",
    "POP": "0A",
    "DUP": "0B",
    "PRINT": "0C",
    "EQUAL": "0D",
    "NOT_EQUAL": "0E",
    "GREATER_THAN": "0F",
    "GREATER_THAN_OR_EQUAL": "10",
    "LESS_THAN": "11",
    "LESS_THAN_OR_EQUAL": "12",
    "NUMBER_ADD": "13",
    "NUMBER_SUBTRACT": "14",
    "NUMBER_MULTIPLY": "15",
    "NUMBER_DIVIDE": "16",
    "NUMBER_POWER": "17",
    "NUMBER_NEGATE": "18",
    "NUMBER_SQRT": "19",
    "INTEGER_TO_DOUBLE": "1A",
    "INTEGER_INCREMENT": "1B",
    "INTEGER_DECREMENT": "1C",
    "INTEGER_MODULO": "1D",
    "INTEGER_AND": "1E",
    "INTEGER_OR": "1F",
    "INTEGER_NOT": "20",
    "INTEGER_XOR": "21",
    "DOUBLE_TO_INTEGER": "22",
    "DOUBLE_CEIL": "23",
    "DOUBLE_FLOOR": "24",
    "OBJECT_NULL": "25",
    "OBJECT_IS_NULL": "26",
    "OBJECT_COPY": "27",
    "OBJECT_EQUALS": "28",
    "OBJECT_HASH": "29",
    "OBJECT_TO_STRING": "2A",
    "ARRAY_NEW": "2B",
    "ARRAY_NEW_WITH_SIZE": "2C",
    "ARRAY_SIZE": "2D",
    "ARRAY_IS_EMPTY": "2E",
    "ARRAY_GET": "2F",
    "ARRAY_SET": "30",
    "ARRAY_INSERT": "31",
    "ARRAY_INSERT_ALL": "32",
    "ARRAY_REMOVE": "33",
    "ARRAY_PUSH": "34",
    "ARRAY_PUSH_ALL": "35",
    "ARRAY_POP": "36",
    "MAP_NEW": "37",
    "MAP_SIZE": "38",
    "MAP_IS_EMPTY": "39",
    "MAP_GET": "3A",
    "MAP_PUT": "3B",
    "MAP_PUT_ALL": "3C",
    "MAP_REMOVE": "3D",
    "MAP_HAS_KEY": "3E",
    "MAP_ENTRIES": "3F",
    "MAP_KEYS": "40",
    "MAP_VALUES": "41",
    "PAIR_NEW": "42",
    "PAIR_GET_FIRST": "43",
    "PAIR_SET_FIRST": "44",
    "PAIR_GET_SECOND": "45",
    "PAIR_SET_SECOND": "46",
    "STRING_SIZE": "47",
    "STRING_IS_EMPTY": "48",
    "STRING_FROM_ARRAY": "49",
    "STRING_TO_ARRAY": "4A",
    "STRING_COMPARE": "4B",
    "STRING_CONCATENATE": "4C",
    "STRING_SUBSTRING": "4D",
    "STRING_INDEX_OF": "4E",
    "STRING_CONTAINS": "4F",
    "STRING_REPLACE": "50",
    "STRING_SPLIT": "51"
}

labels = {}

def removeComments(code):
    if code[len(code) - 1] != '\n':
        code = code + '\n'
    return re.sub(r'#.*\n', "", code)

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print('File needed')
        exit(1)

    code = open(sys.argv[1], 'r').read()

    code = removeComments(code)

    code = code.replace(' ', '')
    code = code.replace('\n', '')

    byteArray = bytes.fromhex(code)

    outFile = open(sys.argv[1].replace('.txt', '.wc'), 'wb')

    outFile.write(byteArray)

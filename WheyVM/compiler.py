import sys
import re

if __name__ == "__main__":
    
    if len(sys.argv) != 2:
        print('File needed')
        exit(1)

    code = open(sys.argv[1], 'r').read()
    if code[len(code) - 1] != '\n':
        code = code + '\n'
    code = re.sub('\#.*\n', "", code)

    byteArray = bytes.fromhex(code)

    outFile = open(sys.argv[1].replace('.txt', '.wc'), 'wb')

    outFile.write(byteArray)


#include <stdio.h>
#include <getopt.h>
#include "../WcFile/WcFile.h"
#include "../WheyVM.h"

#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#define DEFAULT_CALL_STACK_SIZE 1000
#define DEFAULT_OPERAND_STACK_SIZE 100
#define DEFAULT_MEMORY_SIZE 10000
#define DEFAULT_LOAD_FACTOR 0.6

int main(int argc, char **argv) {

    char opt;
    uint8_t state = 0;
    uint16_t callStackSize = DEFAULT_CALL_STACK_SIZE;
    uint16_t operandStackSize = DEFAULT_OPERAND_STACK_SIZE;
    uint32_t memorySize = DEFAULT_MEMORY_SIZE;
    double loadFactor = DEFAULT_LOAD_FACTOR;
    int64_t temp;
    double doubleTemp;

    while((opt = getopt(argc, argv, "s:o:m:l:d")) != -1)  
    {  
        switch (opt)
        {
            case 's':
                temp = strtol(optarg, NULL, 10);
                if (temp <= 0)
                {
                    fprintf(stderr, "Call stack size %ld must be a postive integer.\n", temp);
                    return 1;
                }
                printf("Call stack size set to: %ld\n", temp);
                callStackSize = temp;
                break;

            case 'o':
                temp = strtol(optarg, NULL, 10);
                if (temp <= 0)
                {
                    fprintf(stderr, "Operand stack size %ld must be a postive integer.\n", temp);
                    return 1;
                }
                printf("Operand stack size set to: %ld\n", temp);
                operandStackSize = temp;
                break;

            case 'm':
                temp = strtol(optarg, NULL, 10);
                if (temp <= 0)
                {
                    fprintf(stderr, "Memory size %ld must be a postive integer.\n", temp);
                    return 1;
                }
                printf("Memory size set to: %ld\n", temp);
                memorySize = temp;
                break;

            case 'l':
                doubleTemp = strtod(optarg, NULL);
                if (doubleTemp <= 0 || doubleTemp > 1)
                {
                    fprintf(stderr, "Load factor %f must be between 0 and 1.\n", doubleTemp);
                    return 1;
                }
                printf("Load factor set to: %f\n", doubleTemp);
                loadFactor = doubleTemp;
                break;

            case 'd':
                state = WHEYVM_STATE_DEBUG;
                printf("Running in debug mode\n");
                break;
        
            default:
                fprintf(stderr, "Unexpected option %c\n", opt);
                return 1;
        }
    }

    if (argc - optind != 1) {
        fprintf(stderr, "One filename must be given.\n");
        return 1;
    }

    struct WcFile *program = wcFileNew(argv[optind]);

    wvmRun(program, callStackSize, operandStackSize, memorySize, loadFactor, state);

    wcFileFree(program);

    return 0;
}
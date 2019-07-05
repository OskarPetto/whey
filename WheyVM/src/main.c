#include <stdio.h>
#include <getopt.h>
#include "../WcFile/WcFile.h"
#include "../WheyVM.h"

#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>

#define DEFAULT_CALL_STACK_SIZE 1000
#define DEFAULT_OPERAND_STACK_SIZE 100
#define DEFAULT_MEMORY_SIZE 100000

int main(int argc, char **argv) {

    char opt;
    uint8_t state = 0;
    uint16_t callStackSize = DEFAULT_CALL_STACK_SIZE;
    uint16_t operandStackSize = DEFAULT_OPERAND_STACK_SIZE;
    uint32_t memorySize = DEFAULT_MEMORY_SIZE;
    int64_t temp;

    while((opt = getopt(argc, argv, "s:o:m:d")) != -1)  
    {  
        switch (opt)
        {
            case 's':
                temp = strtol(optarg, NULL, 10);
                if (temp < 0)
                {
                    fprintf(stderr, "call stack size %"PRId64" must be a postive integer.\n", temp);
                    return 1;
                }
                printf("call stack size set to: %"PRId64".\n", temp);
                callStackSize = temp;
                break;

            case 'o':
                temp = strtol(optarg, NULL, 10);
                if (temp < 0)
                {
                    fprintf(stderr, "operand stack size %"PRId64" must be a postive integer.\n", temp);
                    return 1;
                }
                printf("operand stack size set to: %"PRId64".\n", temp);
                operandStackSize = temp;
                break;

            case 'm':
                temp = strtol(optarg, NULL, 10);
                if (temp < 0)
                {
                    fprintf(stderr, "gc-memory size %"PRId64" must be a postive integer.\n", temp);
                    return 1;
                }
                printf("gc-memory size set to: %"PRId64".\n", temp);
                memorySize = temp;
                break;

            case 'd':
                state = WHEYVM_STATE_DEBUG;
                printf("running in debug mode.\n");
                break;
        
            default:
                fprintf(stderr, "unexpected option %c.\n", opt);
                return 1;
        }
    }

    if (argc - optind != 1) {
        fprintf(stderr, "one filename must be given.\n");
        return 1;
    }

    printf("running program: \"%s\".\n", argv[optind]);

    struct WcFile *program = wcFileNew(argv[optind]);

    int returnStatus = wvmRun(program, callStackSize, operandStackSize, memorySize, state);

    wcFileFree(program);

    return returnStatus;
}
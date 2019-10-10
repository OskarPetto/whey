#include <stdio.h>
#include <getopt.h>
#include "../Whey.h"

#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>

#define DEFAULT_STACK_SIZE 100000
#define DEFAULT_MEMORY_SIZE 500000

int main(int argc, char **argv) {

    char opt;
    uint8_t debug = 0;
    uint32_t stackSize = DEFAULT_STACK_SIZE;
    uint32_t memorySize = DEFAULT_MEMORY_SIZE;
    int64_t temp;

    while((opt = getopt(argc, argv, "s:m:d")) != -1)  
    {  
        switch (opt)
        {
            case 's':
                temp = strtol(optarg, NULL, 10);
                if (temp < 0)
                {
                    fprintf(stderr, "Call stack size %"PRId64" must be a postive integer.\n", temp);
                    return 1;
                }
                stackSize = temp;
                break;

            case 'm':
                temp = strtol(optarg, NULL, 10);
                if (temp < 0)
                {
                    fprintf(stderr, "Gc-memory size %"PRId64" must be a postive integer.\n", temp);
                    return 1;
                }
                memorySize = temp;
                break;

            case 'd':
                debug = 1;
                break;
            default:
                fprintf(stderr, "Unexpected option %c.\n", opt);
                return 1;
        }
    }

    if (argc - optind != 1) {
        fprintf(stderr, "One filename must be given.\n");
        return 1;
    }

    wheyRun(argv[optind], stackSize, memorySize, debug);

    return 0; // should never be reached
}
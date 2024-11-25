#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "consistent.h"

int main(int argc, char *argv[])
{
    int option;
    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"consistent", required_argument, 0, 'c'},
            {"splitting", required_argument, 0, 's'},
            {"parallel", no_argument, 0, 'p'},
            {0, 0, 0, 0}};

        option = getopt_long(argc, argv, "c:s:p", long_options, &option_index);
        if (option == -1)
            break;

        switch (option) {
        case 'c': {
            errno = 0;
            char *endptr;
            long value = strtol(optarg, &endptr, 10);
            if (errno != 0 || *endptr != '\0') {
                printf("Invalid integer for 'consistent': %s\n", optarg);
            } else {
                printf("Option 'consistent' called with argument: %ld\n", value);
            }
            perform_integration(value);
            break;
        }
        case 's': {
            errno = 0;
            char *endptr;
            long value = strtol(optarg, &endptr, 10);
            if (errno != 0 || *endptr != '\0') {
                printf("Invalid integer for 'splitting': %s\n", optarg);
            } else {
                printf("Option 'splitting' called with argument: %ld\n", value);
            }
            break;
        }
        case 'p':
            printf("Option 'parallel' called\n");
            break;
        case '?':
            break;
        default:
            printf("?? getopt returned undefined symbol 0%o ??\n", option);
        }
    }

    if (optind < argc) {
        printf("Non-option arguments: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    return 0;
}


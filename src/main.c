#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "consistent.h"
#include "function.h"


double (*select_function())(double) 
{
    double (*selected_function)(double) = NULL;

    int choice;
    printf("Choose a function to integrate:\n");
    printf("1. x^2 + e^x\n   ----------\n   x^3 + 3e^x\n\n");
    printf("2. x*arctg(4x)\n\n");
    printf("3.      (x)        (x)\n   sin^2(-) * cos^2(-)\n        (4)        (4)\n\n");
    printf("4.    1\n   ------ + 2 * x^(1/2)\n   x^(2/3)\n\n");
    printf("5. x^3 + 2x^2 - 5x + 7\n   -------------------\n     x^3 - 2x^2 + x\n\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);

    switch (choice) {
        case func_1:
            selected_function = f1;
            break;
        case func_2:
            selected_function = f2;
            break;
        case func_3:
            selected_function = f3;
            break;
        case func_4:
            selected_function = f4;
            break;
        case func_5:
            selected_function = f5;
            break;
        default:
            printf("Invalid choice.\n");
            return NULL;
    }

    if (selected_function == NULL) {
        printf("No function selected.\n");
        return NULL;
    }

    return selected_function;
}

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
            double (*func)(double) = select_function();
            perform_integration(value, func);
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


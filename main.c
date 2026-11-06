#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"
#include "memory.h"

int CLIInputHandler(bool handlinBool) {
    int input = 0;

    if (handlinBool == true) {
        printf("Number: ");
        scanf("%d", &input);
    } else {
        printf("Method number (0 is =; 1 is +; 2 is -; 3 is *; 4 is /; 10 is (; 20 is )): ");
        scanf("%d", &input);
        // brackets handling
        if (input == 10 || input == 20) {
            int temp = 0;
            printf("Method number (0 is =; 1 is +; 2 is -; 3 is *; 4 is /): ");
            scanf("%d", &temp);
            input += temp;
        }
    }

    return input;
}

int main() {
    // Starter variables
    int capacity = 4;
    int *input = NULL;
    int fullness = 0;
    bool number = true;

    // dynamic memory allocation
    input = newMemoryAllocate(input, capacity);
    if (input == NULL) {
        return(1);
    }

    // CLI input cycle
    while (1)
    {
        // free memory check
        if (fullness >= capacity) {
            // dynamic memory allocation
            capacity*=2;
            if (capacity > 32) {
                break;
            }
            input = newMemoryAllocate(input, capacity);
            if (input == NULL) {
                return(1);
            }
        }

        // input handling
        input[fullness] = CLIInputHandler(number);
        if (number == false && input[fullness] == 0) {
            break;
        }

        // cycle ending
        fullness++;
        number = !number;
    }
    
    // test equasion handler
    float resoult = calculate(input, fullness);
    
    printf("The resoult is %.2f. \n", resoult);

    // Free allocated memory
    free(input);
    //default succesful return
    return(0);
}
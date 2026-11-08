#include "calculator.h"
#include "memory.h"
#include <stdio.h>

int* listReWriter(int* list, int length, int middleIndex) {
    //deleting 2 items from list, with the middle index
    int *temp = NULL;
    temp = newMemoryAllocate(temp, (length - 2));
    for (int i = 0; i < length; i++)
    {
        if (i < middleIndex-1) {
            temp[i] = list[i];
        } else if (i == middleIndex) {
            temp[i-1] = list[i];
        } else if (i > middleIndex+1)
        {
            temp[i-2] = list[i];
        }
    }
    list = temp;
    free(temp);
    return(list);
}

float bracketsHandler(int index, int* list, int lenght) {
    // variable for system
    float resoult = 0.0f;
    int *temp = NULL;
    bool number = true;
    int l = 0;

    // dynamic memory allocation
    temp = newMemoryAllocate(temp, lenght);
    if (temp == NULL) {
        return(1);
    }

    // system body
    printf("Brackets Calculation!\n");
    for (int i = index; i <= lenght; i++)
    {
        if (number == false && list[i] >= 20) {
            resoult = calculate(temp, l+1);
            return(resoult);
        } else if (i == lenght)
        {
            // ERROR
            printf("Unclosed brackets ERROR\n");
            return(0);
        } else {
            temp[l] = list[i];
        }

        // loopend
        l++;
        number = !number;
    }
    
    //func end return
    return(resoult);
}

float calculate(int* list, int lenght) {
    // variables for system
    bool brackets = false;

    // watcher
    printf("\n\n");
    for (int i = 0; i < lenght; i++)
    {
        printf("%d\n", list[i]);
    }
    printf("\n\n");
    
    // * / handler
    int operator = -1;
    bool number = false;
    float number1 = 0.0f;

    for (int i = 0; i < lenght; i++)
    {
        if (number == false) {
            // default case
            if (list[i] == 3) {
                // calculate the * and replace it
                list[i] = list[i-1] * list[i+1];
                list = listReWriter(list,lenght,i);
                lenght -= 2;
            }
            if (list[i] == 4) {
                // calculate the / and replace it
                list[i] = list[i-1] / list[i+1];
                list = listReWriter(list,lenght,i);
                lenght -= 2;
            }
            // complex case
            if (list[i] == 13) {
                // calculate the * and replace it
                list[i + 1] = bracketsHandler(i, list, lenght);
                list[i] = 3;
                list[i + 2] = 19;
                list = listReWriter(list,lenght,i);
                lenght -= 2;
            }
            if (list[i] == 14) {
                // calculate the / and replace it
                list[i + 1] = bracketsHandler(i, list, lenght);
                list[i] = 4;
                list[i + 2] = 19;
                list = listReWriter(list,lenght,i);
                lenght -= 2;
            }
        }

        // loop setter
        number = !number;
    }

    //calculation handling
    number1 = list[0];
    operator = -1;
    number = false;
    for (int i = 1; i < lenght; i++)
    {
        printf("Calculating!\n");
        if (number == true) {
            if (brackets == true)
                if (operator >= 20) {
                    // end brackets
                    brackets = false;
                    operator -= 20;
                } 
            if (brackets == false) {
                if (operator < 20 && operator > 10) {
                    // open brackets
                    brackets = true;
                    operator -= 10;
                    switch (operator)
                        {
                        case 1:
                            number1 += bracketsHandler(i, list, lenght);
                            break;
                        case 2:
                            number1 -= bracketsHandler(i, list, lenght);
                            break;
                        case 9:
                            break;
                        default:
                            return(number1);
                    }
                } else {
                    switch (operator)
                        {
                            case 1:
                                number1 += list[i];
                                break;
                            case 2:
                                number1 -= list[i];
                                break;
                            default:
                                return(number1);
                        }
                }
            }
        } else {
            if (list[i] == 0)
            {
                return(number1);
            }
            
            operator = list[i];
        }
        // loop setter
        number = !number;
    }
    return(number1);
}

/*
Script that can take an input stream of integers and calculate their sum.

Created by Kevin Zhang
Spring 2018 Software Systems
Olin College of Engineering
*/
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

/*
adds numbers into the array, with various checks for compliance with valid input criteria.

nums: array that holds the inputted integers
input: the input the user typed
index: the current cell in the array that hasn't been modified yet
error: a flag used for error checking
*/
void add_numbers(int nums[], char *input, int *index, int *error){
    if (strlen(input) > 10 || atoi(input) == 0){
        if (strcmp(input,"0") == 0){
            nums[*index] = atoi(input);
            *index = *index + 1;
        }
        else{
            puts("Invalid input, TERMINATING.");
            *error = -1;
        }
    }
    else if (*index == 100){
        puts("Array already full, please find a sum.");
    }
    else{
        nums[*index] = atoi(input);
        *index = *index + 1;
    }

}

/*
calculates the sum of the array, with a check for max int thresholding

nums: the array to be summed and holds all inputted integers
sum: the variable that will hold the sum of the array
index: the variable that starts at the last index modified by the user input, so that the sum can be correctly calculated
*/
void find_sum(int nums[], int *sum, int index){
    for (int i=index-1; i>=0; i--){
        if ((INT_MAX - *sum) < nums[i]){
            puts("max sum exceeded, TERMINATING.");
            return;
        }
        *sum += nums[i];
    }
    printf("The sum of your inputs is %d\n", *sum);
}

/*
the main function that allows the user to continue entering valid numbers until EOF, at which then it attempts to calculate those numbers' sum
*/
int main(){
    int numbers[100];
    int index = 0;
    int error = 0;
    int sum = 0;
    char input[11];

    while (scanf("%s", input) != EOF){
        add_numbers(numbers, input, &index, &error);
        if (error == -1){
            break;
        }
    }
    if (error != -1){
        find_sum(numbers, &sum, index);
    }

    return 0;


}

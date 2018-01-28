/*
Exercise code meant to take in a card name from a standard deck
and then change a count value accordingly to a basic set of rules

Borrowed from page 37 of Head First C by Griffith and Griffith
Edited by Kevin Zhang
Spring 2018 Software Systems
Olin College of Engineering
*/

#include <stdio.h>
#include <stdlib.h>


/*
gets the inputted card name and puts it in card_name,
truncates just to two chars

prompt: display question to ask for input
card_name: variable that stores the input
*/
void get_card_name(char *prompt, char *card_name){
    puts(prompt);
    scanf("%2s", card_name);

}


/*
uses the input card name to derive a value, based on cases

card_name: the input card name from get_card_name()
val: the output value obtained from the card name and the below
set of case rules
*/
void get_val(char *card_name, int *val){
    switch(card_name[0]){
      case 'K':
      case 'Q':
      case 'J':
        *val = 10;
        break;
      case 'A':
        *val = 11;
        break;
      case 'X':
        *val = -1;
        break;
      default:
      {
        *val = atoi(card_name);
        if ((*val < 1) || (*val > 10)){
          puts("I don't understand that value!");
          *val = -1;
        }
      }
    }
}


/*
uses val to change the count variable based on what range
val falls into on the number line
prints count to show its current value

val: the latest val obtained from get_val()
count: the count variable to be updated by val according
to val's value
*/
void change_count(int *val, int *count){
    if ((*val > 2) && (*val < 7)){
      *count = *count + 1;
    }
    else if (*val == 10){
      *count = *count - 1;
    }
    printf("Current count: %i\n", *count);
}


/*the main function, which puts the three functions above together*/
int main() {
    char card_name[3];
    int count = 0;
    int val = 0;
    while(card_name[0]!= 'X'){
      get_card_name("Enter the card_name: ", card_name);
      get_val(card_name, &val);
      if (val == -1){ /*small check for invalid or terminating signals*/
        continue;
      }
      change_count(&val, &count);
    }
    return 0;
}

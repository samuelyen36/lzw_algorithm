#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct code_entry{
    char *str;
    char *code;
    struct code_entry *next;
};

struct code_entry *head;  //dictionary of lzw code, using the data structure of linked list

char *lzw(char *input); //constructing the dictionary
int search_dictionary(char a,char b);   //return the index of first match of char a and b. If no match is found, return -1.
int add_entry_to_dictionary(char *str); //add an entry to the dictionary.

int main(void){
    char *input = "abcdefdfkljkldsajfltjikrtwealkfdjslk";
    
    return 0;
}


char *lzw(char *input){
    int current_head=0;
    char *output = malloc(1000);
    for(;current_head < strlen(input);current_head++){

    }
    return output;
}
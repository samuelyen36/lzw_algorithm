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
int search_dictionary(char *a,char b);   //return the index of first match of char a and b. If no match is found, return -1.
int add_entry_to_dictionary(char *str,int dec); //add an entry to the dictionary, we convert the decimal number inside and use it as the code for that string.
char *convert_binary(int num);
char *got_the_code(int index);  //output the code of the specific one.

int main(void){
    char *input = "abcdefdfkljkldsajfltjikrtwealkfdjslk";
    
    return 0;
}


char *lzw(char *input){
    int current_head;
    char tmp[100]="\0";    //known as a
    char next;
    char *output = malloc(1000);    //coded version
    int dictionary_entry=0;
    int search_res;
    int dec=0;

    for(tmp[0] = input[0], current_head=0 ;current_head < strlen(input)-1;current_head++){
        next=input[current_head];
        search_res=search_dictionary(tmp,next); //store that what is the coded version of tmp string.
        if(search_res != -1){  //still hit the search
            tmp[strlen(tmp)] = next;
            //tmp = strcat(tmp,next);
            continue;
        }

        else{
            add_entry_to_dictionary(tmp,dec);
            output=strcat(output,got_the_code(search_res));
            dec++;
            strcpy(tmp,"\0");   //restore the tmp string which is already stored to the dictionary.
        }

        return output;
    }
}

char *convert_binary(int num){
    char *binaryNum=malloc(8);  //8 bit is enough for our implementation 
    int i = 0; 

    while (num > 0) { 
        binaryNum[i] = (num % 2) - '0'; 
        num = num / 2; 
        i++; 
    } 

    return binaryNum;
}
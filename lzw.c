#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct code_entry{
    char *str;
    char *code;
    struct code_entry *next;
};

struct code_entry *head=NULL;  //dictionary of lzw code, using the data structure of linked list
int dec = 0;

char *lzw(char *input); //constructing the dictionary
int search_dictionary(char *a,char b);   //return the index of first match of char a and b. If no match is found, return -1.
int add_entry_to_dictionary(char *str,char c,int dec); //add an entry to the dictionary, we convert the decimal number inside and use it as the code for that string.
char *convert_binary(int num);
char *got_the_code(char *tmp);  //output the code of the specific one.
void init_dic();
void dump_dic();

int main(void){
    char *input = "abcdncvbncvbn";
    init_dic();

    printf("%s\n",lzw(input));
    dump_dic();
    return 0;
}


char *lzw(char *input){
    int current_head;
    char tmp[100] = "\0";    //known as a
    char next;
    char *output = malloc(100000);    //coded version
    strcpy(output,"\0");
    int dictionary_entry = 0;
    int search_res;
    

    for(tmp[0] = input[0], current_head=0 ;current_head < strlen(input)-1;current_head++){
        next = input[current_head+1];
        search_res=search_dictionary(tmp,next); //store that what is the coded version of tmp string.
        if(search_res != -1){  //still hit the search
            printf("search hit\n");
            tmp[strlen(tmp)] = next;
            //tmp = strcat(tmp,next);
            continue;
        }

        else{
            printf("going to add one word\n");
            add_entry_to_dictionary(tmp,next,dec);
            char *x=got_the_code(tmp);
            printf("%s\t%s\n",output,x);
            strncat(output,x,strlen(x)); //encoded content
            dec++;
            memset(tmp,0,100);   //restore the tmp string which is already stored to the dictionary.
            tmp[0] = input[current_head+1];
            printf("\t\t%s",tmp);
        }
    }
    return output;
}

char *convert_binary(int num){
    char *binaryNum=malloc(8);  //8 bit is enough for our implementation 
    //strcpy(binaryNum,"\0");
    memset(binaryNum,0,8);
    int i = 0; 

    while (num > 0) { 
        binaryNum[i] = (num % 2) - 0 + '0'; 
        num = num / 2; 
        i++; 
    }

    return binaryNum;
}

int search_dictionary(char *a,char b){
    printf("enter search\n");
    char *concated = malloc(strlen(a)+2);
    strncpy(concated,a,strlen(a));
    concated[strlen(a)] = b;
    concated[strlen(a)+1]='\0';
    //printf("the string to be search is %s",concated);
    for(struct code_entry *iterator=head; iterator!=NULL; iterator=iterator->next){
        if(iterator==NULL){
            break;
        }
        //printf("%s",iterator->str);
        if(strncmp(concated,iterator->str,strlen(a)+2)==0){  //comparison is matched
            free(concated);
            return 1;
        }
        else{
            continue;
        }
    } 
    free(concated);
    //printf("not found\n");
    return -1;
}

int add_entry_to_dictionary(char *str,char c,int dec){
    if(head==NULL){
        head = malloc(sizeof(struct code_entry));
        head->str = malloc(strlen(str+2));
        strcpy(head->str,str);
        head->str[strlen(str)] = c;
        head->str[strlen(str)+1] = '\0';
        //head->str = str;
        head->code = convert_binary(dec);
        head->next = NULL;
        printf("added %s%c\n",str,c);
    }
    else{
        struct code_entry *iterator = head;
        struct code_entry *new;
        while(iterator->next != NULL){
            iterator = iterator->next;
        }
        new = malloc(sizeof(struct code_entry));
        new->str = malloc(strlen(str+2));
        strcpy(new->str,str);
        new->str[strlen(str)] = c;
        new->str[strlen(str)+1] = '\0';
        //new->str = str;
        new->code = convert_binary(dec);
        new->next = NULL;
        iterator->next = new;
        printf("added %s%c\n",str,c);
    }
}

char *got_the_code(char *tmp){
    struct code_entry *iterator = head;
    for(; iterator!=NULL; iterator = iterator->next){
        if(iterator==NULL)  break;
        //printf("%s\t%s\n",tmp,iterator->str);
        if(strcmp(tmp,iterator->str)==0){
            return iterator->code;
        }
    }
    return NULL;
}

void init_dic(){    //add a-z to dictionary
    for (int i=0; i < 'z'-'a';i++){
        if(head==NULL){
            head = malloc(sizeof(struct code_entry));
            head->str = malloc(2);
            head->str[0]=i+'a';
            head->str[1] = '\0';
            //head->str = str;
            head->code = convert_binary(dec);
            dec++;
            head->next = NULL;
            printf("added %c\n",i+'a');
        }
        else{
            struct code_entry *iterator = head;
            struct code_entry *new;
            while(iterator->next != NULL){
                iterator = iterator->next;
            }
            new = malloc(sizeof(struct code_entry));
            new->str = malloc(2);
            new->str[0]=i+'a';
            new->str[1] = '\0';
            //new->str = str;
            new->code = convert_binary(dec);
            dec++;
            new->next = NULL;
            iterator->next = new;
            printf("added %c\n",i+'a');
        }
    }
}

void dump_dic(){
    for (struct code_entry *idx = head; idx!=NULL; idx = idx->next){
        printf("%s,%s\n",idx->str,idx->code);
    }
}
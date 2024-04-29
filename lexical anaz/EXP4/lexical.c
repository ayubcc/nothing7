/*
                                                NAME: PATEL MUSKAN KASIM SHAH.
                                                ROLL NO: 22DCO04
                                                BATCH: 01
                                                SEMESTER: 6
                                                DATE: 21-03-2024
                                                
                                                
                           EXPERIMENT 4
            AIM: WRITE A PROGRAM FOR LEXICAL ANALYZER
            
*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 
int isKeyword(char buffer[]){
char keywords[32][10] = {"auto","break","case","char","const","continue","default",
"do","double","else","enum","extern","float","for","goto",
"if","int","long","register","return","short","signed",
"sizeof","static","struct","switch","typedef","union",
"unsigned","void","volatile","while"};
int i, flag = 0;
for(i = 0; i < 32; ++i){
if(strcmp(keywords[i], buffer) == 0){
flag = 1;
break;
}
}
return flag;
}
 
int main(){
char ch, buffer[15], operators[] = "+-*/%=";
FILE *fp;
int i,j=0;
fp = fopen("program.txt","r");
if(fp == NULL){
printf("error while opening the file\n");
exit(0);
}
while((ch = fgetc(fp)) != EOF){
   for(i = 0; i < 6; ++i){
   if(ch == operators[i])
   printf("%c is operator\n", ch);
   }
  
   if(isalnum(ch)){
   buffer[j++] = ch;
   }
   else if((ch == ' ' || ch == '\n') && (j != 0)){
   buffer[j] = '\0';
   j = 0;
     
   if(isKeyword(buffer) == 1)
   printf("%s is keyword\n", buffer);
   else
   printf("%s is indentifier\n", buffer);
   }
  
}
fclose(fp);
return 0;
}



//      OUTPUT
// aiktc@aiktc-OptiPlex-3046:~/Desktop/22DCO04$ gcc lexical.c
// aiktc@aiktc-OptiPlex-3046:~/Desktop/22DCO04$ ./a.out
// Void is indentifier
// main is indentifier
// int is keyword
// a is indentifier
// b is indentifier
// c is indentifier
// c is indentifier
// = is operator
// a is indentifier
// + is operator
// b is indentifier
// include is indentifier
// stdioh is indentifier
// int is keyword
// main is indentifier
// printfHello is indentifier
// World is indentifier
// return is keyword
// 0 is indentifier

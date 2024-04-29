/*
                                                NAME: PATEL MUSKAN KASIM SHAH.
                                                ROLL NO: 22DCO04
                                                BATCH: 01
                                                SEMESTER: 6
                                                DATE: 21-03-2024
                                                
                                                
                           EXPERIMENT 5
            AIM: WRITE A PROGRAM FOR Parcer
            
*/



#include <stdbool.h>
#include <stdio.h>
#include <string.h>
  
// Function to parse the HTML code
void parser(char* S)
{
    // Store the length of the
    // input string
    int n = strlen(S);
    int start = 0, end = 0;
    int i, j;
  
    // Traverse the string
    for (i = 0; i < n; i++) {
        // If S[i] is '>', update
        // start to i+1 and break
        if (S[i] == '>') {
            start = i + 1;
            break;
        }
    }
  
    // Remove the blank spaces
    while (S[start] == ' ') {
        start++;
    }
  
    // Traverse the string
    for (i = start; i < n; i++) {
        // If S[i] is '<', update
        // end to i-1 and break
        if (S[i] == '<') {
            end = i - 1;
            break;
        }
    }
  
    // Print the characters in the
    // range [start, end]
    for (j = start; j <= end; j++) {
        printf("%c", S[j]);
    }
  
    printf("\n");
}
  
// Driver Code
int main()
{
    // Given Input
    char input1[] = "<h1>This is a statement</h1>";
    char input2[] = "<h1>         This is a statement with some spaces</h1>";
    char input3[] = "<p> This is a statement with some @ #$ ., / special characters</p>         ";
  
    printf("Parsed Statements:\n");
  
    // Function Call
    parser(input1);
    parser(input2);
    parser(input3);
  
    return 0;
}

// OutPut:
// aiktc@aiktc-OptiPlex-3046:~/Desktop/22DCO04$ gcc Parser.c
// aiktc@aiktc-OptiPlex-3046:~/Desktop/22DCO04$ ./a.out
// Parsed Statements:
// This is a statement
// This is a statement with some spaces
// This is a statement with some @ #$ ., / special characters

/*
                                                NAME: PATEL MUSKAN KASIM SHAH.
                                                ROLL NO: 22DCO04
                                                BATCH: 01
                                                SEMESTER: 6
                                                
                                                
                                                
                           EXPERIMENT 3
            AIM: WRITE A PROGRAM FOR TWO PASS MACRO PROCESSOR

"""

 *  Desciption: Two pass macro processor.
 *      Pass one: Set the MDT and MNT data structures
 *      Pass two: Replace the calls with actual definitions.
 *
 *  To compile:
 *      clang macro.c
 *  or:
 *      gcc macro.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MAX_MACROS 5

int no_of_macros;
mnt_t mnt[MAX_MACROS];
mdt_t mdt[MAX_MACROS];
ala_t ala;

// Processing of a macro definition
void pass_one(FILE *file)
{
    char *line = NULL;
    size_t len = 0;

    int i = 0;

    while (getline(&line, &len, file) != -1) {
        if (contains(line, "MACRO")) {

            // Read the next line
            if (getline(&line, &len, file) == -1) {
                exit(1);
            }

            // get the name of macro
            char *macro_name = get_macro_name(line);

            //get the arguments in the macro
            char **argv = gets_args(macro_name);

            // inset it all in the Macro name table
            insert_mnt((mnt + i), macro_name, count(argv), i);

            // insert in the Macro definition table
            insert_mdt((mdt + i), i, definition(argv, file));

            i++;
        }
        no_of_macros = i;
    }
}

// Macro expansion
void pass_two(FILE *input)
{
    FILE *output = fopen("output.asm", "w");
    char *line = NULL;
    size_t len;

    bool is_macro_definition = false; 
    while (getline(&line, &len, input) != -1) {
        if (contains(line, "MACRO")) {
            fprintf(output, "%s", line);
            is_macro_definition = true;
        } else if (is_macro_definition || !is_macro_invocation(mnt, no_of_macros, line)) {
            fprintf(output, "%s", line);
            is_macro_definition = false;
        } else {
            char *macro_name = get_macro_name(line);
            char *definiton = get_def(mnt,mdt, macro_name);
            char **args = gets_args(macro_name);

            insert_ala(&ala, args);

            // Pop the `MEND` keyword (length: 4) at the end of the file
            definiton[strlen(definiton) - 4] = '\0';
            char *word = strtok(definiton, " ");

            while (word != NULL) {
                //printf("%s", word);
                if (word[0] == '#') {
                    word++;
                    char *arg = ala.actual[atoi(word) - 1];
                    fprintf(output, "%s", arg);
                    if (word[strlen(word) - 1] == ',') {
                        fprintf(output, "%s", ", ");
                    }
                } else {
                    fprintf(output, "%s ", word);
                }
                word =strtok(NULL, " ");
            }       
            fprintf(output, "%s", "\n");
        }
    }

    fclose(output);
}


int main(void)
{
    FILE *input = fopen("input.asm", "r");
    if (input == NULL) {
        printf("Target file: `input.asm` not found in the current directory\n");
        return 1;
    }

    printf("Pass one in progress.\n");
    pass_one(input);
    printf("Pass one completed.\n");
    fclose(input);
    
    display_mnt_mdt(mnt, mdt, no_of_macros);

    input = fopen("input.asm", "r");

    printf("Pass two in progress\n");
    pass_two(input);
    printf("Pass two completed.\n");

    fclose(input);

    return 0;
}
// output:
// Pass one in progress.
// Pass one completed.
// =========================| MNT |=========================
// ---------------------------------------------------------
// Name	Param	Index
// ---------------------------------------------------------
// ADD1	2	0
// ---------------------------------------------------------


// =========================| MDT |=========================
// ---------------------------------------------------------
// Definition		Index
// ---------------------------------------------------------
// LOAD #1 
// ADD #2 
// STORE #1 
// MEND 
 
// ADD1 N1, N2 
 
// MACRO 
// MUL1 &arg3, &arg4 
// MOV A, 00 
// MOV C, &arg4 
// Repeat: ADD &arg3 
// JNZ Repeat 
// MEND 
 
// MUL1 N3, N4			0
// ---------------------------------------------------------


// Pass two in progress
// Pass two completed.

/*
NAME: PATEL MUSKAN KASIM SHAH.
ROLL NUMBER: 22DCO04
BATCH: 01

                       AIM: IMPLEMENTATION OF PASS-2 ASSEMBLER.

                          EXPERIMENMT NO. :- 02

                                                                                            
*/

// Program:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Opcode // This node is used for Hashing using Chaining
{
    char name[10];
    char code[35];
    char format[5];
    struct Opcode *next;
};
struct Symbol // Symbol Table is made using Linked List to save space
{
    char name[50];
    int add;
    struct Symbol *next;
};
typedef struct Opcode Opcode;
typedef struct Symbol Symbol;

Symbol *head = NULL;

Opcode *hash_table[13] = {NULL};
void reverseArray(int arr[], int start, int end)
{
    int temp;
    while (start < end)
    {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}
int *conBin(int num) // function to convert in binary
{
    int t;
    int i, j;
    int *bin;
    bin = (int *)malloc(10 * sizeof(int));
    for (i = 0; i < 10; i++)
    {
        bin[i] = 0;
    }
    i = 9;
    t = num;
    while (t != 0)
    {
        bin[i--] = t % 2;
        t = t / 2;
    }
    return bin;
}

char *convertTo5BitBinaryString(int decimal) // This decimal is between 0 and 31
{
    printf("bitbinary function receives %d\n", decimal);
    char *str = (char *)malloc(5 * sizeof(char));
    int d[5] = {0};
    int i = 0, j = 0;
    while (decimal > 0)
    {
        d[i] = decimal % 2;
        i++;
        decimal = decimal / 2;
    }
    int size = i;
    int k = 0;
    int s = 0;

    reverseArray(d, 0, 4);
    for (s = 0; s < 5; s++)
    {
        printf("%d", d[s]);
        str[s] = d[s] + '0';
    }
    printf("\n");

    printf("%s", str);
    return str;
}
/*******************************************************************
    HASH TABLE IS USED TO STORE THE OPCODES BEING READ
*******************************************************************/
int getHashIndex(char name[])
{
    int sum = 0, i = 0;
    while (name[i] != '\0')
    {
        sum += name[i++];
    }
    return sum % 13;
}
void insertAtIndex(Opcode *Node, int index)
{
    if (hash_table[index] == NULL) // boundary condition
    {
        hash_table[index] = Node;
        Node->next = NULL;
    }
    else
    {
        Opcode *temp = hash_table[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = Node;
        Node->next = NULL;
    }
}
void insertIntoHashMap(Opcode *Node)
{
    int index = getHashIndex(Node->name);
    insertAtIndex(Node, index);
}
int *getAddressCode(char *temp)
{
    Symbol *t = head;
    int *val;
    int num;
    while (t != NULL)
    {
        if (!strcmp(temp, t->name))
        {
            num = t->add;
            break;
        }
        t = t->next;
    }
    val = conBin(num);
    return val;
}
char *getRegisterCode(char *temp)
{
    char *s;
    if (strcmp(temp, "R0") == 0)
    {
        s = "00000";
    }
    else if (strcmp(temp, "R1") == 0)
        s = "00001";
    else if (strcmp(temp, "R2") == 0)
        s = "00010";
    else if (strcmp(temp, "R3") == 0)
        s = "00011";
    else if (strcmp(temp, "R4") == 0)
        s = "00100";
    else if (strcmp(temp, "R5") == 0)
        s = "00101";
    else if (strcmp(temp, "R6") == 0)
        s = "00110";
    else if (strcmp(temp, "R7") == 0)
        s = "00111";
    else if (strcmp(temp, "R8") == 0)
        s = "01000";
    else if (strcmp(temp, "R9") == 0)
        s = "01001";
    else if (strcmp(temp, "R10") == 0)
        s = "01010";
    else if (strcmp(temp, "R11") == 0)
        s = "01011";
    else if (strcmp(temp, "R12") == 0)
        s = "01100";
    else if (strcmp(temp, "R13") == 0)
        s = "01101";
    else if (strcmp(temp, "R14") == 0)
        s = "01110";
    else if (strcmp(temp, "R15") == 0)
        s = "01111";
    else if (strcmp(temp, "A1") == 0)
        s = "10000";
    else if (strcmp(temp, "A2") == 0)
        s = "10001";
    else if (strcmp(temp, "A3") == 0)
        s = "10010";
    else if (strcmp(temp, "A4") == 0)
        s = "10011";
    else if (strcmp(temp, "port0") == 0)
        s = "10100";
    else if (strcmp(temp, "port1") == 0)
        s = "10101";
    return s;
}
char *getConstantCode(int temp)
{
    return convertTo5BitBinaryString(temp);
}
struct Opcode *getOpcodeNode(char *op)
{
    Opcode *temp = NULL;
    int index = getHashIndex(op); // get hash-index for the opcode in the hash table
    if (hash_table[index] == NULL)
    {
        printf("Wrong Opcode");
        return NULL;
    }

    else
    {
        temp = hash_table[index];
        while (strcmp(temp->name, op) != 0 && temp != NULL) // loop until the opcode is not found or the temp pointer not pointing to NULL
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            printf("Opcode not found!");
            return NULL;
        }
        else
        {
            return temp;
        }
    }
}
char *getOpcodeFormat(Opcode *temp)
{
    return temp->format;
}

int main()
{
    FILE *input_opcode;
    FILE *output_machine_code;
    FILE *input_instructions;
    int ilc = 0; // Instruction Location Counter
    int base = 0;
    char c, c2, c3, temp;
    char opcode[100];
    char machine_code[100];
    char format[5];

    input_opcode = fopen("input_opcode.txt", "r+"); // input_opcode contains a list of opcodes followed by their format and mac.code
    if (input_opcode == NULL)
        printf("FILE OPENING PROBLEM");
    char test1[50];
    do
    {
        c = fscanf(input_opcode, "%s", opcode);        // Assuming to get opcode as a string in opcode array
        c2 = fscanf(input_opcode, "%s", machine_code); // Assuming to get a the integer as a string in machine_code array
        c3 = fscanf(input_opcode, "%s", format);
        // now we will create node of each string
        struct Opcode *Node = (struct Opcode *)malloc(sizeof(Opcode));

        strcpy(Node->name, opcode);
        // Name of the opcode is fed
        strcpy(Node->code, machine_code);
        // Machine code of the opcode is fed
        strcpy(Node->format, format);
        // Format of the opcode is fed
        //  printf("BEFORE INSERTING NAME:: %s ,CODE:: %s and format",Node->name,Node->code,Node->format);
        insertIntoHashMap(Node);

    } while (fgets(test1, sizeof test1, input_opcode) != NULL);

    // At this point we have a hash-map of Opcodes

    printf("Hash-map Created Successfully!\n");
    /*TEST:: PRINTING HASHTABLE with hashcode*/
    int i = 0;
    for (i = 0; i < 13; i++)
    {

        if (hash_table[i] != NULL)
        {

            Opcode *temp = hash_table[i];

            while (temp != NULL)
            {
                printf("NAME:: %s and CODE:: %s and format:: %s \n", temp->name, temp->code, temp->format);
                temp = temp->next;
            }
        }
    }
    printf("Now reading Opcodes and Converting them to machine codes\n");

    input_instructions = fopen("input_instructions.txt", "r+");
    output_machine_code = fopen("output_machine_code.txt", "w+");
    char k;
    char op[100];

    /***********************************************************************************************/
    /*First pass for generation of symbol table*/

    while (fgets(op, sizeof op, input_instructions) != NULL) /* read a line */
    {
        int l = 0;

        while (op[l + 1] != '\0')
        {
            if (op[l] == ':') // Its a label
            {
                Symbol *t;
                struct Symbol *temp = (struct Symbol *)malloc(sizeof(Symbol)); // dynamic memory allocation for a node of symbol
                int i = 0;
                for (; i < l; i++)
                    temp->name[i] = op[i];
                temp->name[i] = '\0';
                temp->add = ilc + 1 + base;
                temp->next = NULL;
                if (head == NULL) // boundary condition for implementing symbol table using linked list
                    head = temp;
                else // adding new symbol node to existing table of nodes
                {
                    t = head;
                    while (t->next != NULL)
                        t = t->next;
                    t->next = temp;
                }
                // handle label
            }
            l++;
        }
        ilc++;
    }
    fclose(input_instructions);

    /***********************************************************************************************/
    /*Second pass for generation of binary codes*/
    input_instructions = fopen("input_instructions.txt", "r+");
    int *binary;
    char test[100];
    int count;

    do
    {
        k = fscanf(input_instructions, "%s", op);
        printf("WORD SCANNED IS %s  \n", op);
        /*check if opcode or label*/
        int l = 0;
        while (op[l + 1] != '\0')
        {
            l++;
        }
        if (op[l] == ':') // Its a label
        {
            printf("Label Found!\n");
            fprintf(output_machine_code, "\n");
            // handle label
        }
        else
        {
            char temp[100];
            char temp2[100];
            char temp3[100];
            int temp4;
            // handle opcode and print corresponding machine code
            Opcode *current_node = getOpcodeNode(op);
            fprintf(output_machine_code, "%s", current_node->code); // print machine code of the opcode

            if (strcmp("z", getOpcodeFormat(current_node)) == 0) // ZERO OPERAND INSTRUCTION
            {
                fprintf(output_machine_code, "\n"); // Do nothing
            }
            else if (strcmp("r", getOpcodeFormat(current_node)) == 0) // ONE OPERAND REGISTER OPERAND INSTRUCTION
            {
                k = fscanf(input_instructions, "%s", temp); // read corresponding register code

                fprintf(output_machine_code, "%s", getRegisterCode(temp)); // write corresponding register code in binary
                fprintf(output_machine_code, "\n");
            }
            else if (strcmp("a", getOpcodeFormat(current_node)) == 0) // ONE OPERAND ADDRESS OPERAND INSTRUCTION
            {
                k = fscanf(input_instructions, "%s", temp);
                binary = getAddressCode(temp); // write corresponding address in binary
                for (count = 0; count < 10; count++)
                {
                    fprintf(output_machine_code, "%d", binary[count]);
                }
                fprintf(output_machine_code, "\n");
            }
            else if (strcmp("rr", getOpcodeFormat(current_node)) == 0) // TWO OPERAND REGISTER REGISTER OPERAND INSTRUCTION
            {
                // printf("inside two");
                k = fscanf(input_instructions, "%s", temp);
                k = fscanf(input_instructions, "%s", temp2);
                fprintf(output_machine_code, "%s", getRegisterCode(temp));
                fprintf(output_machine_code, "%s", getRegisterCode(temp2));
                fprintf(output_machine_code, "\n");
            }
            else if (strcmp("ri", getOpcodeFormat(current_node)) == 0) // TWO OPERAND REGISTER CONSTANT INSTRUCTION
            {
                k = fscanf(input_instructions, "%s", temp);
                k = fscanf(input_instructions, "%d", &temp4);
                fprintf(output_machine_code, "%s", getRegisterCode(temp));
                //  fprintf(output_machine_code,"%s",getConstantCode(temp4));
                binary = conBin(temp4);
                for (count = 0; count < 10; count++)
                {
                    fprintf(output_machine_code, "%d", binary[count]);
                }
                fprintf(output_machine_code, "\n");
            }
            else if (strcmp("rrr", getOpcodeFormat(current_node)) == 0) // THREE OPERAND REGISTER-REGISTER-REGISTER INSTRUCTION
            {
                k = fscanf(input_instructions, "%s", temp);
                k = fscanf(input_instructions, "%s", temp2);
                k = fscanf(input_instructions, "%s", temp3);
                fprintf(output_machine_code, "%s", getRegisterCode(temp));
                fprintf(output_machine_code, "%s", getRegisterCode(temp2));
                fprintf(output_machine_code, "%s", getRegisterCode(temp3));
                fprintf(output_machine_code, "\n");
            }
            else if (strcmp("rri", getOpcodeFormat(current_node)) == 0) // THREE OPERAND REGISTER-REGISTER-INTERMEDIATE INSTRUCTION
            {
                k = fscanf(input_instructions, "%s", temp);
                k = fscanf(input_instructions, "%s", temp2);
                k = fscanf(input_instructions, "%d", &temp4);
                fprintf(output_machine_code, "%s", getRegisterCode(temp));
                fprintf(output_machine_code, "%s", getRegisterCode(temp2));
                binary = conBin(temp4);
                for (count = 0; count < 10; count++)
                {
                    fprintf(output_machine_code, "%d", binary[count]);
                }
                fprintf(output_machine_code, "\n");
            }
        }

    } while (fgets(test, sizeof test, input_instructions) != NULL);
    printf("\n\nSymbol Table\n\n");
    fclose(input_instructions);
    fclose(output_machine_code);
    fclose(input_opcode);

    /*PRINT SYMBOL TABLE*/
    Symbol *p;
    p = head;
    FILE *f = fopen("symbol_table.txt", "w+");
    while (p != NULL)
    {
        printf("%s :: ", p->name);
        fprintf(f, "%s :: ", p->name);
        printf("%d\n", p->add);
        fprintf(f, "%d\n", p->add);
        p = p->next;
    }
    return 0;
}

/*
Output:

Hash-map Created Successfully!
NAME:: ORI and CODE:: 000000000110 and format:: rri
NAME:: NORI and CODE:: 000000001001 and format:: rri
NAME:: SUB and CODE:: 00000000101000001 and format:: rrr
NAME:: JLT and CODE:: 0000000010101000101000 and format:: a
NAME:: ADDI and CODE:: 000000000000 and format:: rri
NAME:: DIVI and CODE:: 000000000011 and format:: rri
NAME:: OUT and CODE:: 000000001010100010101101000 and format:: r
NAME:: RET and CODE:: 00000000101010001010110100100000 and format:: z
NAME:: XOR and CODE:: 00000000101000110 and format:: rrr
NAME:: NOTI and CODE:: 00000000101010000 and format:: ri
NAME:: LOAD and CODE:: 0000000010101000100100 and format:: rr
NAME:: EXIT and CODE:: 00000000101010001010110100100011 and format:: z
NAME:: AND and CODE:: 00000000101000100 and format:: rrr
NAME:: NAND and CODE:: 00000000101000111 and format:: rrr
NAME:: MOD and CODE:: 00000000101001000 and format:: rrr
NAME:: ARRI and CODE:: 00000000101001010 and format:: rrr
NAME:: MOVI and CODE:: 00000000101001101 and format:: ri
NAME:: CMP and CODE:: 0000000010101000100000 and format:: rr
NAME:: JEQ and CODE:: 0000000010101000100111 and format:: a
NAME:: LSHIFT and CODE:: 000000001010100010101100011 and format:: r
NAME:: MUL and CODE:: 00000000101000010 and format:: rrr
NAME:: CLR and CODE:: 000000001010100010101100010 and format:: r
NAME:: OR and CODE:: 00000000101000101 and format:: rrr
NAME:: NOR and CODE:: 00000000101001001 and format:: rrr
NAME:: POP and CODE:: 000000001010100010101100110 and format:: r
NAME:: ADD and CODE:: 00000000101000000 and format:: rrr
NAME:: DIV and CODE:: 00000000101000011 and format:: rrr
NAME:: NOT and CODE:: 0000000010101000100010 and format:: rr
NAME:: STORE and CODE:: 0000000010101000100101 and format:: rr
NAME:: SUBI and CODE:: 000000000001 and format:: rri
NAME:: MOV and CODE:: 0000000010101000100001 and format:: rr
NAME:: JGT and CODE:: 0000000010101000101001 and format:: a
NAME:: PUSH and CODE:: 000000001010100010101100101 and format:: r
NAME:: IN and CODE:: 000000001010100010101100111 and format:: r
NAME:: DEC and CODE:: 000000001010100010101100001 and format:: r
NAME:: RSHIFT and CODE:: 000000001010100010101100100 and format:: r
NAME:: MSF and CODE:: 00000000101010001010110100100001 and format:: z
NAME:: XORI and CODE:: 000000000111 and format:: rri
NAME:: ARRC and CODE:: 00000000101001011 and format:: rrr
NAME:: JMP and CODE:: 0000000010101000101010 and format:: a
NAME:: INC and CODE:: 000000001010100010101100000 and format:: r
NAME:: MODI and CODE:: 000000000100 and format:: rri
NAME:: ANDI and CODE:: 000000000101 and format:: rri
NAME:: NANDI and CODE:: 000000001000 and format:: rri
NAME:: CMPI and CODE:: 00000000101001100 and format:: ri
NAME:: ARRD and CODE:: 0000000010101000100011 and format:: rr
NAME:: CALL and CODE:: 0000000010101000100110 and format:: a
NAME:: HLT and CODE:: 00000000101010001010110100100010 and format:: z
NAME:: MULI and CODE:: 000000000010 and format:: rri
Now reading Opcodes and Converting them to machine codes
WORD SCANNED IS MOVI
WORD SCANNED IS MOVI
WORD SCANNED IS MOVI
WORD SCANNED IS MOVI
WORD SCANNED IS MOVI
WORD SCANNED IS MOVI
WORD SCANNED IS MOVI
WORD SCANNED IS P1:
Label Found!
WORD SCANNED IS CMP
WORD SCANNED IS JEQ
WORD SCANNED IS P2:
Label Found!
WORD SCANNED IS CMP
WORD SCANNED IS JEQ
WORD SCANNED IS P3:
Label Found!
WORD SCANNED IS CMP
WORD SCANNED IS JEQ
WORD SCANNED IS P4:
Label Found!
WORD SCANNED IS CMP
WORD SCANNED IS JEQ
WORD SCANNED IS P5:
Label Found!
WORD SCANNED IS CMP
WORD SCANNED IS JEQ
WORD SCANNED IS JMP
WORD SCANNED IS C1:
Label Found!
WORD SCANNED IS INC
WORD SCANNED IS JMP
WORD SCANNED IS C2:
Label Found!
WORD SCANNED IS INC
WORD SCANNED IS JMP
WORD SCANNED IS C3:
Label Found!
WORD SCANNED IS INC
WORD SCANNED IS JMP
WORD SCANNED IS C4:
Label Found!
WORD SCANNED IS INC
WORD SCANNED IS JMP
WORD SCANNED IS C5:
Label Found!
WORD SCANNED IS INC
WORD SCANNED IS HL:
Label Found!
WORD SCANNED IS MOVI
WORD SCANNED IS OUT
WORD SCANNED IS HLT


Symbol Table

P1 :: 8
P2 :: 11
P3 :: 14
P4 :: 17
P5 :: 20
C1 :: 24
C2 :: 27
C3 :: 30
C4 :: 33
C5 :: 36
HL :: 38

*/
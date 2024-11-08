 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void main() {
    FILE *source, *optab, *intermediate, *symtab, *length;
    source = fopen("source.txt", "r");
    optab = fopen("optab.txt", "r");
    intermediate = fopen("intermediate.txt", "w");
    symtab = fopen("symtab.txt", "w+");
    length = fopen("length.txt", "w");

    if (!source || !optab || !intermediate || !symtab || !length) {
        printf("Error: One or more files could not be opened.\n");
        return;
    }

    char label[20], opcode[20], operand[20], symtab_data[20], optab_data[20];
    int locctr = 0, starting_address = 0, program_length = 0;
    bool symbol_found, opcode_found;

    // Read the first line of the source file
    fscanf(source, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        starting_address = atoi(operand);
        locctr = starting_address;
        fprintf(intermediate, "%-8s %-8s %-8s\n", label, opcode, operand); // Align for START directive
    } else {
        locctr = 0;
    }
    fscanf(source, "%s %s %s", label, opcode, operand);

    while (strcmp(opcode, "END") != 0) {
        if (strcmp(label, "**") != 0) {    // searching label in symtab
            symbol_found = false;
            rewind(symtab);
            while (fscanf(symtab, "%s", symtab_data) ==  1) {
                if (strcmp(symtab_data, label) == 0) {
                    printf("Error: Duplicate symbol found: %s\n", label);
                    symbol_found = true;
                    break;
                }
            }
            if (!symbol_found) {
                 fprintf(symtab, "%s\t%d\n", label, locctr);
            }
        }

        opcode_found = false;
        rewind(optab);
        while (fscanf(optab, "%s", optab_data) == 1) {
            if (strcmp(optab_data, opcode) == 0) {
                opcode_found = true;
                break;
            }
        }

        // Write formatted output to intermediate file with consistent alignment
        fprintf(intermediate, "%-8d %-8s %-8s %-8s\n", locctr, label, opcode, operand);

        // Adjust location counter based on opcode
        if (opcode_found) {
            locctr += 3;
        } else if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        } else if (strcmp(opcode, "RESW") == 0) {
            locctr += 3 * atoi(operand);
        } else if (strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        } else if (strcmp(opcode, "BYTE") == 0) {
            locctr += strlen(operand) - 3;
        } else {
            printf("Error: Invalid operation code: %s\n", opcode);
        }

        // Read the next line of the source file
        fscanf(source, "%s %s %s", label, opcode, operand);
    }

    // Final line for END directive
    fprintf(intermediate, "%-8d %-8s %-8s %-8s\n", locctr, label, opcode, operand);
    program_length = locctr - starting_address;
    printf("Program length: %d\n", program_length);

    fclose(source);
    fclose(optab);
    fclose(intermediate);
    fclose(symtab);
    fclose(length);
}

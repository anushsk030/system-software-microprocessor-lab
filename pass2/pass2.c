
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    FILE *intermediate, *optab, *symtab, *output, *prgmlength, *objectcode;
    char opcode[20], operand[20], label[20], mneumonic[20], code[20], value[20], textRecord[70];
    int locctr, start, programLength, length = 0, textStartAddr;

    optab = fopen("optab.txt", "r");
    intermediate = fopen("intermediate.txt", "r");
    symtab = fopen("symtab.txt", "r");
    output = fopen("output.txt", "w");
    objectcode = fopen("objectcode.txt", "w");
    prgmlength = fopen("prgmlength.txt", "r");

    if (!optab || !intermediate || !symtab || !output) {
        printf("Error opening files\n");
        return;
    }

    fscanf(intermediate, "%s %s %s", label, opcode, operand);//1st line of intermediate
   printf("first input line read: %s %s %s\n", label, opcode, operand);
    fprintf(output, "     %-7s%-7s%-7s\n", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        fscanf(prgmlength, "%d", &programLength);
        start = atoi(operand);
        fprintf(objectcode, "H^%s^%06d^%06d\n", label, start, programLength);
    }

    fscanf(intermediate, "%d %s %s %s", &locctr, label, opcode, operand);//2nd line of intermediate
    textStartAddr = locctr;
    strcpy(textRecord, "");///cpy
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while (strcmp(opcode, "END") != 0) {
        char objectCode[10] = "";
        printf("Processing line: %d %s %s %s\n", locctr, label, opcode, operand);
        fprintf(output, "%d %-7s%-7s%-7s", locctr, label, opcode, operand);///print 2nd line

        if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'C' && operand[1] == '\'') {
                if (strcmp(operand, "C'EOF'") == 0) {
                    strcpy(objectCode, "454F46");//cpy
                } else {
                    for (int i = 2; i < strlen(operand) - 1; i++) {
                        sprintf(objectCode + strlen(objectCode), "%02X", operand[i]);//cpy
                    }
                }
            }
        } else if (strcmp(opcode, "WORD") == 0) {
            sprintf(objectCode, "%06d", atoi(operand));
        } else if (strcmp(opcode, "RESB") == 0) {
            // No object code for RESB
        } else if (strcmp(opcode, "RESW") == 0) {
            // No object code for RESW
        } else {
            rewind(optab);
            while (fscanf(optab, "%s %s", mneumonic, code) != EOF) {
                if (strcmp(opcode, mneumonic) == 0) {
                    strcpy(objectCode, code);
                    break;
                }
            }
            rewind(symtab);
            while (fscanf(symtab, "%s %s", label, value) != EOF) {
                if (strcmp(operand, label) == 0) {
                    sprintf(objectCode + strlen(objectCode), "%04d", atoi(value));
                    break;
                }
            }
        }

        printf("Object Code: %s\n", objectCode);
        fprintf(output, "%s\n", objectCode);

        if (length + strlen(objectCode) > 60) {
            fprintf(objectcode, "T^%06d^%02X^%s\n", textStartAddr, length / 2, textRecord);
            strcpy(textRecord, "");
            textStartAddr = locctr;
            length = 0;
        }

        if (strlen(objectCode) > 0) {
            strcat(textRecord, objectCode);
            strcat(textRecord, "^");
            length += strlen(objectCode);
        }
          
        fscanf(intermediate, "%d %s %s %s", &locctr, label, opcode, operand);
    }
       printf("Lerngth is  :%d",length);
    if (length > 0) {
         printf("Lerngth is  :%d",length);
        textRecord[strlen(textRecord) - 1] = '\0'; // Remove the last '^'
        fprintf(objectcode, "T^%06d^%02X^%s\n", textStartAddr, length/2, textRecord);
    }

    fprintf(output, "%d %-7s%-7s%-7s", locctr, label, opcode, operand);
    fprintf(objectcode, "E^%06d\n", start);

    fclose(intermediate);
    fclose(symtab);
    fclose(optab);
    fclose(output);
    fclose(prgmlength);
    printf("FINISHED EXECUTION!!!\n");
}

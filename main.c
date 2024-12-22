#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char label[20];
    int address;
} Label;

Label labels[100];  // Array to store labels and their addresses
int labelCount = 0;

void processInstruction(char *instruction, int address);

void processFile(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int address = 0x00400000;  // Starting address
    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL) {
        processInstruction(line, address);
        address += 4;  // Assuming each instruction is 4 bytes
    }

    fclose(fp);
}

void addLabel(char *label, int address) {
    strcpy(labels[labelCount].label, label);
    labels[labelCount++].address = address;
}

int getLabelAddress(char *label) {
    for (int i = 0; i < labelCount; i++) {
        if (strcmp(labels[i].label, label) == 0) {
            return labels[i].address;
        }
    }
    return -1;  // Label not found
}

void writeOutput(char *filename) {
    FILE *fp = fopen(strcat(filename, ".obj"), "w");
    if (fp == NULL) {
        printf("Error creating output file.\n");
        return;
    }

    // Iterate over labels and write them to the output file
    for (int i = 0; i < labelCount; i++) {
        fprintf(fp, "%s %X\n", labels[i].label, labels[i].address);
    }

    // Write other machine code to the output file
    // ...

    fclose(fp);
}

void processInstruction(char *instruction, int address) {
    // Tokenize instruction
    char *token = strtok(instruction, " \t\n");
    if (token == NULL)
        return;  // Empty line

    // Check for labels
    if (token[strlen(token) - 1] == ':') {
        addLabel(token, address);
        return;
    }

    // Handle other instructions based on their type (R, I, J)
    // I use placeholders for instruction types
    if (strcmp(token, "ADD") == 0) {
        // R-type instruction ADD
        // Generate machine code for ADD
        // ...

        // Write machine code to the output file
        // ...
    } else if (strcmp(token, "LW") == 0) {
        // I-type instruction LW
        // Generate machine code for LW
        // ...

        // Write machine code to the output file
        // ...
    } else if (strcmp(token, "JUMP") == 0) {
        // J-type instruction JUMP
        // Generate machine code for JUMP
        // ...

        // Write machine code to the output file
        // ...
    }
}

int main() {
    char filename[50];
    printf("Enter source code filename: ");
    scanf("%s", filename);

    processFile(filename);
    writeOutput(filename);

    printf("Assembler completed successfully.\n");
    return 0;
}

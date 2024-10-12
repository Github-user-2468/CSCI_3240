/******************************************************************
Program Name: Project1
Programmer: Karigan Stewart
Date: 09-17-24
Description: This program takes a filename as command line input 
and generates a hex dump on the file translating the ASCII chars
into their hexadecimal equilvalent 
******************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define CHUNK_SIZE 16  // Number of bytes per line in hex dump
#define GROUP_SIZE 2   // Number of bytes per group

//Hex dump prototype
void printHexDump(FILE *file);

int main(int argc, char *argv[]) {
    // Check for correct number of command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open the file specified by the command-line argument
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Print the hex dump of the file
    printHexDump(file);

    // Close the file
    fclose(file);

    return EXIT_SUCCESS;
}


// Function to print the hexadecimal and ASCII representation
void printHexDump(FILE *file) {
    unsigned char hexChar[CHUNK_SIZE];
    size_t bytesRead;
    unsigned int offset = 0;

    while ((bytesRead = fread(hexChar, 1, CHUNK_SIZE, file)) > 0) {
        // Print the offset in hexadecimal
        printf("%08x: ", offset);

      // Print the hex values of the hexChar with grouping
        for (size_t i = 0; i < CHUNK_SIZE; i++) {
            if (i < bytesRead) {
                printf("%02x", hexChar[i]);
            } else {
                printf("  ");  
            }

            // Add a space after every GROUP_SIZE bytes 
            if ((i % GROUP_SIZE == GROUP_SIZE - 1) && (i < CHUNK_SIZE - 1)) {
                printf(" ");
            }
        }

      // Print the ASCII representation
        printf("  ");
        for (size_t i = 0; i < bytesRead; i++) {
            if (isprint(hexChar[i])) {
                printf("%c", hexChar[i]);
            } else {
                printf(".");  // Replace unprintable characters with '.'
            }
        }

        printf("\n");  // New line after each chunk
        offset += CHUNK_SIZE;
    }
}

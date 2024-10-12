/*******************************************************************************
Name:lab4Problem1
Programmer: Karigan Stewart
Date:09-12-2024
description: this program is to read from a file and display the 
in an array of 11 character (10 chars per line)and print out the file using "."
for unprintable characters 
*******************************************************************************/
#include <stdio.h>
#include <ctype.h>  
#include <stdlib.h> 

#define ARRAY_SIZE 11  // 10 characters + 1 for \0

void processFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    // Checks if file has opened correctly 
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char arr[ARRAY_SIZE];   // Array to hold characters
    int index = 0;          // Index counter for array
    char ch;                // The character being read

    // If EOF hasn't been reached
    while ((ch = fgetc(file)) != EOF) {
        // If the index has reached its tenth character
        if (index == ARRAY_SIZE - 1) {
            arr[index] = '\0';          // Null terminate the string
            printf("%s\n", arr);
            index = 0;                  // Reset index for the next chunk
        }

        if (isprint(ch)) {
            arr[index++] = ch;         // If the char is printable
        } else {
            arr[index++] = '.';        // If the char is not printable
        }
    }

    // Print any remaining characters
    if (index > 0) {
        arr[index] = '\0';    // Null terminate the string
        printf("%s\n", arr);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please enter exactly 1 value.\n");
        return 1;
    }

    processFile(argv[1]);
    return 0;
}

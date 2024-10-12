/***************************************************************
Program Name: lab2Problem2.b
Programmer:Karigan Stewart
Date: 08/30/24
Description: This program is to gather user input to create
a patterned grid from 1 ti n
*************************************************************/

#include <stdio.h>
#include <stdlib.h>

// Prints the pattern based on the value user inputs
void PrintNumPattern(int n); 


int main(int argc, char *argv[]) {
    
    // Check if exactly one command line argument is provided
    if (argc != 2) {
        printf("Please enter exactly 1 value.\n");
        return 1;
    }

    int n = atoi(argv[1]);

    // Check if the value of n is within the 1 and 9
    if (n < 1 || n > 9) {
        printf("Error: The value of n must be between 1 and 9.\n");
        return 1;
    }

    // Function prints the pattern
    PrintNumPattern(n);
    return 0; 
}

/*********************************************************************
Description: This function is to display a patterned grid based on 
user input. In each row the numbers get smaller as you move from the 
left edge towards the center and then get bigger again as you move 
towards the right edge. The dimesion of grid is determined from
(2n-1) 
*********************************************************************/
void PrintNumPattern(int n) {
    int size = 2 * n - 1; // Size of the pattern

    // First half (including the middle row)
    for (int row = 0; row < n; row++) {                     // Loop through the rows from 0 to n-1
        for (int column = 0; column < size; column++) {     // Loop through the columns from 0 to size-1
            int num;
            if (column < row) {                 // If the column is less than the row, the number gets smaller as it moves left to right
                num = n - column;
            } else if (column < size - row) {   // If the column is within the bounds defined by the row, the number stays the same across the middle part of the row
                num = n - row;
            } else {                            // If the column is greater than size - row - 1, the begins increasing
                num = column - n + 2;
            }
            printf("%d ", num);       // Print the number
        }
        printf("\n");                 // Move to the next line
    }

    // Prints the second half
    for (int row = n - 2; row >= 0; row--) {    // Mirrors the 1st half of pattern
        for (int column = 0; column < size; column++) {
            int num;
            if (column < row) { 
                num = n - column;
            } else if (column < size - row) {
                num = n - row;
            } else {
                num = column - n + 2;
            }
            printf("%d ", num); // Print the number
        }
        printf("\n"); // Move to the next line
    }
}

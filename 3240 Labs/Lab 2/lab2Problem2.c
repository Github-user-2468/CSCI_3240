/***************************************************************
Program Name: lab2Problem2.c
Programmer:Karigan Stewart
Date: 08/30/24
Description: This program is to gather 2 numerical inputs
(n and r) from the user and is to calculate the permutation
and combination of the 2 given values
*************************************************************/
#include <stdio.h>
#include <stdlib.h>

// Function prototypes
long findfactorial(int num);
long findPermutation(int n, int r);
long findCombination(int n, int r);

int main(int argc, char *argv[]) {
   
    //Makes sure the correct number of arguments are used
    if (argc != 3) {
        printf("Please enter exactly 2 values.\n");
        return 1;
    }

   //Converts string to int 
    int n = atoi(argv[1]);
    int r = atoi(argv[2]);

   //Input validation. n and r cannot be negative AND r cannot be greater than n
    if (n < 0 || r < 0) {
        printf("Error: Values must not be negative integers.\n");
        return 1;
    }
    if (r > n){
        printf("Error: r cannot be greater than n");
        return 1;
    }
    
    // Find permutation and combination
    long permutation = findPermutation(n, r);
    long combination = findCombination(n, r);

    // Print both permutation and combination
    printf("P (%d , %d) = %ld\n", n, r, permutation);  // Permutation
    printf("C (%d , %d) = %ld\n", n, r, combination);  // Combination 

    return 0;
}

/*************************************************************
Description: This function calculates the factorial of number
*************************************************************/
long findFactorial(int num) {
    long result = 1;
    for (int i = 1; i <= num; i++) {
        result *= i;
    }
    return result;
}

/*************************************************************
Description: This function calculates the permutation using
the factorials of n and (n-r).
*************************************************************/
long findPermutation(int n, int r) {

    long nFac = findFactorial(n);
    long nrFac = findFactorial(n - r);
    return nFac / nrFac;   // Formula calculates  permutation
}

/*************************************************************
Description: This function calculates the combination using
the factorials of n, r, and (n-r).
*************************************************************/
long findCombination(int n, int r) {

    long perm = findPermutation(n, r);  
    long rFac = findFactorial(r);   
    return perm / rFac;    // Formula calculates combination
}

/* 
 * Program Name: Project2.c
 * Programmer: karigan Stewart
 * Date: 10/06/24
 * Purpose: This file is to replacate the purpose of the functions in project.s and is to output the same result and perform the same functions but in C code.
 * CSCI3240: Project 2
 * 
 * 
 * Project2.c - Source file with your solutions to the Lab.
 *          This is the file you will submit in the D2L -> Project2 dropbox.
 *
 *   Please make sure you don't include the main function in this file. Graders will use a separate `.c` file containing the `main` function to test your Mystery functions.  
 *	 If you'd like to test your code, you can create a separate `main.c` file that includes the `main` function, which calls the Mystery functions defined in this `Project2.c` file.
 *   You don't need to submit the 'main.c' file.
 *	 Make sure you have insightful comments in your code. 
 *   
 * 
 */


/***************************************************************************************************************************
This function is to take two long parameters ( a and b) and is to calculate a^b and return the result
***************************************************************************************************************************/ 
long MysteryFunction1(long a, long b) {
    long result = 1;      
        while (b > 0) { 
            result *= a;  //A is multiplied by itself b times (# of power)     
            b -= 1;       //Deincrement B till it hits 0; then end loop
        }
    return result;        //Result will hold the calculated a^b number
}


/***************************************************************************************************************************
This function reverses the binary represntation of the integer input and outputs the integer representaion of the 
reversed binary value
***************************************************************************************************************************/
unsigned int MysteryFunction2(unsigned int num) {
    unsigned int ReversedResult = 0;              // Initialize result to 0
    for (int i = 0; i < 32; i++) {
        if (num & (1 << i)) {                     // Check if the ith bit is set
            ReversedResult |= (1 << (31 - i));    // Set the corresponding bit in result
        }
    }
    return ReversedResult;                       // Return the manipulated result
}


/***************************************************************************************************************************
 This function finds and return the maximum value found in the array pointed to by the input parameter a 
***************************************************************************************************************************/
long MysteryFunction3(long *a, int n) {
    long ArrMax = a[0];                   // Initialize max to the first element
    for (int i = 1; i < n; i++) {
        if (a[i] > ArrMax) {              // Compares the current element with max 
            ArrMax = a[i];                // If current element is greater than update max and continue forloop
        }
    }
    return ArrMax;                        // Return the maximum value found
}


/***************************************************************************************************************************
  This function is to count the number of set bits in the binary representation of the input parameter by 
  viewing each bit one at a time
***************************************************************************************************************************/
int MysteryFunction4(unsigned long n) {
    int countBit = 0;               // Initialize counter variable to 0 (this is to count the number of set bits)
        while (n) {
            countBit += (n & 1);        // Add 1 if the least significant bit is set
            n >>= 1;                    // Right shift n to view the next least significant bit
        }
    return countBit;                   // Return the total count of set bits
}


/***************************************************************************************************************************
  This function is to count the number of set bits after an xor operation is performed on the 2 input parametrs by 
  count each bit one at a time
***************************************************************************************************************************/
unsigned int MysteryFunction5(unsigned int A, unsigned int B) {
    unsigned int xor_result = A ^ B;           // Perform XOR
    unsigned int countXorBit = 0;              // Initialize counter variable to 0 (this will hold set bit count)

        while (xor_result) {
            countXorBit += (xor_result & 1);   // Add 1 if the least significant bit is set
            xor_result >>= 1;                  // Right shift to process the next bit
        }
    return countXorBit; // Return the count of set bits in the XOR result
}

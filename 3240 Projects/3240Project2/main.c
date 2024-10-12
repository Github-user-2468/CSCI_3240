#include <stdio.h>

// Function prototypes from Project2.c
long MysteryFunction1(long a, int b);
unsigned int MysteryFunction2(unsigned int num);
long MysteryFunction3(long *a, int n);
int MysteryFunction4(unsigned long n);
unsigned int MysteryFunction5(unsigned int A, unsigned int B);

int main() {
    // Test MysteryFunction1 (Factorial)
    printf("MysteryFunction1(5) = %ld\n", MysteryFunction1(2, 5)); // Expect 120
     printf("MysteryFunction1(6) = %ld\n", MysteryFunction1(3, 6));
    printf("MysteryFunction1(8) = %ld\n", MysteryFunction1(2, 8));
    printf("MysteryFunction1(5) = %ld\n", MysteryFunction1(5, 5));
    printf("MysteryFunction1(2) = %ld\n", MysteryFunction1(2, 2));
    printf("MysteryFunction1(3) = %ld\n", MysteryFunction1(2, 3));
    

    // Test MysteryFunction2 (Bit Manipulation)
    unsigned int num1 = 42; // Example number
    printf("MysteryFunction2(%u) = %u\n", num1, MysteryFunction2(num1)); // Adjust expected output based on logic
    unsigned int num2 = 36; // Example number
    printf("MysteryFunction2(%u) = %u\n", num2, MysteryFunction2(num2)); // Adjust expected output based on logic
    unsigned int num3 = 4; // Example number
    printf("MysteryFunction2(%u) = %u\n", num3, MysteryFunction2(num3)); // Adjust expected output based on logic
    
    

    // Test MysteryFunction3 (Maximum in Array)
    long array[] = {1, 5, 3, 7, 2};
    int n = sizeof(array) / sizeof(array[0]);
    printf("MysteryFunction3(array, %d) = %ld\n", n, MysteryFunction3(array, n)); // Expect 7

    // Test MysteryFunction4 (Count Set Bits) 10 35 5
    unsigned long nBits = 29; // Binary 11101
    printf("MysteryFunction4(%lu) = %d\n", nBits, MysteryFunction4(nBits)); // Expect 4
    unsigned long nBits2 = 10; // Binary 11101
    printf("MysteryFunction4(%lu) = %d\n", nBits2, MysteryFunction4(nBits2));
    unsigned long nBits3 = 35; // Binary 11101
    printf("MysteryFunction4(%lu) = %d\n", nBits3, MysteryFunction4(nBits3));
    unsigned long nBits4 = 5; // Binary 11101
    printf("MysteryFunction4(%lu) = %d\n", nBits4, MysteryFunction4(nBits4));

    // Test MysteryFunction5 (XOR and Count Set Bits)
    unsigned int A = 12; // Binary 1100
    unsigned int B = 10; // Binary 1010
    printf("MysteryFunction5(%u, %u) = %d\n", A, B, MysteryFunction5(A, B)); // Expect 2

    return 0;
}

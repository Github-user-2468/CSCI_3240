#include <stdio.h>

// Function prototypes for assembly functions
long MysteryFunction1(long a, int b);
unsigned int MysteryFunction2(unsigned int num);
long MysteryFunction3(long *a, int n);
int MysteryFunction4(unsigned long n);
unsigned int MysteryFunction5(unsigned int A, unsigned int B);

int main() {
    // Test MysteryFunction1 (Factorial)
  long result = MysteryFunction1(2, 5);
    
    // Print the result
    printf("Assembly: MysteryFunction1(2, 5) = %ld\n", result);
    printf("Assembly: MysteryFunction1(3, 6) = %ld\n", MysteryFunction1(3, 6));
    printf("Assembly: MysteryFunction1(2, 8) = %ld\n", MysteryFunction1(2, 8));
    printf("Assembly: MysteryFunction1(5, 5) = %ld\n", MysteryFunction1(5, 5));
    printf("Assembly: MysteryFunction1(2, 1) = %ld\n", MysteryFunction1(2, 2));
    printf("Assembly: MysteryFunction1(2, 3) = %ld\n", MysteryFunction1(2, 3));


    // Test MysteryFunction2 (Bit Manipulation)
    unsigned int num = 0b101010; // Example number
    printf("Assembly: MysteryFunction2(%u) = %u\n", 42, MysteryFunction2(42));
     printf("Assembly: MysteryFunction2(%u) = %u\n", 36, MysteryFunction2(36));
         printf("Assembly: MysteryFunction2(%u) = %u\n", 4, MysteryFunction2(4));


    // Test MysteryFunction3 (Maximum in Array)
    long array[] = {1, 5, 3, 7, 2};
    int n = sizeof(array) / sizeof(array[0]);
    printf("Assembly: MysteryFunction3(array, %d) = %ld\n", n, MysteryFunction3(array, n));

    // Test MysteryFunction4 (Count Set Bits)
    unsigned long nBits = 29; // Binary 11101
    printf("Assembly: MysteryFunction4(%lu) = %d\n", nBits, MysteryFunction4(nBits));
    nBits = 10;
    printf("Assembly: MysteryFunction4(%lu) = %d\n", nBits, MysteryFunction4(10));
    nBits = 35;
    printf("Assembly: MysteryFunction4(%lu) = %d\n", nBits, MysteryFunction4(35));
    nBits = 5;
    printf("Assembly: MysteryFunction4(%lu) = %d\n", nBits, MysteryFunction4(5));

    // Test MysteryFunction5 (XOR and Count Set Bits)
    unsigned int A = 12; // Binary 1100
    unsigned int B = 10; // Binary 1010
    printf("Assembly: MysteryFunction5(%u, %u) = %d\n", A, B, MysteryFunction5(A, B));

    return 0;
}

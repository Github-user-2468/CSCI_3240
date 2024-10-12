#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>  // For qsort
#include <stdbool.h> // For bool type

#define MAX_WORDS 50
#define MAX_LENGTH 20

/**************************************************************
This function takes an array index and checks to see if the
word begins with a vowel. If it does it returns true
**************************************************************/
bool WordwithVowel(char word[]) {
    char firstChar = toupper(word[0]);  // Convert the first character to uppercase for comparison
    return firstChar == 'A' || firstChar == 'E' || firstChar == 'I' || firstChar == 'O' ||              firstChar == 'U';
}

/**************************************************************
This function is a comparison function for qsort
**************************************************************/
int compareWords(const void *a, const void *b) {
    return strcasecmp(*(const char **)a, *(const char **)b);
}


int main() {
   
    char sentence[1000];                    // Stores the sentence from user
    char words[MAX_WORDS][MAX_LENGTH];      // Stores individual words
    char *wordsPtr[MAX_WORDS];              // Array of pointers to words for the sorting
    int wordCount = 0;                      // A counter to count the number of words

    // Get the sentence from the user
    printf("Enter a line of text: ");
    fgets(sentence, sizeof(sentence), stdin);

    // Tokenize the sentence into individual words
    char *token = strtok(sentence, " \n");

    while (token != NULL && wordCount < MAX_WORDS) {
    strcpy(words[wordCount], token);               // Copy each word into the array
        wordsPtr[wordCount] = words[wordCount];    // Store the pointer to the word for sorting
        wordCount++;                               // Increment word count
        token = strtok(NULL, " \n");
    }

  // Check words that start with a vowel and capitalize them
    for (int i = 0; i < wordCount; i++) {
        if (WordwithVowel(words[i])) {  // Function returns true if word starts with vowel
          // Capitalizes the whole word
            for (int j = 0; words[i][j] != '\0'; j++) {
                words[i][j] = toupper(words[i][j]);
            }
        }
    }

    // Sort the words array in alphabetical order 
    qsort(wordsPtr, wordCount, sizeof(char *), compareWords);

    // Print the sorted and capitalized words
    printf("\nWords starting with vowels:\n");
    for (int i = 0; i < wordCount; i++) {
        if (WordwithVowel(wordsPtr[i])) {  // Only print the words that start with a vowel
            printf("%s\n", wordsPtr[i]);
        }
    }

    return 0;
}

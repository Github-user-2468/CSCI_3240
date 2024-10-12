/*******************************************************************************
Name: lab4Problem2
Programmer: Karigan Stewart
Date: 09-12-2024
Description: This program is to gather a username and password from the user
and is to search a file for that given input and display a numerical output
corresponding to the username and password. If there is no such match an error
message should occur.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define USERNAME_MAX 21  
#define PASSWORD_MAX 21  
#define NUMERICAL_MAX 10000000.0f  // 10^7 as a float

void checkCred(const char *username, const char *password) {
    FILE *file = fopen("userdata.txt", "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    char file_username[USERNAME_MAX];
    char file_password[PASSWORD_MAX];
    float numerical_data;  // Change from int to float

    // Read file line by line
    while (fgets(line, sizeof(line), file)) {
        // Parse the line and check the data
        if (sscanf(line, "%20s %20s %f", file_username, file_password, &numerical_data) == 3) {
            if (strcmp(username, file_username) == 0 && 
                strcmp(password, file_password) == 0 &&
                numerical_data <= NUMERICAL_MAX) {
                printf("The amount is: %.2f\n", numerical_data);  // Format as float with 2 decimal places
                fclose(file);
                return; 
            }
        }
    }

    // If no match is found
    printf("Username/password mismatch!!!\n");
    fclose(file);
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];

    // Get username from the user
    printf("Username: ");
    if (scanf("%20s", username) != 1 || strlen(username) > 20) {
        fprintf(stderr, "Invalid username. It must be between 1 and 20 characters.\n");
        return 1;  // Return 1 if the username is invalid
    }

    // Get password from the user
    printf("Password: ");
    if (scanf("%20s", password) != 1 || strlen(password) > 20) {
        fprintf(stderr, "Invalid password. It must be between 1 and 20 characters.\n");
        return 1;  // Return 1 if the password is invalid
    }

    // Check credentials
    checkCred(username, password);

    return 0;
}

#include "csapp.h"

// Define constants for buffer sizes and record limits
#define FILESIZE 1000          // Max size for file reading buffer
#define MAXSTRUCT 100          // Max number of employee records that can be handled
#define NAMELIMIT 100          // Max length for first and last name
#define ZIPLIMIT 6             // Max length for zip code
#define DEPTLIMIT 100          // Max length for department name
#define MAX_SIZE 1000          // Max size for result strings

struct Struct_Employee_Info {
    char firstName[NAMELIMIT];        // First name of the employee
    char lastName[NAMELIMIT];         // Last name of the employee
    char zipCode[ZIPLIMIT];           // Zip code of the employee
    char department[DEPTLIMIT];       // Department of the employee
    int salary;                       // Salary of the employee
};

// Function declarations for searching employee data by name, zip code, and salary
char* SearchByName(struct Struct_Employee_Info employee[], const char *firstName, const char *lastName);
char* SearchByZipCode(struct Struct_Employee_Info employee[], const char *zipCode);
char* SearchBySalary(struct Struct_Employee_Info employee[], int salary, const char *comparisonOperator);
void serverFunction(int connfd);


void serverFunction(int connfd) {
    char buffer[MAXLINE];         //MAXLINE = 8192 in csapp.h
    char successMess[MAXLINE] = "Record added Successfully!!\n";  // Success message for adding a record
    char connectClosed[MAXLINE] = "Connection Closed!!\n";        // Message for closing the connection
    int userChoice;                       // Stores users menu choice
    FILE *employRec;                      // File pointer to the records.csv
    size_t n;                             // Number of bytes read from the client
    char *filename = "records.csv";       // File that holds employee records
    char buf[FILESIZE];                   // Buffer to read file contents
    int count = 0;                        // Counter variable for number of records read
    struct Struct_Employee_Info employee[MAXSTRUCT];  // Array of structures to hold employee data 

   // Open the records file for reading
    employRec = fopen(filename, "a+");
    if (employRec == NULL) {
        perror("Failed to open file");
        return;
    }

    // Read employee records from the file into employee structure
    while (fgets(buf, FILESIZE, employRec) != NULL && count < MAXSTRUCT) {
        sscanf(buf, "%[^,],%[^,],%[^,],%[^,],%d", 
               employee[count].firstName,   // Holds first name
               employee[count].lastName,    // Holds last name
               employee[count].zipCode,     // Holds zip code
               employee[count].department,  // Holds department
               &employee[count].salary);    // Holds salary
        count++;                            // Increment the record counter
    }

    // Reset the buffer to clear any leftover data
    bzero(buffer, MAXLINE);

    // Main loop to handle incoming client requests
    while ((n = read(connfd, buffer, MAXLINE)) != 0) {
        write(connfd, buffer, strlen(buffer)); // Echo the client's input back to them
        userChoice = atoi(buffer); // Convert the client's choice from string to integer

        switch (userChoice) {
        
        // Case 1 (option 1 == Add Record) This adds records to the records.csv and gathers input from user
            case 1: 
                bzero(buffer, MAXLINE);                 // Resets the buffer
                n = read(connfd, buffer, MAXLINE);      // Read employee data from client
                if (count < MAXSTRUCT) {
                    // Parse the buffer data into the employee record
                    sscanf(buffer, "%[^,],%[^,],%[^,],%[^,],%d", 
                           employee[count].firstName,     // Adds first name
                           employee[count].lastName,      // Adds last name
                           employee[count].zipCode,       // Adds zip code
                           employee[count].department,    // Adds department
                           &employee[count].salary);      // Adds salary 
                    
             // Write the new record to the file
                    fprintf(employRec, "%s\n", buffer);
                    count++; // Increment the record counter
                    write(connfd, successMess, strlen(successMess)); // Send success message 
               
                } else {
                    write(connfd, "Max records reached.\n", 21); // Send a message that max has been reached
                }
                
                bzero(buffer, MAXLINE);  // Reset buffer
                break;

     // Case 2 (option 2 == Search by Name) Gets a name from user and searches/returns a corresponding employee name 
            case 2: 
                bzero(buffer, MAXLINE);                            // Clear the buffer
                n = read(connfd, buffer, MAXLINE);                 // Reads the name given by the client program
                char firstName[NAMELIMIT], lastName[NAMELIMIT];    // Creates two buffers for the first and last name

               // Reads first name and last name from userInput(buffer)
                sscanf(buffer, "%[^,],%s", firstName, lastName);

                // Search for the employee by name by calling SearchByName function 
                char *searchName = SearchByName(employee, firstName, lastName);

                // Sends result back to client program
                write(connfd, searchName, strlen(searchName));
                free(searchName);          // Free memory
               
                bzero(buffer, MAXLINE);    // Reset buffer
                break;

    // Case 3 (option 3 == Searches by Zip code) gathers input from the user and finds the corresponding employee based on the given zip code
            case 3:
                bzero(buffer, MAXLINE);                                // Clear the buffer
                n = read(connfd, buffer, MAXLINE);                     // Read zip code input from client program
                char *searchZip = SearchByZipCode(employee, buffer);

                // Calls function SearchByZipCode to find employee records by the given zip code
                write(connfd, searchZip, strlen(searchZip)); 

                // Sends results to client program 
                free(searchZip);         // Free memory 
                bzero(buffer, MAXLINE);  // Reset buffer 
                break;

      // Case 4 (option 4 == Search by salary) This program searches for employee record by the given salary
            case 4:
                bzero(buffer, MAXLINE);                 // Clear the buffer
                n = read(connfd, buffer, MAXLINE);      // Read salary input from client
                int salary = atoi(buffer);              // Convert user input into an integer for comparison
                write(connfd, buffer, strlen(buffer));  // Echo back the salary
                bzero(buffer, MAXLINE);                 
                n = read(connfd, buffer, MAXLINE);       // Read the comparison operator 

           // Calls the SearchBySalary function to find corresponding employee records that fit salary and comparison operator 
                char *searchSalary = SearchBySalary(employee, salary, buffer);

                // Sends results to client program
                write(connfd, searchSalary, strlen(searchSalary)); 
                free(searchSalary);      // Free memory
                bzero(buffer, MAXLINE);
                break;

       // Case 5 (option 5 == terminate) Closes the connection between client and server, server remains running 
            case 5: 
                write(connfd, connectClosed, strlen(connectClosed)); // Send connection closed message
                bzero(buffer, MAXLINE); // Reset buffer
                break;
            
      // Default case (If user input is not 1,2,3,4, or 5)
            default:
                write(connfd, "Invalid option.\n", 16); // Error message
                break;
        }
    }

    // Close the file after finishing communication with the client
    fclose(employRec);
    return;
}

int main(int argc, char *argv[]) {
    int listenfd;
    int connfd;                    // File descriptor for client communication
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; // To hold the client address
    char client_hostname[MAXLINE], client_port[MAXLINE];

    // Ensures that correct amount of arguments 
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    // Open a listening socket on the port provided with argument
    listenfd = Open_listenfd(argv[1]);

    // Loop to handle incoming client connections 
    // Server runs in the infinite loop.
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);

        // Wait for the connection from the client.
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, client_hostname,
                     MAXLINE, client_port, MAXLINE, 0);

        printf("Connected to (%s, %s)\n", client_hostname, client_port);

        // Function to interact with the client
        serverFunction(connfd);

        Close(connfd);
        printf("(%s, %s) Server has disconnected\n", client_hostname, client_port);
    }
    exit(0);
}


// ======================= Function Declarations ==============================

/****************************************************************************
This function searches the employee records structure based on the given
first and last name parameters. If a match is found it is to display the 
employee name, zip code, department, and salary information 
****************************************************************************/
char* SearchByName(struct Struct_Employee_Info employee[], const char *firstName, const char *lastName) {
   char *result = malloc(MAX_SIZE * sizeof(char));  // Allocate memory for the result string
    bzero(result, MAX_SIZE);                        // Initialize result with zeros 

   // Loops through the employee records to search for employee by name
    for (int i = 0; i < MAXSTRUCT; i++) {
     // Compares records with the given first and last name 
        if (strcmp(employee[i].firstName, firstName) == 0 && strcmp(employee[i].lastName, lastName) == 0) {
           
            char temp[MAX_SIZE];        // Temporary string buffer to format the employee data
          //Prints out FOUND matching employee records 
            sprintf(temp, "%s,%s,%s,%s,%d\n", 
                employee[i].firstName,  // Prints out first name
                employee[i].lastName,   // Prints out last name
                employee[i].zipCode,    // Prints out zip code
                employee[i].department, // Prints out department
                employee[i].salary);    // Prints out salary
                strcat(result, temp);   // Append the formatted record to the result string
        }
    }

    // If no matching records were found return an error message 
    if (strlen(result) == 0) {
        sprintf(result, "No matching records found.\n");
    }
    return result; // Return the result string containg employee record/ or error message
}

/****************************************************************************
This takes seraches the employee structure for the employee record
mataching the zip code inputted into the function parameters. If found
the function will return the employee information, if not the function 
will return an error message
****************************************************************************/
char* SearchByZipCode(struct Struct_Employee_Info employee[], const char *zipCode) {
    char *result = malloc(FILESIZE);  // Allocate memory for the return
    
    if (!result) return strdup("Memory allocation failed.\n"); 
    bzero(result, FILESIZE);     // Initialize result with zeros

    char noRecord[MAXLINE] = "No record found!!\n";    // Error message if no record matching zip was found

  // Loop through the employee records to find records matching the zip code
    for (int i = 0; i < MAXSTRUCT; i++) {
      // if a matching record is found display information 
        if (strcmp(zipCode, employee[i].zipCode) == 0) {
            snprintf(result + strlen(result), FILESIZE - strlen(result), 
                     "%s,%s,%s,%s,%d\n", 
                     employee[i].firstName,  // Prints first name
                     employee[i].lastName,   // Prints last name
                     employee[i].zipCode,    // Prints zip code
                     employee[i].department, // Prints department 
                     employee[i].salary);    // Prints salary
        }
    }

    // If no matching records found, return a "no records" message
    if (strlen(result) == 0) {
        strncpy(result, noRecord, strlen(noRecord));
    }
    return result; // Return the result string
}

/****************************************************************************
This function takes a salary amount and comparison operator and searches
the employee records for matching information based on the comparison 
operator and salary given. If so it will print out the employee information
that matches the parameters given 
****************************************************************************/
char* SearchBySalary(struct Struct_Employee_Info employee[], int salary, const char *comparisonOperator) {
    char *result = malloc(FILESIZE);  // Allocate memory for the return string
    if (!result) {
        return strdup("Memory allocation failed.\n");
    }
    bzero(result, FILESIZE);  // Initialize result with zeros

    char noRecord[MAXLINE] = "No record found!!\n"; // Message if no matching record is found

    // Loop through the employee array to check salary with the operator
    for (int i = 0; i < MAXSTRUCT; i++) {
        // Ensure that the employee record is valid and initialized
        if (employee[i].salary == 0 && strlen(employee[i].firstName) == 0) {
            continue;  // Skip uninitialized or invalid records
        }

        int matches = 0;

        // Check the salary condition with the comparison operator
        if (strcmp(comparisonOperator, ">") == 0 && employee[i].salary > salary) {
            matches = 1;
        } else if (strcmp(comparisonOperator, "<") == 0 && employee[i].salary < salary) {
            matches = 1;
        } else if (strcmp(comparisonOperator, ">=") == 0 && employee[i].salary >= salary) {
            matches = 1;
        } else if (strcmp(comparisonOperator, "<=") == 0 && employee[i].salary <= salary) {
            matches = 1;
        } else if (strcmp(comparisonOperator, "==") == 0 && employee[i].salary == salary) {
            matches = 1;
        }

        // If a match is found, append the employee data to the result string
        char temp[MAX_SIZE];
        
        if (matches) {
            // Ensure snprintf does not overflow
            snprintf(result + strlen(result), FILESIZE - strlen(result), 
                     "%s,%s,%s,%s,%d\n", 
                     employee[i].firstName,   // First name
                     employee[i].lastName,    // Last name
                     employee[i].zipCode,     // Zip code
                     employee[i].department,  // Department
                     employee[i].salary);     // Salary
                     strcat(result, temp);
        }
    }

    // If no matching records found, return the "no records" message
    if (strlen(result) == 0) {
        strncpy(result, noRecord, strlen(noRecord));
    }

    return result; // Return the result string
}


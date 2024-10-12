/*****************************************************************************
Program Name: lab6Problem1
Programmer:Karigan Stewart
Date: 09/30/24
Description: This program is to read from the file  records.csv and is to 
input the data into a structure Struct_Employee_Info. It is to then search 
the structure for employee infomration through the given methods; searching 
by name, searching by salart, and searching through zip code. If a match is  
found through any of those means displays the matched employee info. 
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define MAX_LENGTH 25

typedef struct {
    char firstName[MAX_LENGTH];  
    char lastName[MAX_LENGTH];
    char zipCode[MAX_LENGTH];
    char department[MAX_LENGTH];
    int salary;
} Struct_Employee_Info;


/************************************************************************
This function is to access the structure containing the information
about each employee and is to search the structure by name. It will
accept a first name and last name of an employee and is to search the
structure until it finds a match. If a match is found it is to return 
the information regarding that employee. If no information is found,
send an error message saying no matching records found.
************************************************************************/

char* searchByName(Struct_Employee_Info employees[], int count, const char *firstName, const char *lastName) {
    //creating a character array to store the result of the search operation
    char *result = malloc(MAX_SIZE * sizeof(char));
    /*The bzero() function erases the data in the MAX_SIZE bytes of the memory starting at the location pointed to by
     result, by writing zeros (bytes containing '\0') to that area.*/
    bzero(result,MAX_SIZE);
    
    //TODO Start: ====================================
    for (int i = 0; i < count; i++) {
        
        // IF FIRST AND LAST NAME MATCH
        if (strcmp(employees[i].firstName, firstName) == 0 && strcmp(employees[i].lastName, lastName) == 0) {
            char temp[MAX_SIZE];      // Temporary variable to hold the string to concate later
            sprintf(temp, "Name: %s %s\tZip Code: %s\tDepartment: %s\tSalary: %d\n", 
                employees[i].firstName, employees[i].lastName,
                employees[i].zipCode, employees[i].department, employees[i].salary);
            strcat(result, temp);   // Append to result to form one string
        }
    }

    if (strlen(result) == 0) {
        sprintf(result, "No matching records found.\n");
    }
    //TODO End  ==========================
    return result;
}

/************************************************************************
This function is to accept a zip code as a parameter and is to search
the employee function for the given zip code. If a zip code is found
it returns the information about the employee or employees with 
the matching zip code. If no match is found, return an error message
indicating no matching record.
************************************************************************/

char* searchByZipCode(Struct_Employee_Info employees[], int count, const char *zipCode) {
    //creating a character array to store the result of the search operation
    char *result = malloc(MAX_SIZE * sizeof(char));
    /*The bzero() function erases the data in the MAX_SIZE bytes of the memory starting at the location pointed to by
     result, by writing zeros (bytes containing '\0') to that area.*/
    bzero(result,MAX_SIZE);

    //TODO Start: =================================================================
    for (int i = 0; i < count; i++) {
        
      //If a matching zip code is found
        if (strcmp(employees[i].zipCode, zipCode) == 0) {
            char temp[MAX_SIZE];     // Temporary variable to hold string to concate later
            sprintf(temp, "Name: %s %s\tZip Code: %s\tDepartment: %s\tSalary: %d\n", 
                employees[i].firstName, employees[i].lastName,
                employees[i].zipCode, employees[i].department, employees[i].salary);
            strcat(result, temp); // Append to result
        }
    }
   //If NO match is found
    if (strlen(result) == 0) {
        sprintf(result, "No matching records found.\n");
    }
    //TODO End =====================================================================
    return result;
}

/************************************************************************
This function is to accept an integer salary value as a parameter. The 
function is to then search the employee structure for the matching 
salary input. It also accepts a comparison operator as a parameter as
a part of its search. So the function can search for any salary less
than/equal to, greater than/equal to, or equal to the salary parameter.
************************************************************************/

char* searchBySalary(Struct_Employee_Info employees[], int count, int salary, const char *comparisonOperator) {
    //creating a character array to store the result of the search operation
    char *result = malloc(MAX_SIZE * sizeof(char));
    /*The bzero() function erases the data in the MAX_SIZE bytes of the memory starting at the location pointed to by
     result, by writing zeros (bytes containing '\0') to that area.*/
    bzero(result,MAX_SIZE);

    //TODO Start: ================================================================
    for (int i = 0; i < count; i++) {
        int salaryMatch = 0;

        //Uses comparison operators and salary amount to search structure 
        if (strcmp(comparisonOperator, ">") == 0) {            // greater than
            salaryMatch = employees[i].salary > salary;
        } else if (strcmp(comparisonOperator, "<") == 0) {    // less than
            salaryMatch = employees[i].salary < salary;
        } else if (strcmp(comparisonOperator, ">=") == 0) {    // greater than/equal to
            salaryMatch = employees[i].salary >= salary;
        } else if (strcmp(comparisonOperator, "<=") == 0) {    // less than/equal to 
            salaryMatch = employees[i].salary <= salary;
        } else if (strcmp(comparisonOperator, "==") == 0) {    // equal to
            salaryMatch = employees[i].salary == salary;
        }

        // If a match is found; print employee information
        if (salaryMatch) {
            char temp[MAX_SIZE]; // Temporary variable to hold formatted string
            sprintf(temp, "Name: %s %s\tZip Code: %s\tDepartment: %s\tSalary: %d\n", 
                employees[i].firstName, employees[i].lastName,
                employees[i].zipCode, employees[i].department, employees[i].salary);
           
            strcat(result, temp); // Append to result
        }
    }

    // if NO match is found 
    if (strlen(result) == 0) {
        sprintf(result, "No matching records found.\n");
    }
    //TODO End ===============================================================
    return result;
}

int main() {
    FILE *file;
    Struct_Employee_Info employees[MAX_SIZE];
    char line[MAX_SIZE];
    int count = 0;

    file = fopen("records.csv", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    //Adding the record from records.csv to the employees structure
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",
               employees[count].firstName, employees[count].lastName,
               employees[count].zipCode, employees[count].department,&employees[count].salary);
        count++;
    }

    fclose(file);

    char *searchResult1 = searchByName(employees, count, "Jack", "Sparrow");
    printf("\nSearch Results by Name: %s %s\n", "Jack", "Sparrow");
    printf("%s", searchResult1);
    free(searchResult1);

    char *searchResult2 = searchByZipCode(employees, count, "37128");
    printf("\nSearch Results by Zip Code: %s\n", "37128");
    printf("%s", searchResult2);
    free(searchResult2);

    char *searchResult3 = searchBySalary(employees, count, 45000, ">=");
    printf("\nSearch Results by Salary: %s %d\n", ">=", 45000);
    printf("%s", searchResult3);
    free(searchResult3);

    char *searchResult4 = searchBySalary(employees, count, 500000, "==");
    printf("\nSearch Results by Salary: %s %d\n", "==", 500000);
    printf("%s", searchResult4);
    free(searchResult4);

    return 0;
}

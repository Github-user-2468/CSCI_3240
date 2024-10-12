/************************************************************************************
Programmer: Karigan Stewart
Program Name:lab5Problem1
Date: 09/25/24
Description: This program is to read from a .csv file and is to display the data
in the file sorted by score order.
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 51
#define MAX_ID_LENGTH 7

typedef struct { 
    char StudentName[MAX_NAME_LENGTH];      //To hold student name             
    char ID[MAX_ID_LENGTH];                 //To hold ID number
    float Score;                            //To hold sudent score
} Struct_Student_Info;

// Function prototypes
void SortByScore(Struct_Student_Info studentsArray[], int n);                             //Sorts score using bubble sort
void Display(const Struct_Student_Info studentsArray[], int n);                           //Displays structure
int readStudentsFromFile(const char* filename, Struct_Student_Info studentsArray[]);      //Reads file and stores in structure

int main() {
    Struct_Student_Info studentsArray[MAX_STUDENTS]; //Array of structure objects to hold student information

  //calls read function to read from file and store in array and return number of students in file
    int n = readStudentsFromFile("student.csv", studentsArray);    
    
    if (n == -1) {   //If readStudentFromFile returns error code
        printf("Error reading student data.\n");
        return 1;
    }

    SortByScore(studentsArray, n);       //sorts students by score order by number of students 
    Display(studentsArray, n);           //Displays in the new sorted order

    return 0;
}

/**************************************************************************
This function is to take a filename and a structure array as parameters.
It is to then read the file and store its contents into the array. It is 
scan the file and break it up into three components when it hits a comma
and a float. It is to then close the file and return the number of 
students read
**************************************************************************/
int readStudentsFromFile(const char* filename, Struct_Student_Info studentsArray[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return -1; // Error opening file
    }

    char line[100];
    int count = 0;     //Holds number of students read

    // Skip the header line
    fgets(line, sizeof(line), file);   //Skips header (dont need it) and it would affect storing in structure

    while (fgets(line, sizeof(line), file) && count < MAX_STUDENTS) {
        sscanf(line, "%[^,], %[^,], %f",             //stops at commas 1 and 2, and floating int 
               studentsArray[count].StudentName,     //holds student name
               studentsArray[count].ID,              //holds id
               &studentsArray[count].Score);         //holds score 
        count++;
    }

    fclose(file);
    return count; // Return number of students read
}

/************************************************************************
This function is to take an structure array and integer paratmeter and
is to sort the given array of items by their asending score order. If 
a student were to have the same score as another; sort by name order
This function uses bubble sort algorithmn
************************************************************************/
void SortByScore(Struct_Student_Info studentsArray[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // Sort by score first
            if (studentsArray[i].Score > studentsArray[j].Score ||
                (studentsArray[i].Score == studentsArray[j].Score &&
                 strcmp(studentsArray[i].StudentName, studentsArray[j].StudentName) > 0)) {
                // Swap the smaller with the bigger
                Struct_Student_Info temp = studentsArray[i];
                studentsArray[i] = studentsArray[j];
                studentsArray[j] = temp;
            }
        }
    }
}

/*******************************************************************
This funciton is to display the sorted data in the Student_Info
structure array
*******************************************************************/
void Display(const Struct_Student_Info studentsArray[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %s %.2f\n", studentsArray[i].StudentName, studentsArray[i].ID, studentsArray[i].Score);
    }
}

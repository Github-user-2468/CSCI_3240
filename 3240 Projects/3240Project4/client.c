

#include "csapp.h"


int main(int argc, char *argv[])
{
    int clientfd;                   //file descriptor to communicate with the server
    char *host, *port;
    size_t n;
    char buffer[MAXLINE];            // MAXLINE = 8192 defined in csapp.h           
    char userInput[MAXLINE];         // Temp storage for user input 
    int userChoice;                  // Holds user menu choice 
    
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
       exit(0);
    }

    host = argv[1];
    port = argv[2];
    clientfd = Open_clientfd(host, port);

    

    // Reset buffer
    bzero(buffer,MAXLINE);
    // Enters the loop until it is disconnected (menu option 5/ctrl + c)
    do{
        // Prints out menu to user
        printf("(1) Add record\n");             // Option to add record
        printf("(2) Search by Name\n");         // Option to search by name
        printf("(3) Search by Zip Code\n");     // Option to search by Zip Code
        printf("(4) Search by Salary\n");       // Option to search by salary
        printf("(5) Terminate\n");              // Option to end connection
        printf("Select an option [1,2,3,4, or 5]: ");      // Asks user for input

        //get choice from user
        Fgets(buffer, MAXLINE, stdin);           // Gets user input for menu 
        userChoice = atoi(buffer);               // Turns user input into intger value for comparison

        // Sends choice to server for case 
        write(clientfd,buffer,strlen(buffer));
        read(clientfd,buffer,MAXLINE);

        // Based on user choice from enter prompts user for input 
        switch(userChoice){
    
    // Case 1 (option 1 == Add record) asks user for the employee information ==============================================
            case 1:
                // Resetting the buffers
                bzero(userInput,MAXLINE);          // Clears the buffer to ready for more input from user 
                bzero(buffer,MAXLINE);
                // GETS FIRST NAME ====
                printf("\nEnter first name: ");      // Gets first name of employee
                // Holds the user input 
                Fgets(userInput,MAXLINE,stdin);
                   // Append the userInput to the buffer so it can be sent to the server == first name
                      strncpy(buffer, userInput, strlen(userInput)-1);
                      strncat(buffer, ",", 1);

                // GETS LAST NAME === 
                bzero(userInput,MAXLINE);
                printf("Enter last name: ");      // Gets last name of employee
                // Holds user input 
                Fgets(userInput,MAXLINE,stdin);
                   // Append the userInput to the buffer so it can be sent to the server == last name 
                      strncat(buffer, userInput, strlen(userInput)-1); // Append to the buffer except the null 
                      strncat(buffer, ",", 1);                         // Append comma for output

                // GETS ZIP CODE ===
                printf("Enter Zip Code: ");      // Gets zip code for employee
                Fgets(userInput,MAXLINE,stdin);
                   // Append the userInput to the buffer so it can be sent to the server 
                      strncat(buffer, userInput, strlen(userInput)-1);   // Append user input to the buffer except the null
                      strncat(buffer, ",", 1);                           // Append the comman for output 

                // GETS DEPARTMENT ===
                printf("Enter Department: ");   // Gets department that employee works for
                Fgets(userInput,MAXLINE,stdin);
                   // Append the userInput to the buffer so it can be sent to the server 
                      strncat(buffer, userInput, strlen(userInput)-1);      // Append user input to the buffer except the null
                      strncat(buffer, ",", 1);                              // Append the comma for output 

                // GETS SALARY === 
                printf("Enter Salary: ");       // Gets employees salary 
                Fgets(userInput,MAXLINE,stdin); // Gets user input and stores in userInput
                    // Append the userInput to the buffer so it can be sent to the server 
                        strncat(buffer, userInput, strlen(userInput)-1);     // Append user input to the buffer except the null

                write(clientfd,buffer,strlen(buffer));
                bzero(buffer,MAXLINE);          // Reset buffer
                bzero(userInput,MAXLINE);       // Clears the buffer to ready for more input from user 
                
                // Recieves message from server that the record has been sucessfully added 
                read(clientfd,buffer,MAXLINE);
                printf("Message from Server:\n");
                // Displays the message in the buffer 
                   Fputs(buffer,stdout);
                   printf("\n");
                break;
            
    // Case 2 (option 2 == Search by Name) asks the user for first/last name and displays cooresponding records===========================
            case 2:
                bzero(buffer,MAXLINE);                    // Resets buffer
                // GETS FIRST NAME ===
                printf("\nEnter first name: ");             // Gets employee first name
                Fgets(userInput,MAXLINE,stdin);           // Stores the input given from user into server
                  // Append the userInput to the buffer so it can be sent to the server 
                      strncpy(buffer, userInput, strlen(userInput)-1);      // Append
                      strncat(buffer, ",", 1);

                // GETS LAST NAME 
                printf("Enter last name: ");              // Gets employee last name
                Fgets(userInput,MAXLINE,stdin);           // Inserts the input from user into the userinput to be sent to server 
                   // Append the userInput to the buffer so it can be sent to the server
                      strncat(buffer, userInput, strlen(userInput)-1);

                // Sends the messages to the server that is stored in buffer
                write(clientfd,buffer,strlen(buffer));
                bzero(buffer,MAXLINE);
                bzero(userInput,MAXLINE);
                
                // Gets a return message from the server
                read(clientfd,buffer,MAXLINE);
                printf("Message from Server:\n");
                // Displays the message held in buffer 
                   Fputs(buffer,stdout);
                        printf("\n");
                break;
            
    // Case 3 (option 3 == Search by zip code) asks the user for a zip code and returns cooresponding employee information =========
            case 3:
                bzero(buffer,MAXLINE);
                // GETS ZIP CODE === 
                printf("\nEnter Zip Code: ");           // Gets employee zip code
                Fgets(userInput,MAXLINE,stdin);       // Stores input from user into userInput 
                    // Append the userInput to the buffer so it can be sent to the server 
                        strncat(buffer, userInput, strlen(userInput)-1);
                
                // Sends the information given by the user over to the server
                write(clientfd,buffer,strlen(buffer));
                // Resets buffers
                  bzero(buffer,MAXLINE);
                  bzero(userInput,MAXLINE);
                
                // Gets the message returned from the server
                read(clientfd,buffer,MAXLINE);
                printf("Message from Server:\n");
                // Displays the message that is held in the buffer
                    Fputs(buffer,stdout);
                     printf("\n");
                break;
            
    // case 4 (option 4 == Search by Salary) This gets employee salary and comparison operator and returns the corresponding employee info
            case 4:
                bzero(buffer,MAXLINE);
                // GETS SALARY
                printf("\nEnter Salary: ");         // Gets Salary information 
                Fgets(userInput,MAXLINE,stdin);   // Stores input from the user into userInput 
                   // Append the userInput to the buffer so it can be sent to the server
                      strncat(buffer, userInput, strlen(userInput)-1);

                // This sends the information to the server
                write(clientfd,buffer,strlen(buffer));
                read(clientfd,buffer,MAXLINE);
                   // Resets buffer
                     bzero(buffer,MAXLINE);
                     bzero(userInput,MAXLINE);   
                // GETS COMPARISON TYPE == 
                printf("Enter Comparision Type [’>’,’<’,’==’,’>=’,’<=’]: ");        // Gets comparison operator from the user 
                Fgets(userInput,MAXLINE,stdin);     // Stores comparison type into userInput 
                   // Append the userInput to the buffer so it can be sent to the server
                     strncat(buffer, userInput, strlen(userInput)-1);     

                // This sends the comparison operator to the server 
                write(clientfd,buffer,strlen(buffer));
                bzero(buffer,MAXLINE);
                bzero(userInput,MAXLINE);

                // Gets the message returned from the server
                read(clientfd,buffer,MAXLINE);
                printf("Message from Server:\n");
                // Displays the message from server 
                   Fputs(buffer,stdout);
                    printf("\n");
                break;
          
    // Case 5 (option 5 == terminate) This ends the client connection with the server, the server keeps running =======
            case 5:
                Close(clientfd);     // Closes client connection 
                exit(0);
                break;
    // Default == if any of the entered values from the user did not match 1,2,3,4, or 5 =================================
            default:
                printf("Invalid choice!\n");
                break;
        }
    }while(userChoice != 5);
    


    Close(clientfd);   // closes connection 
    return 0;
}
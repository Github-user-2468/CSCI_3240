#include "csapp.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

#define BUFSIZE 1024  // Buffer size for reading and sending messages

// Global variables
int sockfd;          // File descriptor for the client
char username[50];   // Username of the client

// Function prototypes
void *receive_messages(void *arg);    
void send_message(const char *message);  

//-------------------------------------------------

int main(int argc, char **argv) {
    // Check if correct number of arguments are passed 
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        exit(1);
    }

    // Define server address structure and establish a connection to the server
    struct sockaddr_in serveraddr;
    sockfd = Open_clientfd(argv[1], argv[2]);  // Open connection to the server 

    // Receive the welcome message from the server first
    char buf[BUFSIZE];
    int n = recv(sockfd, buf, sizeof(buf), 0);  // Receive the welcome message from the server
    if (n <= 0) {
        fprintf(stderr, "Failed to receive the welcome message.\n");
        exit(1);
    }
    buf[n] = '\0';        // Null-terminate the received message
    printf("%s\n", buf);  // Print the welcome message from the server

    // Prompt the user to enter their username
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);  // Read the username from the user
    username[strcspn(username, "\n")] = '\0';  // Remove the newline character from the username input

    // Send the username to the server
    send(sockfd, username, strlen(username), 0);  // Send the username to the server

    // Create a new thread to handle receiving messages from the server
    pthread_t tid;
    pthread_create(&tid, NULL, receive_messages, NULL);  // Create a new thread to receive messages 

    // Main loop to send messages to the server
    while (1) {
      // Print the prompt and ensure it's displayed
        printf("> ");
        fflush(stdout);  // Flush the output buffer 

        // Get user input for the message to be sent
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';  // Remove the newline character from input

        // Check if the user typed "exit" to close the connection
        if (strcmp(buf, "exit") == 0) {
            send_message("exit");     // Send "exit" message to server
            break;                    // Exit the loop and terminate the program
        }

        // Send the message to the server
        send_message(buf);
    }

    // Close the socket after the communication is done
    close(sockfd);
    return 0;
}

// Function to handle receiving messages from the server in a separate thread
void *receive_messages(void *arg) {
    char buf[BUFSIZE];  // Buffer to store received messages
    int n;

    // Setup for using select() to check if there is data to read from the server
    fd_set readfds;          // Set of file descriptors to monitor
    struct timeval timeout;  // Timeout value for select()

    while (1) {
        FD_ZERO(&readfds);           // Clear the readfds set
        FD_SET(sockfd, &readfds);  // Add the client socket to the readfds set
        
        // Set the timeout for select(), to avoid blocking indefinitely
        timeout.tv_sec = 1;       // 1 second timeout for select
        timeout.tv_usec = 0;      // No microseconds

        // Call select() to check if there is data available on the socket
        int activity = select(sockfd + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0) {
            printf("select() error\n");
            continue;  // Continue if there was an error with select
        }

        // Check if there is data available to read from the socket
        if (FD_ISSET(sockfd, &readfds)) {
            n = recv(sockfd, buf, sizeof(buf), 0);  // Receive data from the server
            if (n <= 0) {
                printf("Disconnected from the server.\n");  // If the connection was closed
                exit(0);  // Exit the program
            }
            buf[n] = '\0';  // Null-terminate the received message

            // Print the received message without overwriting the prompt
            printf("\r%s\n> ", buf);  // Print the received message and display the prompt on the next line
            fflush(stdout);           // Flush the output to ensure it's displayed immediately
        }
    }
}

// Function to send a message to the server
void send_message(const char *message) {
    send(sockfd, message, strlen(message), 0);  // Send the message to the server
}

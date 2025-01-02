#include "csapp.h"
#include <pthread.h>

#define MAX_CLIENTS 100   // Maximum number of clients that the server can handle
#define BUFSIZE 1024      // Buffer size for reading messages

// Structure to represent each client
typedef struct {
    int connfd;          // Connection file descriptor for the client
    char username[50];   // Username of the client
} client_t;

client_t *clients[MAX_CLIENTS];                              // Array to store connected clients
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;   // Mutex to protect access to the client list

// Function prototypes 
void *handle_client(void *arg);               
void broadcast_message(char *message, int sender_fd);  
void add_client(client_t *new_client);      
void remove_client(int connfd);             
void *input_listener(void *arg);          

//-------------------------------------------------

int main(int argc, char **argv) {
    int listenfd, connfd, *client_sock;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;   // Thread ID for handling client connections
    
    // Check if the server port is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    // Open a listening socket
    listenfd = Open_listenfd(argv[1]);

    // Server runs in an infinite loop, handling multiple clients
    while (1) {
        clientlen = sizeof(clientaddr);
        // Accept a new client connection
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

        // Create a new thread to handle this client
        pthread_t client_thread;
        client_sock = malloc(sizeof(int));
        *client_sock = connfd;
        pthread_create(&client_thread, NULL, handle_client, (void *)client_sock);
    }

    return 0;
}

// Function to handle each client connection
void *handle_client(void *arg) {
    int connfd = *((int *)arg);     // Retrieve the client socket descriptor
    free(arg);                      // Free the memory allocated for the client socket descriptor
    char buf[BUFSIZE];              // Buffer to store incoming messages
    int n;

    // Send the welcome message first
    char *welcome_message = "Welcome to the server. This is a safe place where we support and share our struggles.\n"
                            "Rules:\n"
                            "1. Be kind.\n"
                            "2. No swearing.\n"
                            "3. No encouragement of self-harm.\n"
                            "4. No degrading each other.\n"
                            "5. We are here to support, not hurt.\n";
    send(connfd, welcome_message, strlen(welcome_message), 0);  // Send the welcome message to the client

    // Now receive the username from the client
    if ((n = recv(connfd, buf, sizeof(buf), 0)) <= 0) {
        close(connfd);  // Close connection if there was an error or client disconnected
        return NULL;
    }
    buf[n] = '\0';          // Null-terminate the received username
    char username[50];
    strcpy(username, buf);  // Copy the received username into the username variable

    // Create new client structure and add it to the list of clients
    client_t *new_client = malloc(sizeof(client_t));
    new_client->connfd = connfd;               // Store the client connection fd
    strcpy(new_client->username, username);    // Store the username
    add_client(new_client);                    // Add the client to the client list

  // Inform other clients that a new user has joined
    char join_message[BUFSIZE];
    sprintf(join_message, "%s has joined the chat\n", username);  // Prepare the join message
    broadcast_message(join_message, connfd);                      // Broadcast the message to all clients except the new one

  // Listen for incoming messages from the client
    while ((n = recv(connfd, buf, sizeof(buf), 0)) > 0) {
        buf[n] = '\0';   // Null-terminate the received message
        if (strcmp(buf, "exit") == 0) {
            break;       // Exit the loop if the client sends "exit"
        }

      // Broadcast the message to all clients
        char message[BUFSIZE];
        sprintf(message, "%s: %s", username, buf);  // Format the message with the client's username
        broadcast_message(message, connfd);         // Send the message to all other clients
    }

    // Client disconnected, so remove them from the list
    remove_client(connfd);

    // Inform other clients that the user has left
    char leave_message[BUFSIZE];
    sprintf(leave_message, "%s has left the chat\n", username);  // Prepare the leave message
    broadcast_message(leave_message, connfd);                    // Broadcast the leave message

    close(connfd);  // Close the connection with the client
    return NULL;
}

// Function to broadcast a message to all clients except the sender
void broadcast_message(char *message, int sender_fd) {
    pthread_mutex_lock(&clients_mutex);  // Lock the mutex to safely access the shared client list

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] != NULL && clients[i]->connfd != sender_fd) {
            send(clients[i]->connfd, message, strlen(message), 0);  // Send the message to each client
        }
    }

    pthread_mutex_unlock(&clients_mutex);  // Unlock the mutex after sending the message
}

// Function to add a new client to the client list
void add_client(client_t *new_client) {
    pthread_mutex_lock(&clients_mutex);  // Lock the mutex to safely add a new client to the list

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] == NULL) {
            clients[i] = new_client;  // Add the new client to the list
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);  // Unlock the mutex after adding the client
}

// Function to remove a client from the client list
void remove_client(int connfd) {
    pthread_mutex_lock(&clients_mutex);  // Lock the mutex to remove a client from the list

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] != NULL && clients[i]->connfd == connfd) {
            free(clients[i]);     // Free the memory allocated for the client structure
            clients[i] = NULL;    // Set the client pointer to NULL to mark the slot as available
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);  // Unlock the mutex after removing the client
}

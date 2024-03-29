#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, char const *argv[])
{
    
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        printf("Error creating socket. Terminating client...\n");
        return -1;
    }
    else
    {
        printf("Client socket created succesfully.\n");
    }
    

    struct sockaddr_in svrAddress;
    svrAddress.sin_family = AF_INET;
    svrAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    svrAddress.sin_port = htons(50000);


    int connectionResult = connect(clientSocket, (struct sockaddr *)&svrAddress, sizeof(svrAddress));
    if (connectionResult == -1)
    {
        printf("Error establishing connection. Terminating client...\n");
    }
    else
    {
        printf("Connection Established.\n");
    }
    

    char credentials[20] = {};
    char authentication[30] = {};

    sprintf(credentials, "%s,%s", argv[1], argv[2]);

    int sntBytes = send(clientSocket, credentials, strlen(credentials) + 1, 0);
    if (sntBytes == -1)
    {
        printf("Error sending password to server. Terminating client...\n");
        return -1;
    }
    printf("Login Info sent to server.\n");
    printf("Waiting for response...\n");

    int rcvdBytes = recv(clientSocket, authentication, sizeof(authentication), 0);
    if (rcvdBytes == -1)
    {
        printf("Error receiving authentication from server. Terminating client...\n");
        return -1;
    }
    else if (rcvdBytes == 0)
    {
        printf("Server closed connection. Terminating client...\n");
        return -1;        
    }
    else
    {
        printf("Received from the server --> %s\n", authentication);
    }

    close(clientSocket); 

    return 0;
}

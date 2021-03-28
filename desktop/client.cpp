#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
using namespace std;

// Client side TCP socket
int main(int argc, char *argv[])
{
    // Compile: g++ client.cpp
    // Input: ./a.out 127.0.0.1 12345 (IP + Port)
    // Terminate: exit

    if(argc != 3)
    {
        cerr << "Usage: ip_address port" << endl; exit(0); 
    } 
    
    // Grab the IP address and port number 
    char *serverIp = argv[1]; 
    int port = atoi(argv[2]); 

    // Message buffer 
    char msg[1500]; 

    // Socket and connection tools 
    struct hostent* host = gethostbyname(serverIp); 
    sockaddr_in clientAddr;   
    bzero((char*)& clientAddr, sizeof(clientAddr)); 
    clientAddr.sin_family = AF_INET; 
    clientAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    clientAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);

    // Try to connect
    int status = connect(clientSd, (sockaddr*) &clientAddr, sizeof(clientAddr));
    if(status < 0)
    {
        cout << "Error connecting to socket!" << endl; exit(0);
    }
    cout << "Connected to the server!" << endl;

    int bytesRead, bytesWritten = 0;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    while(1)
    {
        cout << "> ";
        string data;
        getline(cin, data);
        memset(&msg, 0, sizeof(msg)); // Clear the buffer
        strcpy(msg, data.c_str());

        if(data == "exit")
        {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            break;
        }

        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        cout << "Awaiting server response..." << endl;
        memset(&msg, 0, sizeof(msg)) ; // Clear the buffer
        bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);

        // End connection
        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
            break;
        }

        cout << "Server: " << msg << endl;
    }

    // Close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    close(clientSd);

    // Session end
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) << " secs" << endl;
    cout << "Connection closed" << endl;

    return 0;    
}
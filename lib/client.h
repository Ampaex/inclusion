#ifndef CLIENT_H
#define CLIENT_H

#include "group.h"
#include "message.h"
#include "user.h"
#include <fstream>
#include <iostream>
#include <sstream>
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
#include <thread>
using namespace std;

class Client 
{

    public:

        // Attributes
        int clientSd;
        User user;
        Group group;
        string data;
        // Attributes
        vector<string> groups;
        bool responseAvailable;
        string lastListen;
        bool exitListen;

        // Constructor
        Client() { user = User(); group = Group(); responseAvailable = false; data = "";};
        ~Client() {}

        // Setters
        void setGroup( Group group );
        void setUser( User newUser );
        void setLanguage( string &lang );

        // Methods
        bool addGroup( string title );
        bool removeGroup( Group group );
        string processClassType(string &msg);

        // Socket: Connection
        void startConnection(char *ip, int port);
        void listenConnection();
        void receiveAnswer( string &msg );
        void checkRequest( string &data );
        void endConnection();
}; 

#endif // CLIENT_H

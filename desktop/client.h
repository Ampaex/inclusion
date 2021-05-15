#ifndef CLIENT_H
#define CLIENT_H

#include "../lib/group.h"
#include "../lib/message.h"
#include "../lib/user.h"
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
using namespace std;

class Client 
{
    private:

        // Attributes
        vector<string> groups;

    public:

        // Attributes
        int clientSd;
        User user;
        Group group;

        // Constructor
        Client() { user = User(); group = Group(); }
        ~Client() {}

        // Setters
        void setGroup( Group group );

        // Methods
        bool addGroup( string title );
        bool removeGroup( Group group );

        // Socket: Connection
        void startConnection(char *ip, int port);
        void listenConnection();
        void receiveAnswer( string &msg );
        void sendRequest( string &data );
        void endConnection();
}; 

#endif // CLIENT_H
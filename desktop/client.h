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
        User user;
        Group group;

        // Constructor
        Client() { user = User(); group = Group(); }
        ~Client() {}

        // Setters
        void setGroup( Group group );

        // Methods
        bool addGroup( Group group );
        bool addMessage( Message message, Group group );
        bool removeGroup( Group group );

        void receiveAnswer( string &msg );
        void sendRequest( string &data );
        void startConnection(int &clientSd, char *ip, int port);
        void endConnection(int &clientSd);
}; 

#endif // CLIENT_H
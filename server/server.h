#ifndef SERVER_H
#define SERVER_H

#include "../lib/group.h"
#include "../lib/message.h"
#include "../lib/user.h"
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

class Server 
{
    private:

        // Attributes
        int port;
        vector<Group> groups;
        vector<string> titles;
        vector<User> users;

    public:

        // Constructor
        Server( int port );
        ~Server() {}

        // Getters
        vector<string> getTitles() { return titles; }
        Group getGroup( string title );
        vector<User> getUsers() { return users; }

        // Methods
        bool addGroup( Group group );
        bool addMessage( Message message, Group group );
        bool addUser( User user );
        bool addUserToGroup( User user, Group group );
        bool removeGroup( Group group );
        bool removeUser( User user );
};

#endif // SERVER_H
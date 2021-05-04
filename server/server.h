#ifndef SERVER_H
#define SERVER_H

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

class Server 
{
    private:

        // Attributes
        vector<Group> groups;
        vector<User> users;

    public:

        // Constructor
        Server() {}
        ~Server() {}

        // Getters
        Group getGroup( string title );
        vector<Group> getGroups() { return groups; }
        vector<User> getUsers() { return users; }

        // Methods
        bool addGroup( Group group );
        bool addMessage( Message message, Group group );
        bool addUser( User user );
        bool addUserToGroup( User user, Group group );
        bool inGroup( string title, User user );
        bool parseGroup( string &msg );
        bool parseMessage( string &msg );
        bool parseNewUser( string &msg );
        bool parseUserGroup( string &msg );
        bool removeGroup( Group group );
        bool removeUser( User user );

        string parseType( string &msg );
};

#endif // SERVER_H
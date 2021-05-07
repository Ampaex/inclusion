#ifndef SERVER_H
#define SERVER_H

#include "../lib/group.h"
#include "../lib/message.h"
#include "../lib/user.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <tuple> 
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
        vector<tuple<User, string>> users;

    public:

        // Constructor
        Server();
        ~Server() {}

        // Getters
        Group getGroup( string title );
        vector<Group> getGroups() { return groups; }p
        User getUser( string name );
        vector<tuple<User, string>> getUsers() { return users; }

        // Methods
        bool addNewGroup( Group group );
        bool addNewUser( User user );
        bool addMessageToGroup( Message message, Group group );
        bool addUserToGroup( User user, Group group );
        bool isUserInGroup( User user, string title );
        bool removeGroup( Group group );
        bool removeUser( User user );

        // Socket: Connection
        void handleRequest( string &data,  string &message );
        void startConnection( int &serverSd, int &clientSd, int port );
        void receiveConnection();
        void endConnection( int &serverSd, int &clientSd );

        // Socket: Data
        string processClassType( string &msg );
        bool processGroupData( string &data, string &msg );
        bool addNewUser( string &msg );
        bool addMessageToGroup( string &msg, Group &group );
        bool addUserToGroup( string &msg, Group &group );
};

#endif // SERVER_H
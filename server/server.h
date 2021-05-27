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
#include <thread>
#include <tuple> 
#include <pthread.h>
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

        // Attributes
        int clientSd;
        int serverSd;
        int currentConnections;
        int maxConnections;

        // Constructor
        Server();
        ~Server() {}

        // Getters
        Group getGroup( string title );
        vector<Group> getGroups() { return groups; }
        User getUser( string name );
        vector<tuple<User, string>> getUsers() { return users; }

        // Setters
        void setGroup( Group group );

        // Methods
        bool addGroup( Group group );
        bool addUser( User user );
        bool removeGroup( Group group );
        bool removeUser( User user );

        // Socket: Connection
        void startConnection( int port );
        void listenConnection( int client );
        void receiveConnection();
        void receiveRequest( string &data,  string &message );
        void endConnection();

        // Socket: Data management
        string processClassType( string &msg );
        bool processGroupRequest( string &data, string &msg );
        bool receivedUser( string &msg );
        bool receivedMessage( string &msg, Group &group );
        bool receivedGroupRequest( string &msg, Group &group );
};

#endif // SERVER_H
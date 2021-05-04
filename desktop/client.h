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
        vector<Group> groups;
        User user;

    public:

        // Constructor
        Client() {}
        ~Client() {}

        // Getters
        Group getGroup( string title );
        User getUser() { return user; }

        // Setters
        void setUser( User user ) { this->user = user; }

        // Methods
        bool addGroup( Group group );
        bool addMessage( Message message, Group group );
        bool removeGroup( Group group );
}; 

#endif // CLIENT_H
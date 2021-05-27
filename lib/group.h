#ifndef GROUP_H
#define GROUP_H

#include "message.h"
#include "user.h"
#include <iostream>
#include <string>
#include <vector>

const int limit = 100;
using namespace std;

class Group
{
    private:

        // Attributes
        vector<Message> messages;
        string title;
        vector<User> users;

    public:

        // Constructor
        Group();
        Group( string title );

        // Getters
        vector<Message> getMessages() { return messages; }
        string getTitle() { return title; }
        vector<User> getUsers() { return users; }

        // Setters
        void setMessages( vector<Message> messages );
        void setTitle( string title );
        void setUsers( vector<User> users );

        // Methods
        void addMessage( Message message );
        bool addUser( User user );
        bool removeUser( User user );

        // Operators
        friend ostream& operator<<(ostream& os, const Group& group);
};

#endif // GROUP_H
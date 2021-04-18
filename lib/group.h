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
        Group( string title, User user );

        // Getters
        vector<Message> getMessages() { return messages; }
        string getTitle() { return title; }
        vector<User> getUsers() { return users; }

        // Setters
        void setTitle( string title );

        // Methods
        void addMessage( Message message );
        bool addUser( User user );
        bool removeUser( User user );
};

#endif // GROUP_H
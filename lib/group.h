#ifndef GROUP_H
#define GROUP_H

#include "message.h"
#include "user.h"
#include <string>
#include <vector>

class Group
{
    private:

        // Attributes
        unsigned int groupID;
        std::string title;
        std::vector<User> users;
        std::vector<Message> messages;
        // Language vector: Every time a user is added, check if language exists

    public:

        // Constructor
        Group( unsigned int group, std::string title );

        // Getters
        unsigned int getGroup() { return groupID; }
        std::string getTitle() { return title; }

        // Setters
        void setGroup( unsigned int group );
        void setTitle( std::string title );

        // Methods
        void addMessage( Message message );
        bool addUser( User user );
        bool removeUser( User user );

    };

#endif // GROUP_H
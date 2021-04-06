#ifndef GROUP_H
#define GROUP_H

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
        bool addUser( User user );
        bool removeUser( User user );

    };

#endif // GROUP_H
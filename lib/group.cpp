#include "group.h"
#include <iostream>

using namespace std;

// Constructor

Group::Group( unsigned int group, string title )
{
  this->groupID = group;
  this->title = title;
}

// Setters

void Group::setGroup( unsigned int group )
{
  this->groupID = group;
}

void Group::setTitle( string user )
{
  this->title = user;
}

// Methods

bool Group::addUser( User user ) 
{
    bool add = true;

    // Iterate trough existing users
    for (int i = 0; i < this->users.size(); i++) {

        // If the current user exists, do not add it
        if (this->users[i].getUser() == user.getUser()) {
            add = false;
            break;
        }
    }

    // Add the user if it does not exist yet
    if (add) this->users.push_back(user);

    // Returns true if added, false if not
    return add;
}

bool Group::removeUser( User user ) 
{
    bool remove = false;

    // Iterate trough existing users
    for (int i = 0; i < this->users.size(); i++) {

        // If the current user has the same name as 
        // the user to remove, delete it
        if (this->users[i].getUser() == user.getUser()) {
            remove = true;
            this->users.erase(this->users.begin() + i);
            break;
        }
    }

    // Returns true if removed, false if not
    return remove;
}

// Sample:

int main( int argc, char *argv[], char *envp[] )
{
    Group g = Group(0,"Informática");
    cout << g.getGroup() << endl;
    cout << g.getTitle() << endl;
}
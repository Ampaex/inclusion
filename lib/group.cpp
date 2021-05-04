// g++ -c group.cpp

#include "group.h"

using namespace std;

//////////////////////
//      GROUP       //
//////////////////////

// Constructor

Group::Group()
{
  this->title = "";
}

Group::Group( string title )
{
  this->title = title;
}

// Setters

void Group::setTitle( string user )
{
  this->title = user;
}

// Methods

void Group::addMessage( Message message ) 
{
    // Add message to message list
    this->messages.push_back(message);

    // Remove first message if limit is surpassed
    if (this->messages.size() > limit) {
        this->messages.erase(this->messages.begin());
    }
}

bool Group::addUser( User user ) 
{
    bool add = true;

    // Iterate trough existing users
    for (int i = 0; i < this->users.size(); i++) {

        // If the current user exists, do not add it
        if (this->users[i].getName() == user.getName()) {
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
        if (this->users[i].getName() == user.getName()) {
            remove = true;
            this->users.erase(this->users.begin() + i);
            break;
        }
    }

    // Returns true if removed, false if not
    return remove;
}

// Operators

ostream& operator<<(ostream& os, const Group& group)
{
    // Print group
    os << "Group" << ':' << group.title << '/';

    // Print users
    for ( int i = 0; i < group.users.size(); i++ ) {
        os << group.users[i];
    }

    // Print messages
    for ( int i = 0; i < group.messages.size(); i++ ) {
        os << group.messages[i];
    }

    return os;
}

//////////////////////
//      MAIN        //
//////////////////////

// g++ -c *.cpp

// int main( int argc, char *argv[], char *envp[] )
// {
//     Group g = Group("Informática");
//     cout << g.getTitle() << endl;
// }
#include "user.h"

/////////////////////
//      USER       //
/////////////////////

// Constructor

User::User( string name, string language )
{
  this->name = name;
  this->language = language;
}

// Setters

void User::setLanguage( string language )
{
  this->language = language;
}

void User::setName( string name )
{
  this->name = name;
}

// Operators

ostream& operator<<(ostream& os, const User& user)
{
    os << "User" << ':' << user.name << ',' << user.language << '/';
    return os;
}

//////////////////////
//      MAIN        //
//////////////////////

// int main( int argc, char *argv[], char *envp[] )
// {
//     User u = User("ES","Juan");
//     cout << u.getName() << endl;
//     cout << u.getLanguage();
// }
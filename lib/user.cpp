#include "user.h"

/////////////////////
//      USER       //
/////////////////////

// Constructor

User::User( string language, string name )
{
  this->language = language;
  this->name = name;
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

//////////////////////
//      MAIN        //
//////////////////////

// int main( int argc, char *argv[], char *envp[] )
// {
//     User u = User("ES","Juan");
//     cout << u.getName() << endl;
//     cout << u.getLanguage();
// }
#include "user.h"

/////////////////////
//      USER       //
/////////////////////

// Constructor

User::User( string language, string user )
{
  this->languageID = language;
  this->userID = user;
}

// Setters

void User::setLanguage( string language )
{
  this->languageID = language;
}

void User::setUser( string user )
{
  this->userID = user;
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
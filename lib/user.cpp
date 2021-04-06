#include "User.h"
#include <iostream>

using namespace std;

User::User( string language, string user )
{
  this->languageID = language;
  this->userID = user;
}

void User::setLanguage( string language )
{
  this->languageID = language;
}

void User::setUser( string user )
{
  this->userID = user;
}

// Sample:

// int main( int argc, char *argv[], char *envp[] )
// {
//     User u = User("ES","Juan");
//     cout << u.getUser() << endl;
//     cout << u.getLanguage();

// }
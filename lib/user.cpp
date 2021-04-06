#include "user.h"
#include <iostream>

using namespace std;

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

// Sample:

int main( int argc, char *argv[], char *envp[] )
{
    User u = User("ES","Juan");
    cout << u.getUser() << endl;
    cout << u.getLanguage();

}
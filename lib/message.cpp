#include "message.h"
#include <iostream>

using namespace std;

// Constructor

Message::Message( int group, string message, string user )
{
  this->epoch = time(nullptr);
  this->groupID = group;
  this->message = message;
  this->userID = user;
}

// Setters

void Message::setMessage( string message )
{
  this->message = message;
}

// Sample:

int main( int argc, char *argv[], char *envp[] )
{
    Message m = Message(1,"Hola","Juan");
    cout << m.getMessage() << endl;
    cout << m.getEpoch();

}
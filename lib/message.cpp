#include "Message.h"

using namespace std;

Message::Message( int group, string message, string user )
{
  this->date = std::chrono::system_clock::now();
  this->groupID = group;
  this->message = message;
  this->userID = user;
}

void Message::setMessage( string message )
{
  this->message = message;
}
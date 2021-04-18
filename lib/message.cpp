#include "message.h"

//////////////////////
//      MESSAGE     //
//////////////////////

// Constructor

Message::Message( int group, string message, string language, string user )
{
  this->epoch = time(nullptr);
  this->groupID = group;
  this->languageID = language;
  this->message[language] = message;
  this->userID = user;
}

//////////////////////
//      MAIN        //
//////////////////////

// int main( int argc, char *argv[], char *envp[] )
// {
//     Message m = Message(1,"Hola","es_ES","Juan");
//     cout << m.getText("es_ES") << endl;
//     cout << m.getEpoch();
// }
#include "message.h"

//////////////////////
//      MESSAGE     //
//////////////////////

// Constructor

Message::Message( string message, string language, User user )
{
  this->epoch = time(nullptr);
  this->language = language;
  this->message[language] = message;
  this->user = user;
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
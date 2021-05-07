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

// Operators

ostream& operator<<(ostream& os, const Message& message)
{
    // Print language
    os << "Message" << ':';

    // Print messages
    for(map<string, string>::const_iterator it = message.message.begin(); it != message.message.end(); ++it) {
      os << it->first << "," << it->second << "/";
    }

    // Print user
    os << message.user;

    return os;
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
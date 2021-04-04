#include "message.h"

using namespace std;

message::message( char m)
{
  messages = m;

}

void message:: setMessage(char m){
    messages = m;
}

char message:: getMessage(){
     return messages;
}


#include "message.h"

//////////////////////
//      MESSAGE     //
//////////////////////

// Constructor

Message::Message( string message, string language, User user, bool translate )
{
  this->epoch = time(nullptr);
  this->language = language;
  this->message[language] = message;
  this->user = user;
  this->toTranslate.erase(std::remove(
    this->toTranslate.begin(), 
    this->toTranslate.end(), 
    this->language), 
    this->toTranslate.end());
  // Translate the message
  for (int i = 0; i < this->toTranslate.size() && translate; i++) 
  {
    this->translateMessage(this->toTranslate[i]);
  }

}

// Methods

void Message::translateMessage(string newLanguage) 
{

  // Create JSON
  CkJsonObject json;
  json.AppendString("q", this->message[this->language].c_str());
  json.AppendString("source", this->language.c_str());
  json.AppendString("target", newLanguage.c_str());
  json.AppendString("format","text");
  json.put_EmitCompact(false);

  // Create request and receive response
  CkHttp http;
  http.put_AcceptCharset("");
  http.put_UserAgent("");
  http.put_AllowGzip(false);
  CkHttpResponse *response = http.PostJson("https://translation.googleapis.com/language/translate/v2?key=AIzaSyBvGJF3P5AKmrq_b9eKmrdcqCcmr63bfi0", json.emit());

  // Response error
  if (http.get_LastMethodSuccess() != true) {
      std::cout << http.lastErrorText() << "\r\n";
  }
  // Response is valid
  else {
      json.Load(response->bodyStr());
      cout << "toTranslate:";
      for(string st: this->toTranslate)
      {
          cout << st << endl;
      }
      cout << "newMessage:" << json.stringOf("data.translations[0].translatedText");
      string newMessage = json.stringOf("data.translations[0].translatedText");
      this->setMessage(newMessage, newLanguage);
      delete response;
  }
}

// Operators

ostream& operator<<(ostream& os, const Message& message){
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
//   Message m = Message("Hola","es",User());

//   cout << m.getText("es") << endl;
//   cout << m.getText("en") << endl;
//   cout << m.getText("zh") << endl;

//   cout << m << endl;
// }

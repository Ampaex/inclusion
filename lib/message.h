#ifndef MESSAGE_H
#define MESSAGE_H

#include "user.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <CkHttp.h>
#include <CkHttpRequest.h>
#include <CkHttpResponse.h>
#include <CkJsonObject.h>
#include <CkJsonArray.h>
using namespace std;

class Message
{
    private:

        // Attributes
        time_t epoch;
        string language;
        map<std::string, std::string> message;
        vector<string> toTranslate {"es", "en", "zh"};
        User user;

    public:

        // Constructor
        Message( string message, string language, User user, bool translate );

        // Getters
        time_t getEpoch() { return epoch; }
        string getLanguage() { return language; }
        string getText( string language ) { return message[language]; }
        User getUser() { return user; }

        // Setters
        void setMessage( string message, string newLanguage ) { this->message[newLanguage] = message; };

        // Methods
        void translateMessage(string newLanguage);

        // Operators
        friend ostream& operator<<(ostream& os, const Message& message);
};

#endif // MESSAGE_H

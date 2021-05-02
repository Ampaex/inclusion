#ifndef MESSAGE_H
#define MESSAGE_H

#include "user.h"
#include <chrono>
#include <ctime> 
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Message
{
    private:

        // Attributes
        time_t epoch;
        // int groupID;
        string language;
        map<std::string, std::string> message;
        User user;

    public:

        // Constructor
        Message( string message, string language, User user );

        // Getters
        time_t getEpoch() { return epoch; }
        // int getGroup() { return groupID; }
        string getLanguage() { return language; }
        string getText( string language ) { return message[language]; }
        User getUser() { return user; }

        // Setters
        void setMessage( string message, string newLanguage ) { this->message[newLanguage] = message; };

        // Methods
};

#endif // MESSAGE_H
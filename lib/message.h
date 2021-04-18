#ifndef MESSAGE_H
#define MESSAGE_H

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
        int groupID;
        string languageID;
        string userID;
        map<std::string, std::string> message;

    public:

        // Constructor
        Message( int group, string message, string language, string user );

        // Getters
        time_t getEpoch() { return epoch; }
        int getGroup() { return groupID; }
        string getLanguage() { return languageID; }
        string getText( string language ) { return message[language]; }
        string getUser() { return userID; }

        // Setters
        void setMessage( string message ) { this->message[languageID] = message; };

        // Methods
};

#endif // MESSAGE_H
#ifndef MESSAGE_H
#define MESSAGE_H

#include <chrono>
#include <ctime> 
#include <string>

class Message
{
    private:

        // Attributes
        time_t epoch;
        int groupID;
        std::string languageID;
        std::string userID;
        // TODO: Create language dict
        // std::string message;

    public:

        // Constructor
        Message( int group, std::string message, std::string user );

        // Getters
        time_t getEpoch() { return epoch; }
        int getGroup() { return groupID; }
        std::string getText( std::string language ) { /*return message[language];*/ }
        std::string getUser() { return userID; }

        // Setters
        void setMessage( std::string message );

        // Methods

    };

#endif // MESSAGE_H
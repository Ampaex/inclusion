#ifndef MESSAGE_H
#define MESSAGE_H

#include <chrono> // https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
#include <ctime> 
#include <string>

class Message
{
    private:

        // Attributes
        auto date;
        int groupID;
        string message;
        string userID;

    public:

        // Constructor
        Message( int group, string message, string user );

        // Getters
        string getDate() { return date; }
        string getGroup() { return groupID; }
        string getMessage() { return message; }
        string getUser() { return userID; }

        // Setters
        void setMessage( string message );

        // Methods

    };

#endif // MESSAGE_H
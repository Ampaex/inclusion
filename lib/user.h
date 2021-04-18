#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User
{
    private:

        // Attributes
        string languageID;
        string userID;

    public:

        // Constructor
        User( string language, string user );

        // Getters
        string getLanguage() { return languageID; }
        string getName() { return userID; }

        // Setters
        void setLanguage( string language );
        void setUser( string user );

        // Methods
};

#endif // USER_H
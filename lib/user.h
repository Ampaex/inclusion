#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User
{
    private:

        // Attributes
        string language;
        string name;

    public:

        // Constructor
        User() { language = ""; name = ""; };
        User( string language, string user );

        // Getters
        string getLanguage() { return language; }
        string getName() { return name; }

        // Setters
        void setLanguage( string language );
        void setName( string name );

        // Methods

        // Operators
        friend ostream& operator<<(ostream& os, const User& user);
};


#endif // USER_H
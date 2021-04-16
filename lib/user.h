#ifndef USER_H
#define USER_H

#include <string>

class User
{
    private:

        // Attributes
        std::string languageID;
        std::string userID;

    public:

        // Constructor
        User( std::string language, std::string user );

        // Getters
        std::string getLanguage() { return languageID; }
        std::string getUser() { return userID; }

        // Setters
        void setLanguage( std::string language );
        void setUser( std::string user );

        // Methods

    };

#endif // USER_H
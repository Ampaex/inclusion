#ifndef MESSAGE_H
#define MESSAGE_H


class message
{
    private:
    
    char messages;   // Private attribute

    public:
    message(char m);
    void setMessage(char m);
    char getMessage();

    };

#endif // MESSAGE_H
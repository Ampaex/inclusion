// cd ../lib; g++ -c *.cpp; cd ../desktop/; g++ -o client client.cpp ../lib/message.o ../lib/user.o ../lib/group.o -lchilkat-9.5.0; ./client 127.0.0.1 12345

// Compile: cd ../lib; g++ -c *.cpp; cd ../server
// Compile: g++ -o client client.cpp ../lib/message.o ../lib/user.o ../lib/group.o -lchilkat-9.5.0
// Input: ./client 127.0.0.1 12345 (IP + Port)
// Terminate: exit

#include "client.h"

/////////////////////
//      CLIENT     //
/////////////////////

// Setters

void Client::setGroup( Group group )
{
    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size(); i++) {

        // If the current group exists, do not add it
        if (this->groups[i] == group.getTitle()) {
            this->group = group;
        }
    }
}

// Methods

bool Client::addGroup( string title ) 
{
    bool add = true;

    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size(); i++) {

        // If the current group exists, do not add it
        if (this->groups[i] == title) {
            add = false;
            break;
        }
    }

    // Add the group if it does not exist yet
    if (add) this->groups.push_back(title);

    // Returns true if added, false if not
    return add;
}

bool Client::removeGroup( Group group ) 
{
    bool remove = false;

    // Iterate trough existing users
    for (int i = 0; i < this->groups.size(); i++) {

        // If the current user has the same name as 
        // the user to remove, delete it
        if (this->groups[i] == group.getTitle()) {
            remove = true;
            this->groups.erase(this->groups.begin() + i);
            break;
        }
    }

    // Returns true if removed, false if not
    return remove;
}

// Socket: Connection

void Client::startConnection(char *ip, int port)
{     
    // Socket and connection tools 
    struct hostent* host = gethostbyname(ip); 
    sockaddr_in clientAddr;   
    bzero((char*)& clientAddr, sizeof(clientAddr)); 
    clientAddr.sin_family = AF_INET; 
    clientAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    clientAddr.sin_port = htons(port);
    this->clientSd = socket(AF_INET, SOCK_STREAM, 0);

    // Try to connect
    int status = connect(this->clientSd, (sockaddr*) &clientAddr, sizeof(clientAddr));
    if(status < 0)  
    { 
        cout << "Error connecting to socket!" << endl; exit(0); 
    }
    else            
    { 
        cout << "Connected to the server!" << endl; 
        this->listenConnection();
    }
}

void Client::listenConnection() {

    // Set socket variables
    char message[1500];
    string data;
    
    // Send and receive data
    while(1)
    {
        /////////////////////
        // Object handling //
        /////////////////////

        cout << "Client: "; 
        getline(cin, data); 
        this->sendRequest(data); // TODO: Change to suit Qt requests

        //////////////////////
        //   Send message   //
        //////////////////////

        memset(&message, 0, sizeof(message));
        strcpy(message, data.c_str());
        send(this->clientSd, (char*)&message, strlen(message), 0);

         // End connection: client
        if(data == "exit")
        {
            break;
        }
        // Wait for response
        else 
        {
            // cout << "Awaiting server response..." << endl;
        }    

        /////////////////////
        // Receive message //
        /////////////////////

        memset(&message, 0, sizeof(message));
        recv(this->clientSd, (char*)&message, sizeof(message), 0);

        // End connection: server
        if(!strcmp(message, "exit"))
        {
            cout << "Server: Session quit" << endl;
            break;
        }
        // Print message
        else 
        {
            cout << "Server: " << message << endl;
            string msg = message;
            this->receiveAnswer(msg);
        }

        cout << "---" << endl;
        cout << this->user << endl;
        cout << this->group << endl;
        cout << "---" << endl;
    }

    this->endConnection();
}

void Client::receiveAnswer( string &msg )
{
    bool valid = false;
    string title = "";
    string className = "";
    string delimiter = ":";

    // Fetch class
    className = msg.substr(0, msg.find(delimiter));
    msg.erase(0, msg.find(delimiter) + delimiter.length());

    // Request made: New user
    while (className == "Group" && msg != "")
    {
        // Fetch group
        delimiter = "/";
        title = msg.substr(0, msg.find(delimiter));
        msg.erase(0, msg.find(delimiter) + delimiter.length());
        valid = title != "" ? true : false;

        // Add group to the list
        if (valid)
        {
            this->addGroup(title);
        }
        
        // Fetch class
        delimiter = ":";
        className = msg.substr(0, msg.find(delimiter));
        msg.erase(0, msg.find(delimiter) + delimiter.length());

        // List of groups, no other object is allowed
        if (className == "Group") {
            valid = false;
        }
    }

    // Request made: Add user to group/Send new message
     if (className == "User" && valid)
    {
        string userName = "";
        string userLanguage = "";
        string messageText = "";
        string messageLanguage = "";
        vector<User> groupUsers;
        map<string, string> translatedMessages;
        User messageUser;

        // Set the new group and add it to the list if needed
        Group newGroup = Group(title);
        this->addGroup(title);

        // If the object is an user, continue
        while (className == "User" && msg != "")
        {
            // Fetch user
            delimiter = ",";
            userName = msg.substr(0, msg.find(delimiter));
            msg.erase(0, msg.find(delimiter) + delimiter.length());
            delimiter = "/";
            userLanguage = msg.substr(0, msg.find(delimiter));
            msg.erase(0, msg.find(delimiter) + delimiter.length());
            valid = userName != "" && userLanguage != "" ? true : false;

            // Add user to the list
            if (valid)
            {
                groupUsers.push_back( User(userName, userLanguage) );
            }
            
            // Fetch class
            delimiter = ":";
            className = msg.substr(0, msg.find(delimiter));
            msg.erase(0, msg.find(delimiter) + delimiter.length());
        }

        // Add user list to the group
        newGroup.setUsers(groupUsers);

        // If the object is an user or message, continue
        while (className == "Message" || className == "User" && msg != "")
        {
            if (className == "Message" && messageLanguage == "" && messageText == "")
            {
                delimiter = ",";
                messageLanguage = msg.substr(0, msg.find(delimiter));
                msg.erase(0, msg.find(delimiter) + delimiter.length());
                delimiter = "/";
                messageText = msg.substr(0, msg.find(delimiter));
                msg.erase(0, msg.find(delimiter) + delimiter.length());
                valid = messageLanguage != "" && messageText != "" ? true : false;
            }
            else if (className == "Message")
            {
                delimiter = ",";
                messageLanguage = msg.substr(0, msg.find(delimiter));
                msg.erase(0, msg.find(delimiter) + delimiter.length());
                delimiter = "/";
                messageText = msg.substr(0, msg.find(delimiter));
                msg.erase(0, msg.find(delimiter) + delimiter.length());
                valid = messageLanguage != "" && messageText != "" ? true : false; 

                if (valid)
                {
                    // Add message to translated messages
                    translatedMessages[messageLanguage] = messageLanguage;                    
                }
            }
            else if (className == "User")
            {
                delimiter = ",";
                userName = msg.substr(0, msg.find(delimiter));
                msg.erase(0, msg.find(delimiter) + delimiter.length());
                delimiter = "/";
                userLanguage = msg.substr(0, msg.find(delimiter));
                msg.erase(0, msg.find(delimiter) + delimiter.length());
                valid = userName != "" && userLanguage != "" ? true : false;

                if (valid)
                {
                    // Add messages to group
                    Message msg = Message(messageText, messageLanguage, User(userName, userLanguage), false);

                    // Loop through translated messages
                    for(map<string, string>::iterator it = translatedMessages.begin(); it != translatedMessages.end(); ++it) {
                        msg.setMessage(it->first, it->second);
                    }

                    // Set values into group
                    newGroup.addMessage(msg);
                }

                // Reset values
                messageLanguage = "";
                messageText = "";
                userName = "";
                userLanguage = "";
            }
            
            // Fetch class
            delimiter = ":";
            className = msg.substr(0, msg.find(delimiter));
            msg.erase(0, msg.find(delimiter) + delimiter.length());
        }

        if (valid)
        {
            this->group = newGroup;
        }
    }
}

void Client::sendRequest( string &data )
{
    stringstream buffer;

    // Qt: must set the user before calling this method

    // Set the user to send
    if (data == "user") 
    {   
        this->user.setName("Example"); // TODO: Add via Qt
        this->user.setLanguage("en"); // TODO: Add via Qt
        buffer << user;
        data = buffer.str();
    }

    // Qt: may need to change parameters in order to pass the group name

    // Set user in group
    else if (data == "group")
    {
        // TODO: Change group title by the one indicated by Qt
        if (this->user.getName() != "") // TODO: Change
        {
            buffer << "Group:" << "Group 1" << "/" << user; // TODO: Change
            data = buffer.str();
        }
        else 
        {
            data = "Error: Empty user or group";
        }
    } 

    // Qt: may need to change parameters in order to pass the group name

    // Set the message to send
    else if (data == "message")
    {
        // TODO: Change message by the one indicated by Qt
        if (user.getName() != "" && group.getTitle() != "")
        {
            Message message = Message("Ejemplo", "es", user, false); // TODO: Change
            buffer << "Group:" << group.getTitle() << "/" << message; 
            data = buffer.str();
        }
        else 
        {
            data = "Error: Empty user or group";
        }
    }
    // Quit request
    else if (data == "exit")
    {
        // Exit
    }
    // No valid data
    else 
    {
        data = "Error: Unknown";
    }
}

void Client::endConnection()
{     
    // Close the socket descriptors after we're all done
    close(this->clientSd);
}

//////////////////////
//      MAIN        //
//////////////////////

// Client side TCP socket
int main(int argc, char *argv[])
{

    // Check provided arguments
    if(argc != 3)
    {
        cerr << "Usage: ip_address port" << endl; exit(0); 
    } 
    
    // Start client
    Client client = Client();
    client.startConnection(argv[1], atoi(argv[2]));

    return 0;    
}
// Compile: cd ../lib; g++ -c *.cpp; cd ../server
// Compile: g++ -o server server.cpp ../lib/message.o ../lib/user.o ../lib/group.o
// Input: ./server 12345 (Port)
// Terminate: exit

#include "server.h"

/////////////////////
//      SERVER     //
/////////////////////

// Constructor

Server::Server()
{
    addGroup(Group("Group 1"));
    addGroup(Group("Group 2"));
    addGroup(Group("Group 3"));
    addGroup(Group("Group 4"));
    addGroup(Group("Group 5"));
}

// Getters

Group Server::getGroup( string title )
{
    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size(); i++) {

        // If found, return it
        if (this->groups[i].getTitle() == title) {
            return this->groups[i];
        }
    }

    // Return empty group
    return Group();
}

User Server::getUser( string name )
{
    // Iterate trough existing groups
    for (int i = 0; i < this->users.size(); i++) {

        // If found, return it
        if (get<0>(this->users[i]).getName() == name) {
            return get<0>(this->users[i]);
        }
    }

    // Return empty group
    return User();
}

// Setters

void Server::setGroup( Group group )
{
    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size(); i++) {

        // If found, return it
        if (this->groups[i].getTitle() == group.getTitle()) {
            this->groups[i] = group;
        }
    }
}

// Methods

bool Server::addGroup( Group group ) 
{
    bool add = true;

    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size(); i++) {

        // If the current group exists, do not add it
        if (this->groups[i].getTitle() == group.getTitle()) {
            add = false;
            break;
        }
    }

    // Add the groups if it does not exist yet
    if (add) this->groups.push_back(group);

    // Returns true if added, false if not
    return add;
}

bool Server::addUser( User user ) 
{
    bool add = true;

    // Iterate trough existing users
    for (int i = 0; i < this->users.size(); i++) {

        // If the current user exists, do not add it
        if (get<0>(this->users[i]).getName() == user.getName()) {
            add = false;
            break;
        }
    }

    // Add the user if it does not exist yet
    if (add) this->users.push_back(make_tuple(user, ""));

    // Returns true if added, false if not
    return add;
}

bool Server::removeGroup( Group group ) 
{
    bool remove = false;

    // Iterate trough existing users
    for (int i = 0; i < this->groups.size(); i++) {

        // If the current user has the same name as 
        // the user to remove, delete it
        if (this->groups[i].getTitle() == group.getTitle()) {
            remove = true;
            this->groups.erase(this->groups.begin() + i);
            break;
        }
    }

    // Returns true if removed, false if not
    return remove;
}

bool Server::removeUser( User user ) 
{
    bool remove = false;

    // Iterate trough existing users
    for (int i = 0; i < this->users.size(); i++) {

        // If the current user has the same name as 
        // the user to remove, delete it
        if (get<0>(this->users[i]).getName() == user.getName()) {
            remove = true;
            this->users.erase(this->users.begin() + i);
            break;
        }
    }

    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size(); i++) {

        // Remove the user if exists
        this->groups[i].removeUser( user );
    }

    // Returns true if removed, false if not
    return remove;
}

// Socket: connection

void Server::startConnection( int &serverSd, int &clientSd, int port )
{
    // Socket and connection tools 
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
 
    // Open stream oriented socket with internet address
    // Keep track of the socket descriptor
    serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0) { cerr << "Error establishing the server socket" << endl; exit(0); }

    // Bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, sizeof(servAddr));
    if(bindStatus < 0) { cerr << "Error binding socket to local address" << endl; exit(0); }
    else               { cout << "Waiting for a client to connect..." << endl; }

    // Listen for up to 5 requests at a time
    listen(serverSd, 5);

    // Receive a request from client using accept
    // We need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    // Accept, create a new socket descriptor to 
    // handle the new connection with client
    clientSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(clientSd < 0) { cerr << "Error accepting request from client!" << endl; exit(1); }
    else             { cout << "Connected with client!" << endl; }
}

// TODO: Threads for multiple clients
void Server::receiveConnection() {};

void Server::receiveRequest( string &data, string &msg )
{
    // Request class type from message
    bool valid = false;
    stringstream buffer;
    string classType = this->processClassType(msg);

    // Request rest of message depending on class type
    if (classType == "Group") 
    {
        valid = this->processGroupRequest(data, msg);
    }
    else if (classType == "User")
    {
        // Request and create user if possible
        valid = this->receivedUser(msg);

        // If valid, return existing groups titles
        if (valid) 
        {
            vector<Group> groups = this->getGroups();
            for (int i = 0; i < groups.size(); i++) 
            {
                // Append group
                buffer << "Group:" << groups[i].getTitle() << "/";
            }

            // Save buffer in data
            data = buffer.str();
        }   
    }

    // If not valid, return a retry message
    if (!valid)
    {
        data = "Retry";
    }
}

void Server::endConnection( int &serverSd, int &clientSd )
{     
    // Close the socket descriptors after we're all done
    close(clientSd);
    close(serverSd);
}

// Socket: data management

string Server::processClassType( string &msg )
{
    // Will return none if no class applies
    string classType = "None";
    string delimiter = ":";

    // Fetch class to build
    classType = msg.substr(0, msg.find(delimiter));

    // If class fetched is non applicable, change it to "None"
    if (classType != "Group" && classType != "Message" && classType != "User")
    {
        classType = "None";
    }

    // Erase extracted token (delimiter included)
    else
    {
        msg.erase(0, msg.find(delimiter) + delimiter.length());
    }

    // Return type
    return classType;
}

bool Server::processGroupRequest( string &data, string &msg ) 
{
    // Will return false if no user is created
    stringstream buffer;
    bool valid = false;
    string title = "";
    string delimiter = "/";

    // Fetch group
    title = msg.substr(0, msg.find(delimiter));
    valid = title != "" ? true : false;

    if (valid)
    {
        msg.erase(0, msg.find(delimiter) + delimiter.length());
        Group group = this->getGroup(title);

        // Check if group is empty (not valid)
        if (group.getTitle() == "")
        {
            valid = false;
        }
        // Process rest of the message
        else 
        {
            string classType = processClassType(msg);

            if (classType == "User")
            {
                valid = receivedGroupRequest( msg, group );
            }
            else if (classType == "Message")
            {
                valid = receivedMessage( msg, group );
            }
            else 
            {
                valid = false;
            }

            // If correct, return group
            if (valid)
            {
                // Save buffer in data
                buffer << group;
                data = buffer.str();
            }
        }
    }

    // Return whether user was created or not
    return valid;
}

bool Server::receivedUser( string &msg ) 
{
    // Will return false if no user is created
    bool valid = false;
    string name = "";
    string language = "";
    string delimiter = ",";

    // Fetch name
    name = msg.substr(0, msg.find(delimiter));
    valid = name != "" ? true : false;
    msg.erase(0, msg.find(delimiter) + delimiter.length());

    // Fetch language
    delimiter = "/";
    language = msg.substr(0, msg.find(delimiter));
    valid = language != "" && valid ? true : false;

    // Create user if possible
    if (valid) 
    {
        this->addUser( User(name, language) );
    }

    // Return whether user was created or not
    return valid;
}

bool Server::receivedMessage( string &msg, Group &group ) 
{
    // Will return false if no user is created
    bool valid = false;

    string messageText = "";
    string messageLanguage = "";
    string userName = "";
    string delimiter = ",";
    string classType = "";

    // Fetch message
    messageLanguage = msg.substr(0, msg.find(delimiter));
    msg.erase(0, msg.find(delimiter) + delimiter.length());
    delimiter = "/";
    messageText = msg.substr(0, msg.find(delimiter));
    msg.erase(0, msg.find(delimiter) + delimiter.length());
    valid = messageText != "" && messageLanguage != "" ? true : false;

    // Fetch user
    delimiter = ",";
    classType = processClassType(msg);
    if (classType == "User" && valid)
    {
        // Fetch user
        userName = msg.substr(0, msg.find(delimiter));
        msg.erase(0, msg.find(delimiter) + delimiter.length());
        delimiter = "/";
        valid = userName != "" ? true : false;
    }

    // Create message and add it to the group
    if (valid)
    {
        group.addMessage( Message(messageText, messageLanguage, this->getUser(userName)) );
        this->setGroup( group );
    }

    // Return whether user was created or not
    return valid;
}

bool Server::receivedGroupRequest( string &msg, Group &group ) 
{
    // Will return false if no user is created
    bool valid = false;
    string name = "";
    string delimiter = ",";

    // Fetch name
    name = msg.substr(0, msg.find(delimiter));
    valid = name != "" ? true : false;

    if (valid)
    {
        User user = this->getUser(name);

        if (user.getName() == "")
        {
            valid = false;
        }
        else 
        {
            group.addUser(user);
            this->setGroup( group );
        }
    }

    // Return whether user was created or not
    return valid;
}

//////////////////////
//      MAIN        //
//////////////////////

// Server side TCP socket
int main(int argc, char *argv[])
{
    // Check provided arguments
    if(argc != 2)
    {
        cerr << "Usage: port" << endl;
        cerr << "Example: ./server 12345" << endl;
        exit(0);
    }

    // Start server
    Server server = Server();

    // Set socket variables
    char message[1500];
    int serverSd, clientSd;
    string data;

    // Start connection
    server.startConnection(serverSd, clientSd, atoi(argv[1]));

    // Send and receive data
    while(1)
    {
        /////////////////////
        // Receive message //
        /////////////////////
        
        memset(&message, 0, sizeof(message)); // Clear the buffer
        recv(clientSd, (char*)&message, sizeof(message), 0);

        // End connection: client
        if(!strcmp(message, "exit"))
        {
            cout << "Client: Session quit" << endl;
            break;
        }
        // Print message
        else 
        {
            cout << "Client: " << message << endl;
        }

        //////////////////////
        // Request handling //
        //////////////////////

        string msg = message;
        server.receiveRequest(data, msg);
        cout << "Server: " << data << endl;

        //////////////////////
        //   Send message   //
        //////////////////////

        // REMOVE 
        cout << "---" << endl;
        for (int i = 0; i < server.getGroups().size(); i++)
            cout << server.getGroups()[i] << endl;
        cout << "---" << endl;
        // REMOVE

        memset(&message, 0, sizeof(message));
        strcpy(message, data.c_str());
        send(clientSd, (char*)&message, strlen(message), 0);

        // End connection: server
        if(data == "exit")
        {
            break;
        }
    }

    // End connection
    server.endConnection(serverSd, clientSd);

    return 0;   
}
// TODO: Group name list
// TODO: Receive name and check if valid
// TODO: Receive group message

#include "server.h"

/////////////////////
//      SERVER     //
/////////////////////

// Getters

Group Server::getGroup( string title )
{
    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size(); i++) {

        // If the current group exists, do not add it
        if (this->groups[i].getTitle() == title) {
            return this->groups[i];
        }
    }

    return Group();
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

bool Server::addMessage( Message message, Group group ) 
{
    bool add = false;

    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size(); i++) {

        // If the current group exists, add it
        if (this->groups[i].getTitle() == group.getTitle()) {
            this->groups[i].addMessage( message );
            add = true;
            break;
        }
    }

    // Returns true if added, false if not
    return add;
}

bool Server::addUser( User user ) 
{
    bool add = true;

    // Iterate trough existing users
    for (int i = 0; i < this->users.size(); i++) {

        // If the current user exists, do not add it
        if (this->users[i].getName() == user.getName()) {
            add = false;
            break;
        }
    }

    // Add the user if it does not exist yet
    if (add) this->users.push_back(user);

    // Returns true if added, false if not
    return add;
}

bool Server::addUserToGroup( User user, Group group ) 
{
    bool add = false;
    int index = 0;

    // Iterate trough existing users
    for (int i = 0; i < this->users.size(); i++) {

        // If the current user exists, add it
        if (this->users[i].getName() == user.getName()) {
            add = true;
            break;
        }
    }

    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size() && !add; i++) {

        // If the current group exists, add it
        if (this->groups[i].getTitle() == group.getTitle()) {
            add = true;
            index = i;
            break;
        }
    }

    // Add the user if it does not exist yet
    if (add) this->groups[index].addUser( user );

    // Returns true if added, false if not
    return add;
}

bool Server::inGroup( string title, User user )
{
    bool found = false;

    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size() && !found; i++) {

        // If the group exists, check if the user is in
        if (this->groups[i].getTitle() == title) {

            // Check if the user is in
            vector<User> auxUsers = this->groups[i].getUsers();
            for ( int j = 0; j < auxUsers.size() && !found; j++ ) {

                // If the user exists in the group, end
                if ( auxUsers[j].getName() == user.getName() ) {
                    found = true;
                    break;
                }
            }
        }
    }

    // Returns true if added, false if not
    return found;
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
        if (this->users[i].getName() == user.getName()) {
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

bool Server::parseGroup( string &msg ) 
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
        this->addUser(User(language, name));
    }

    // Return whether user was created or not
    return valid;
}

bool Server::parseMessage( string &msg ) 
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
        this->addUser(User(language, name));
    }

    // Return whether user was created or not
    return valid;
}

bool Server::parseNewUser( string &msg ) 
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
        this->addUser(User(language, name));
    }

    // Return whether user was created or not
    return valid;
}

bool Server::parseUserGroup( string &msg ) 
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
        this->addUser(User(language, name));
    }

    // Return whether user was created or not
    return valid;
}

string Server::parseType( string &msg )
{
    // Will return none if no class applies
    string classType = "None";
    string delimiter = ":";

    // Fetch class to build
    classType = msg.substr(0, msg.find(delimiter));

    // If class fetched is non applicable, change it to "None"
    if (classType != "Group" && classType != "Message" && classType != "User")
        classType = "None";

    // Erase extracted token (delimiter included)
    else
        msg.erase(0, msg.find(delimiter) + delimiter.length());

    // Return type
    return classType;
}

//////////////////////
//      MAIN        //
//////////////////////

// Server side TCP socket
int main(int argc, char *argv[])
{
    // Compile: g++ -o server server.cpp ../lib/message.o ../lib/user.o ../lib/group.o
    // Input: ./server 12345 (Port)
    // Terminate: exit

    // Check provided arguments
    if(argc != 2)
    {
        cerr << "Usage: port" << endl;
        cerr << "Example: ./server 12345" << endl;
        exit(0);
    }

    // Start server
    Server server = Server();
    server.addGroup(Group("Group 1"));
    server.addGroup(Group("Group 2"));
    server.addGroup(Group("Group 3"));
    server.addGroup(Group("Group 4"));
    server.addGroup(Group("Group 5"));

    // Set socket variables
    char msg[1500]; // Message buffer 
    int port = atoi(argv[1]); // Port
     
    // Socket and connection tools 
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
 
    // Open stream oriented socket with internet address
    // Keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
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
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0) { cerr << "Error accepting request from client!" << endl; exit(1); }
    else          { cout << "Connected with client!" << endl; }

    // Keep track of the session time
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);

    // Keep track of the amount of data sent
    int bytesRead, bytesWritten = 0;
    while(1)
    {
        // Receive a message from the client (listen)
        cout << "Client: ";

        memset(&msg, 0, sizeof(msg)); // Clear the buffer
        bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);

        // End connection: client
        if(!strcmp(msg, "exit"))
        {
            cout << "Client has quit the session" << endl;
            break;
        }

        /////////////////////
        // Object handling //
        /////////////////////

        // Parse class type from message
        stringstream buffer;
        string data;
        string msgString = msg;
        string classType = server.parseType(msgString);

        // TODO: Create objects
        if (classType == "Group") 
        {
            bool valid = server.parseMessage(msgString);

            // If correct, return valid
            if (valid) 
            {
                data = "Valid";
            }
        }
        else if (classType == "User")
        {
            // Parse and create user if possible
            bool valid = server.parseNewUser(msgString);

            // If valid, return existing groups titles
            if (valid) 
            {
                vector<Group> groups = server.getGroups();
                for (int i = 0; i < groups.size(); i++) 
                {
                    // Append group
                    buffer << groups[i];
                }

                // Save buffer in data
                data = buffer.str();
            }     
        }
        else 
        {
            data = "Continue";
        }

        /////////////////////
        //  End of handler //
        /////////////////////

        // Print client message
        cout << msg << endl;
        cout << "Server: " << data << endl;

        memset(&msg, 0, sizeof(msg)); // Clear the buffer
        strcpy(msg, data.c_str());

        // End connection: server
        if(data == "exit")
        {
            // Send to the client that server has closed the connection
            send(newSd, (char*)&msg, strlen(msg), 0);
            break;
        }

        // Send the message to client
        bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);
    }

    // Close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    close(newSd);
    close(serverSd);

    return 0;   
}
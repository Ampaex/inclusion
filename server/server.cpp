// TODO: Group name list
// TODO: Receive name and check if valid
// TODO: Receive group message

#include "server.h"

/////////////////////
//      SERVER     //
/////////////////////

// Constructor

Server::Server( int port ) 
{
    // // Message buffer 
    // char msg[1500];
     
    // // Socket and connection tools 
    // sockaddr_in servAddr;
    // bzero((char*)&servAddr, sizeof(servAddr));
    // servAddr.sin_family = AF_INET;
    // servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servAddr.sin_port = htons(port);
 
    // // Open stream oriented socket with internet address
    // // Keep track of the socket descriptor
    // int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    // if(serverSd < 0)
    // {
    //     cerr << "Error establishing the server socket" << endl;
    //     exit(0);
    // }

    // // Bind the socket to its local address
    // int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, sizeof(servAddr));
    // if(bindStatus < 0)
    // {
    //     cerr << "Error binding socket to local address" << endl;
    //     exit(0);
    // }
    // cout << "Waiting for a client to connect..." << endl;

    // // Listen for up to 5 requests at a time
    // listen(serverSd, 5);

    // // Receive a request from client using accept
    // // We need a new address to connect with the client
    // sockaddr_in newSockAddr;
    // socklen_t newSockAddrSize = sizeof(newSockAddr);

    // // Accept, create a new socket descriptor to 
    // // handle the new connection with client
    // int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    // if(newSd < 0)
    // {
    //     cerr << "Error accepting request from client!" << endl;
    //     exit(1);
    // }
    // cout << "Connected with client!" << endl;

    // // Keep track of the session time
    // struct timeval start1, end1;
    // gettimeofday(&start1, NULL);

    // // Keep track of the amount of data sent
    // int bytesRead, bytesWritten = 0;
    // while(1)
    // {
    //     // Receive a message from the client (listen)
    //     cout << "Awaiting client response..." << endl;
    //     memset(&msg, 0, sizeof(msg)); // Clear the buffer
    //     bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);

    //     if(!strcmp(msg, "exit"))
    //     {
    //         cout << "Client has quit the session" << endl;
    //         break;
    //     }

    //     cout << "Client: " << msg << endl;
    //     cout << ">";

    //     string data;
    //     getline(cin, data);
    //     memset(&msg, 0, sizeof(msg)); // Clear the buffer
    //     strcpy(msg, data.c_str());
    //     if(data == "exit")
    //     {
    //         // Send to the client that server has closed the connection
    //         send(newSd, (char*)&msg, strlen(msg), 0);
    //         break;
    //     }

    //     // Send the message to client
    //     bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);
    // }

    // // Close the socket descriptors after we're all done
    // gettimeofday(&end1, NULL);
    // close(newSd);
    // close(serverSd);

    // // Session end
    // cout << "********Session********" << endl;
    // cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    // cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) << " secs" << endl;
    // cout << "Connection closed..." << endl;
}

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
    Server server = Server( atoi(argv[1]) );
    Group group = Group("grupo");
    User user1 = User("en", "Ernesto");
    User user2 = User("es", "Antonio");
    Message message1 = Message("Hello", "en-UK", user1); message1.setMessage("Hola", "es-ES");
    Message message2 = Message("Adios", "es-ES", user2); message2.setMessage("Bye", "en-UK");

    group.addUser(user1);
    group.addUser(user2);
    group.addMessage(message1);
    group.addMessage(message2);

    server.addUser(user1);
    server.addUser(user2);
    server.addGroup(group);

    // Print users

    vector<User> users = server.getUsers();

    for (int i = 0; i < users.size(); i++) {
        cout << users[i].getName() << endl;
    }

    // Print messages in a language in group

    vector<Message> messages = server.getGroup("grup").getMessages();

    cout << "Messages in english:" << endl;

    for (int i = 0; i < messages.size(); i++) {
        cout << messages[i].getText("en-UK") << endl;
    }

    // Print user messages in group

    cout << "Ernesto's messages:" << endl;

    for (int i = 0; i < messages.size(); i++) {

        if ( messages[i].getUser().getName() == user1.getName() ) {
            // cout << messages[i].getText("en-UK") << endl;
            // cout << messages[i].getText("es-ES") << endl;
            cout << messages[i];
        }
    }

    // cout << message1.getText("en-UK") << endl;
    // cout << server.getGroup("grupo").getTitle() << endl;
    // cout << server.inGroup("grupo", user1) << endl;

    return 0;   
}
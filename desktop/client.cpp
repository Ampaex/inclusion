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

bool Client::addGroup( Group group ) 
{
    bool add = true;

    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size(); i++) {

        // If the current group exists, do not add it
        if (this->groups[i] == group.getTitle()) {
            add = false;
            break;
        }
    }

    // Add the group if it does not exist yet
    if (add) this->groups.push_back(group.getTitle());

    // Returns true if added, false if not
    return add;
}

bool Client::addMessage( Message message, Group group ) 
{
    bool add = false;

    // Iterate trough existing groups
    for (int i = 0; i < this->groups.size(); i++) {

        // If the current group exists, add it
        if (this->groups[i] == group.getTitle()) {
            this->group.addMessage( message );
            add = true;
            break;
        }
    }

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

void Client::receiveAnswer( string &msg )
{
    // TODO: Receive groups
    // TODO: Receive new user in group
    // TODO: Receive new message in group
}

void Client::sendRequest( string &data )
{
    stringstream buffer;

    // Set the user to send
    if (data == "user") 
    {
        this->user.setName("Example");
        this->user.setLanguage("en-UK");
        buffer << user;
        data = buffer.str();
    }
    // Set the message to send
    else if (data == "message")
    {
        if (user.getName() != "")
        {
            Message message = Message("Example", "es-ES", user);
            // TODO: Add message to current group
            // this->group.addMessage(message);
            buffer << "Group:" << group.getTitle() << "/" << message;
            data = buffer.str();
        }
        else 
        {
            data = "";
        }
    }
    // Set user in group
    else if (data == "group")
    {
        if (this->user.getName() != "")
        {
            // TODO: Add user to current group
            // this->group.addUser(user);
            buffer << "Group:" << this->group.getTitle() << "/" << user;
            data = buffer.str();
        }
        else 
        {
            data = "Not valid";
        }
    } 
}

void Client::startConnection(int &clientSd, char *ip, int port)
{     
    // Socket and connection tools 
    struct hostent* host = gethostbyname(ip); 
    sockaddr_in clientAddr;   
    bzero((char*)& clientAddr, sizeof(clientAddr)); 
    clientAddr.sin_family = AF_INET; 
    clientAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    clientAddr.sin_port = htons(port);
    clientSd = socket(AF_INET, SOCK_STREAM, 0);

    // Try to connect
    int status = connect(clientSd, (sockaddr*) &clientAddr, sizeof(clientAddr));
    if(status < 0)  { cout << "Error connecting to socket!" << endl; exit(0); }
    else            { cout << "Connected to the server!" << endl; }
}

void Client::endConnection(int &clientSd)
{     
    // Close the socket descriptors after we're all done
    close(clientSd);
}

//////////////////////
//      MAIN        //
//////////////////////

// Client side TCP socket
int main(int argc, char *argv[])
{
    // Compile: g++ -o client client.cpp ../lib/message.o ../lib/user.o ../lib/group.o
    // Input: ./client 127.0.0.1 12345 (IP + Port)
    // Terminate: exit

    // Check provided arguments
    if(argc != 3)
    {
        cerr << "Usage: ip_address port" << endl; exit(0); 
    } 
    
    // Start client
    Client client = Client();
    Group group = Group("Group 1");
    client.setGroup(group);

    // Set socket variables
    char message[1500];
    int clientSd;
    string data;

    // Start connection
    client.startConnection(clientSd, argv[1], atoi(argv[2]));

    // Send and receive data
    while(1)
    {
        /////////////////////
        // Object handling //
        /////////////////////

        cout << "> "; 
        // TODO: Qt request
        getline(cin, data);p 
        client.sendRequest(data);

        //////////////////////
        //   Send message   //
        //////////////////////

        memset(&message, 0, sizeof(message));
        strcpy(message, data.c_str());
        send(clientSd, (char*)&message, strlen(message), 0);

         // End connection: client
        if(data == "exit")
        {
            break;
        }
        // Wait for response
        else 
        {
            cout << "Awaiting server response..." << endl;
        }    

        /////////////////////
        // Receive message //
        /////////////////////

        memset(&message, 0, sizeof(message));
        recv(clientSd, (char*)&message, sizeof(message), 0);

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
            client.receiveAnswer(msg);
        }
    }

    // Close the socket descriptors after we're all done
    client.endConnection(clientSd);

    return 0;    
}
#include "client.h"

/////////////////////
//      CLIENT     //
/////////////////////

// Getters

Group Client::getGroup( string title )
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

bool Client::addGroup( Group group ) 
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

bool Client::addMessage( Message message, Group group ) 
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

bool Client::removeGroup( Group group ) 
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

//////////////////////
//      MAIN        //
//////////////////////

// Client side TCP socket
int main(int argc, char *argv[])
{
    // Compile: g++ -o client client.cpp ../lib/message.o ../lib/user.o ../lib/group.o
    // Input: ./client 127.0.0.1 12345 (IP + Port)
    // Terminate: exit

    // TODO: Receive groups
    // TODO: Receive new user in group
    // TODO: Receive new message in group
    // TODO: Send message

    // Check provided arguments
    if(argc != 3)
    {
        cerr << "Usage: ip_address port" << endl; exit(0); 
    } 
    
    // Start client
    Client client = Client();
    User user = User();
    Group group = Group();

    // Set socket variables
    char msg[1500]; // Message buffer 
    char *ip = argv[1]; // IP address
    int port = atoi(argv[2]); // Port

    // Socket and connection tools 
    struct hostent* host = gethostbyname(ip); 
    sockaddr_in clientAddr;   
    bzero((char*)& clientAddr, sizeof(clientAddr)); 
    clientAddr.sin_family = AF_INET; 
    clientAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    clientAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);

    // Try to connect
    int status = connect(clientSd, (sockaddr*) &clientAddr, sizeof(clientAddr));
    if(status < 0)  { cout << "Error connecting to socket!" << endl; exit(0); }
    else            { cout << "Connected to the server!" << endl; }

    int bytesRead, bytesWritten = 0;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    while(1)
    {
        cout << "> ";
        string data;
        getline(cin, data);
        stringstream buffer;

        // Set the user to send
        if (data == "user") 
        {
            client.setUser(User("en-UK", "Example"));
            user.setName("Example");
            user.setLanguage("en-UK");
            buffer << user;
            data = buffer.str();
        }
        // Set the message to send
        else if (data == "message")
        {
            if (user.getName() != "")
            {
                Message message = Message("Example", "es-ES", user);
                // Add message to current group
                group.addMessage(message);
                buffer << "Group:" << group.getTitle() << "/" << message;
                data = buffer.str();
            }
            else 
            {
                data = "";
            }
        }
        // Set user to group
        else if (data == "group")
       {
            if (user.getName() != "")
            {
                // Add message to current group
                group.addUser(user);
                buffer << "Group:" << group.getTitle() << "/" << user;
                data = buffer.str();
            }
            else 
            {
                data = "";
            }
       } 

        memset(&msg, 0, sizeof(msg)); // Clear the buffer
        strcpy(msg, data.c_str());

        // End connection: client
        if(buffer.str() == "exit" || data == "exit")
        {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            break;
        }

        // Send client message
        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        cout << "Awaiting server response..." << endl;
        memset(&msg, 0, sizeof(msg)) ; // Clear the buffer

        // Receive server message
        bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);

        // End connection: server
        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
            break;
        }

        // Print server message
        cout << "Server: " << msg << endl;
    }

    // Close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    close(clientSd);

    return 0;    
}
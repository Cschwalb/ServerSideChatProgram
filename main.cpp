#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == -1)
    {
        std::cerr<< "Error in creating socket, retry!"<<std::endl;
        return -1;
    }
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(1337);
    servAddr.sin_addr.s_addr = INADDR_ANY;


    if(bind(serverSocket, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1)
    {
        std::cerr<<"Couldn't bind to port 1337!"<<std::endl;
        close(serverSocket);
        return -1;
    }
    if(listen(serverSocket, 5 /* may change this is the backlog */) == -1)
    {
        std::cerr<<"Error listening on port 1337 with 5 as backlog"<<std::endl;
        close(serverSocket);
        return -1;
    }
    std::cout<<"Server listening on 1337 ... " << std::endl;
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if(clientSocket == -1)
    {
        std::cerr<<"Error accepting new connection."<<std::endl;
        close(serverSocket);
        return -1;
    }
    char message[1024]; //  1mb message
    while(true)
    {
        if(message[0] == '#')
        {
            break;
        }
        memset(message, 0, sizeof(message));
        recv(clientSocket, message, sizeof(message), 0);
        std::cout<<"Client:  " << message << std::endl;
        std::cout<<"Server:  ";
        memset(message, 0, sizeof(message));
        std::cin.getline(message, sizeof(message));
        send(clientSocket, message, strlen(message), 0);;
    }
    close(clientSocket);
    close(serverSocket);
    return 0;
}

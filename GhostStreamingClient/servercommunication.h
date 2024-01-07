#ifndef SERVERCOMMUNICATION_H
#define SERVERCOMMUNICATION_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>


class ServerCommunication
{
public:
    ServerCommunication();
    static std::vector<std::string> GetUsers(std::string url, std::string clientName);
    static std::vector<std::string> AddUser(std::string url, std::string clientName, std::string newUsername);

};

#endif // SERVERCOMMUNICATION_H

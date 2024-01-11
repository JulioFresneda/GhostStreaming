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
    static void GetUsers(std::string url, std::string clientName, std::vector<std::string>& userList, std::vector<std::string>& profilePics);
    static std::vector<std::string> AddUser(std::string url, std::string clientName, std::string newUsername, std::string profilePic);
    static void GetGenres();
};

#endif // SERVERCOMMUNICATION_H

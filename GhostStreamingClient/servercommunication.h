#ifndef SERVERCOMMUNICATION_H
#define SERVERCOMMUNICATION_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "json.hpp"

using json = nlohmann::json;

class ServerCommunication
{
public:
    ServerCommunication();
    static void GetUsers(std::string url, std::string clientName, std::vector<std::string>& userList, std::vector<std::string>& profilePics);
    static std::vector<std::string> AddUser(std::string url, std::string clientName, std::string newUsername, std::string profilePic);
    static std::map<std::string, std::vector<int>> GetGenres();
    static json GetMediaItem(int id);
};

#endif // SERVERCOMMUNICATION_H

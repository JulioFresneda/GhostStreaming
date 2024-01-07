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
    static std::vector<std::string> API_Request(std::string url, std::string clientName);
};

#endif // SERVERCOMMUNICATION_H

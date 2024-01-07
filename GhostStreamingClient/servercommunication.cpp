#include "servercommunication.h"
#include "json.hpp"

using json = nlohmann::json;

ServerCommunication::ServerCommunication() {}



size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<std::string> parseJson(const std::string& jsonString) {
    std::vector<std::string> result;
    auto j = json::parse(jsonString);

    // Assuming the JSON structure is an array of strings: ["string1", "string2", ...]
    for (const auto& item : j["users"]) {
        result.push_back(item.get<std::string>());
    }

    return result;
}


std::vector<std::string> ServerCommunication::API_Request(std::string url, std::string clientName) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::vector<std::string> user_list;

    // Your JSON data
    std::string jsonData = "{\"clientName\":\"" + clientName + "\"}";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonData.size());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            user_list = parseJson(readBuffer);
            for (const auto& str : user_list) {
                std::cout << str << std::endl;
            }
        }

        curl_slist_free_all(headers); // Free the header list
        curl_easy_cleanup(curl); // Clean up the CURL handle
    }

    curl_global_cleanup(); // Clean up global state
    return user_list;
}



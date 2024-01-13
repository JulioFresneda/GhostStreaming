#include "servercommunication.h"


ServerCommunication::ServerCommunication() {}



size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

template <typename T>
std::vector<T> parseJson(const std::string& jsonString, const std::string& key) {
    std::vector<T> result;
    auto j = json::parse(jsonString);

    // Check if the key exists and is an array
    if (key == ""){
        for (const auto& item : j) {
            result.push_back(item.get<T>());
        }
    }
    else{
        if (j.find(key) != j.end() && j[key].is_array()) {
            for (const auto& item : j[key]) {
                result.push_back(item.get<T>());
            }
        }
    }



    return result;
}

std::map<std::string, std::vector<int>> parseJsonMap(const std::string& jsonString) {
    std::map<std::string, std::vector<int>> result;
    auto j = json::parse(jsonString);

    for (auto& [key, value] : j.items()) {
        if (value.is_array()) {
            std::vector<int> numbers;
            for (const auto& item : value) {
                numbers.push_back(item.get<int>());
            }
            result[key] = numbers;
        }
    }

    return result;
}


void ServerCommunication::GetUsers(std::string url, std::string clientName, std::vector<std::string>& userList, std::vector<std::string>& profilePics) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;


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
            userList = parseJson<std::string>(readBuffer, "users");
            for (const auto& str : userList) {
                std::cout << str << std::endl;
            }

            profilePics = parseJson<std::string>(readBuffer, "profilePics");
            for (const auto& str : userList) {
                std::cout << str << std::endl;
            }


        }

        curl_slist_free_all(headers); // Free the header list
        curl_easy_cleanup(curl); // Clean up the CURL handle
    }

    curl_global_cleanup(); // Clean up global state

}



std::vector<std::string> ServerCommunication::AddUser(std::string url, std::string clientName, std::string newUsername, std::string profilePic) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::vector<std::string> user_list;

    // Your JSON data
    std::string jsonData = "{\"clientName\":\"" + clientName + "\", \"userName\":\"" + newUsername + "\", \"profilePic\":\"" + profilePic + "\"}";

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
            std::cerr << readBuffer;
        }

        curl_slist_free_all(headers); // Free the header list
        curl_easy_cleanup(curl); // Clean up the CURL handle
    }

    curl_global_cleanup(); // Clean up global state
    return user_list;
}

std::map<std::string, std::vector<int>> ServerCommunication::GetGenres() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string url = "http://0.0.0.0:18080/metadata/bygenre";
    std::map<std::string, std::vector<int>> genres;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            genres = parseJsonMap(readBuffer);
        }

        curl_slist_free_all(headers); // Free the header list
        curl_easy_cleanup(curl); // Clean up the CURL handle
    }

    curl_global_cleanup(); // Clean up global state
    return genres;
}


json ServerCommunication::GetMediaItem() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string url = "http://0.0.0.0:18080/metadata/bygenre";
    std::map<std::string, std::vector<int>> genres;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            genres = parseJsonMap(readBuffer);
        }

        curl_slist_free_all(headers); // Free the header list
        curl_easy_cleanup(curl); // Clean up the CURL handle
    }

    curl_global_cleanup(); // Clean up global state
    return genres;
}



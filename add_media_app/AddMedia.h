//
// Created by juliofgx on 12/27/23.
//

#ifndef ADDMEDIA_H
#define ADDMEDIA_H

#include "DatabaseManager.h"
#include <json.hpp>
#include <fstream>
#include <iostream>
#include "MediaMetadata.h"
#include "MediaCollection.h"

using json = nlohmann::json;



class AddMedia {
public:
    AddMedia(const json& config, DatabaseManager& dbm);
    ~AddMedia();

    static json loadJSONPath(const std::string& jsonPath);
    static bool isDirectory(const std::string& path);
    static std::string askForPath();
    MediaMetadata loadMediaMetadata(const json& j);

private:
    json mediaJson;
    json configJson;
    DatabaseManager dbm;
    bool collection;
    int mediaToChunks(const std::string& sourcePath, const std::string& storePath);




};



#endif //ADDMEDIA_H

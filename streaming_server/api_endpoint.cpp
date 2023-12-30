//
// Created by juliofgx on 12/23/23.
//

#include "api_endpoint.h"

APIEndpoint::~APIEndpoint()
= default;

APIEndpoint::APIEndpoint(const DatabaseManager &database): db(database) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Ghost Streaming";
    });

    CROW_ROUTE(app, "/hehe")([]() {
        //
        return "xddd";
    });
    CROW_ROUTE(app, "/media/<string>")([this](const std::string &mediaId) {
        crow::json::wvalue metadata = fetchMetadata(db, std::stoi(mediaId));
        return metadata;
    });
    CROW_ROUTE(app, "/collection/<string>")([this](const std::string &collectionId) {
        crow::json::wvalue collection = fetchCollection(db, std::stoi(collectionId));
        return collection;
    });



    app.port(18080).multithreaded().run();
}

std::string APIEndpoint::readFileContents(const std::string& filepath) {
    std::ifstream fileStream(filepath, std::ios::binary);
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}


crow::json::wvalue APIEndpoint::fetchMetadata(DatabaseManager &db, const int &mediaId) {
    // Logic to fetch metadata goes here
    // For this example, returning dummy data
    MediaMetadata metadata_raw = db.getMediaItem(mediaId);

    return to_json(metadata_raw);
}

crow::json::wvalue APIEndpoint::fetchCollection(DatabaseManager &db, const int &collectionId) {
    // Logic to fetch metadata goes here
    // For this example, returning dummy data
    MediaCollection metadata_raw = db.getMediaCollection(collectionId);
    return to_json(metadata_raw);
}

crow::json::wvalue APIEndpoint::to_json(MediaMetadata &metadata) {
    crow::json::wvalue json;
    json["video_path"] = metadata.getPath();
    json["title"] = metadata.getTitle();
    json["description"] = metadata.getDescription();
    json["id"] = metadata.getId();
    return json;
}

crow::json::wvalue APIEndpoint::to_json(MediaCollection &metadata) {
    crow::json::wvalue json;
    json["title"] = metadata.getTitle();
    json["description"] = metadata.getDescription();
    json["id"] = metadata.getId();
    return json;
}

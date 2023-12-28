//
// Created by juliofgx on 12/23/23.
//

#include "api_endpoint.h"

APIEndpoint::~APIEndpoint()
= default;

APIEndpoint::APIEndpoint(const DatabaseManager &database): db(database) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
    });

    CROW_ROUTE(app, "/hehe")([]() {
        //
        return "xddd";
    });
    CROW_ROUTE(app, "/metadata/<string>")([this](const std::string &mediaId) {
        crow::json::wvalue metadata = fetchMetadata(db, std::stoi(mediaId));
        return metadata;
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

crow::json::wvalue APIEndpoint::to_json(MediaMetadata &metadata) {
    crow::json::wvalue json;
    json["video_path"] = metadata.getPath();
    json["title"] = metadata.getTitle();
    json["description"] = metadata.getDescription();
    json["id"] = metadata.getId();
    return json;
}

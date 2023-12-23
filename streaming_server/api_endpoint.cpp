//
// Created by juliofgx on 12/23/23.
//

#include "api_endpoint.h"


APIEndpoint::APIEndpoint(const MetadataDB &database): db(database) {
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
    CROW_ROUTE(app, "/media/<string>")([this](const std::string &mediaId){
        int result = db.loadMediaSegments(mediaId);
        return result;
    });
    CROW_ROUTE(app, "/media/<string>/<int>")([this](const std::string &mediaId, int segmentNumber){
            std::string segmentPath = db.getSegmentPath(mediaId, segmentNumber);
            std::string fileContent = readFileContents(segmentPath);
            return crow::response{fileContent};
    });

    app.port(18080).multithreaded().run();
}

std::string APIEndpoint::readFileContents(const std::string& filepath) {
    std::ifstream fileStream(filepath, std::ios::binary);
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}


crow::json::wvalue APIEndpoint::fetchMetadata(MetadataDB &db, const int &mediaId) {
    // Logic to fetch metadata goes here
    // For this example, returning dummy data
    MovieMetadata metadata_raw = db.fetchMetadata(mediaId);

    return to_json(metadata_raw);
}

crow::json::wvalue APIEndpoint::to_json(const MovieMetadata &metadata) {
    crow::json::wvalue json;
    json["video_path"] = metadata.video_path;
    json["title"] = metadata.title;
    json["description"] = metadata.description;
    json["id"] = metadata.id;
    return json;
}

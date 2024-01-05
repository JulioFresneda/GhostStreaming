//
// Created by juliofgx on 12/23/23.
//
#include <filesystem>
#include "api_endpoint.h"

#include <string>
#include <bits/fs_path.h>

#include "UserManagement.h"


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
    CROW_ROUTE(app, "/media/<int>/chunks/mpd")
        ([&](int mediaId) {
            MediaMetadata metadata = db.getMediaItem(mediaId);
            std::string chunkFolder = metadata.getPath();
            std::string MPDName = "output.mpd";
            std::filesystem::path MPDPath = std::filesystem::path(chunkFolder) / MPDName;

            return APIEndpoint::getMPD(MPDName);
        });
    CROW_ROUTE(app, "/media/<int>/chunks/<string>")
    .methods("GET"_method)
    ([&](int mediaId, std::string chunkName) {
        // Logic to find the right chunk based on mediaId
        MediaMetadata metadata = db.getMediaItem(mediaId);

        std::string chunkFolder = metadata.getPath();
        std::filesystem::path chunkPath = std::filesystem::path(chunkFolder) / chunkName;

        // Read the chunk data
        std::ifstream file(chunkPath, std::ios::binary);
        std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        // Set the appropriate content type (e.g., video/mp4)
        crow::response resp;

        resp.code = 200; // OK
        resp.set_header("Content-Type", "video/mp4");
        resp.body = std::string(buffer.begin(), buffer.end());

        // You may need to set the content length header as well
        resp.add_header("Content-Length", std::to_string(buffer.size()));

        return resp;
    });
    CROW_ROUTE(app, "/connect").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
        // Parse the JSON body
        auto x = crow::json::load(req.body);

        if (!x) {
            return crow::response(400, "Invalid JSON");
        }

        // Access data from JSON object
        std::string clientName = x["clientName"].s();
        std::cout << "Received message from: " << clientName << std::endl;

        std::string machineInfo = x["machineInfo"].s();
        std::cout << "Machine Info: " << machineInfo << std::endl;

        std::string code = x["code"].s();
        std::cout << "Code: " << code << std::endl;



        ClientStatus userStatus = ClientManagement::checkClientStatus(db, clientName, machineInfo, code);


        // Create a JSON response
        crow::json::wvalue response;
        if(userStatus == ClientStatus::NEW) {
            response["authorized"] = false;
            response["status"] = "NEW";
            response["response"] = "New client. Ticket added.";
        }
        else {
            if(userStatus == ClientStatus::NEW_MACHINE) {
                response["authorized"] = false;
                response["status"] = "NEWMACHINE";
                response["response"] = "New machine. Ticket added.";

            }
            else {
                if(userStatus == ClientStatus::USER) {
                    response["authorized"] = true;
                    response["status"] = "USER";
                    response["response"] = "Welcome back.";

                }
                else {
                    response["authorized"] = false;
                    response["status"] = "CODE_ERROR";
                    response["response"] = "Incorrect code.";
                }
            }
        }

        return crow::response{response};
    });

    CROW_ROUTE(app, "/user/create").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
        // Parse the JSON body
        auto x = crow::json::load(req.body);

        if (!x) {
            return crow::response(400, "Invalid JSON");
        }

        // Access data from JSON object
        std::string clientName = x["clientName"].s();
        std::cout << "Received message from: " << clientName << std::endl;

        std::string userName = x["userName"].s();
        std::cout << "User: " << userName << std::endl;



        bool added = db.addUser(clientName, userName);
        // Create a JSON response
        crow::json::wvalue response;
        if(added) {
            response["status"] = "OK";
            response["response"] = "User added!";
        }
        else {
            response["status"] = "error";
            response["response"] = "User already exists!";
        }


        return crow::response{response};
    });

    CROW_ROUTE(app, "/user/delete").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
        // Parse the JSON body
        auto x = crow::json::load(req.body);

        if (!x) {
            return crow::response(400, "Invalid JSON");
        }

        // Access data from JSON object
        std::string clientName = x["clientName"].s();
        std::cout << "Received message from: " << clientName << std::endl;

        std::string userName = x["userName"].s();
        std::cout << "User: " << userName << std::endl;



        bool deleted = db.deleteUser(clientName, userName);
        // Create a JSON response
        crow::json::wvalue response;
        if(deleted) {
            response["status"] = "OK";
            response["response"] = "User deleted!";
        }
        else {
            response["status"] = "error";
            response["response"] = "User does not exist!";
        }


        return crow::response{response};
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

crow::response APIEndpoint::getMPD(const std::string& mpdFilePath) {
    std::ifstream file(mpdFilePath);
    if (!file) {
        return crow::response(404); // File not found
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string mpdContent = buffer.str();

    crow::response resp;
    resp.code = 200; // OK
    resp.set_header("Content-Type", "application/dash+xml");
    resp.body = mpdContent;

    return resp;
}

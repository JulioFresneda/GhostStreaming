//
// Created by juliofgx on 12/27/23.
//



#include <iostream>
#include <string>
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include "AddMedia.h"
#include "pugixml.hpp"


#include <string>


using json = nlohmann::json;

AddMedia::AddMedia(const json& config, DatabaseManager& dbm) : dbm(dbm) {
    std::string jsonPath = askForPath();


    json storeJson = config;
    std::string storePath = storeJson.value("store_path", "");

    if (!isDirectory(jsonPath))
    {
        collection = false;
        int new_id = AddMediaItem(jsonPath, storePath);
        modifyMPD(fullPath, "http://0.0.0.0:18080/media/" + std::to_string(new_id) + "/chunks/");
        std::cout << "Media added. ID: " << new_id << std::endl;
    }

    else
    {
        collection = true;
        int new_id = AddMediaCollection(jsonPath, storePath);
        std::cout << "Collection added. ID: " << new_id << std::endl;
    }
}

int AddMedia::AddMediaItem(const std::string& jsonPath, const std::string& storePath)
{

    mediaJson = loadJSONPath(jsonPath);
    std::string sourcePath = mediaJson.value("sourcePath", "");


    int cooked = mediaToChunks(sourcePath, storePath);
    if(!cooked)
    {
        MediaMetadata media_metadata = loadMediaMetadata(mediaJson, storePath);
        int id = dbm.addMediaItem(media_metadata);
        if(id == -1)
        {
            std::cout << "Error adding media" << std::endl;
        }
        return id;
    }
    return -1;


}

int AddMedia::AddMediaCollection(const std::string& jsonPath, const std::string& storePath)
{

    std::string filename = "collection.json";
    std::string dirname = "media";


    std::filesystem::path collectionPath = std::filesystem::path(jsonPath) / filename;
    std::filesystem::path mediasPath = std::filesystem::path(jsonPath) / dirname;


    DIR *dir;
    struct dirent *ent;

    std::vector<int> list_ids;

    if ((dir = opendir(mediasPath.c_str())) != nullptr)
    {
        while ((ent = readdir(dir)) != nullptr) {
            // Check if it's a regular file
            if (ent->d_type == DT_REG) {
                std::string mediaPath = (mediasPath / ent->d_name).c_str();
                int new_id = AddMediaItem(mediaPath, storePath);
                list_ids.push_back(new_id);
                std::cout << "Added media " << new_id << " from collection " << ent->d_name << std::endl;
            }
        }
        closedir(dir);
    }

    json collectionJson = loadJSONPath(collectionPath);
    MediaCollection media_collection = loadMediaCollection(list_ids, collectionJson, storePath);

    int id = dbm.addMediaCollection(media_collection);
    if(id == -1)
    {
        std::cout << "Error adding media collection" << std::endl;
    }
    return id;


}





AddMedia::~AddMedia()
= default;


int AddMedia::mediaToChunks(const std::string& sourcePath, const std::string& storePath)
{
    std::string outputFile = "output.mpd"; // Replace with your desired output file name
    fullPath = std::filesystem::path(storePath) / outputFile;

    std::string command = "ffmpeg -i " + sourcePath +
                          " -map 0 -c:v libx264 -c:a aac -b:v:0 5000k -s:v:0 1920x1080 -b:a 128k "
                          "-f dash -use_template 1 -use_timeline 1 "
                          "-init_seg_name 'init-stream$RepresentationID$.m4s' "
                          "-media_seg_name 'chunk-stream$RepresentationID$-$Number%05d$.m4s' " + fullPath.c_str();

    std::cout << "Running command" << std::endl;
    int result = std::system(command.c_str());




    if (result != 0) {
        std::cerr << "FFmpeg command failed." << std::endl;
        return 1;
    }

    std::cout << "FFmpeg processing complete." << std::endl;
    return 0;


}

json AddMedia::loadJSONPath(const std::string& jsonPath)
{
    std::ifstream collectionFile(jsonPath);
    json Json;
    collectionFile >> Json;
    return Json;

}

bool AddMedia::isDirectory(const std::string& path) {
    std::filesystem::path filePath = std::filesystem::path(path);
    return std::filesystem::exists(filePath) && std::filesystem::is_directory(filePath);
}

std::string AddMedia::askForPath() {
    std::string path;

    std::cout << "Enter the absolute path to the directory containing JSON files: ";
    std::getline(std::cin, path);

    // Basic validation of the path
    if (!std::filesystem::exists(path)) {
        std::cerr << "Error: The path does not exist." << std::endl;
        return "";
    }


    return path;
}

// Load a single media item from JSON
MediaMetadata AddMedia::loadMediaMetadata(const json& j, const std::string& storePath) {



    // Assuming 'j' is a JSON object representing a media item
    std::string title = j.value("title", "");
    std::string description = j.value("description", "");
    std::string releaseDate = j.value("releaseDate", "");
    int duration = j.value("duration", 0);
    std::string genres = j.value("genres", "");
    float rating = j.value("rating", NULL);
    std::string thumbnailPath = j.value("thumbnailPath", "");

    return MediaMetadata(title, description, releaseDate, duration, genres, rating, storePath, thumbnailPath);

}

MediaCollection AddMedia::loadMediaCollection(std::vector<int> mediaList, const json& j, const std::string& storePath) {



    // Assuming 'j' is a JSON object representing a media item
    std::string title = j.value("title", "");
    std::string description = j.value("description", "");
    std::string category = j.value("releaseDate", "");
    float rating = j.value("rating", 0);
    std::string genre = j.value("genre", "");
    std::string thumbnailPath = j.value("thumbnailPath", "");

    return MediaCollection(title, description, category, rating, genre, thumbnailPath, mediaList);

}


bool AddMedia::modifyMPD(const std::string& mpdFilePath, const std::string& apiBaseUrl) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(mpdFilePath.c_str());

    if (!result) {
        std::cerr << "XML Parse Error: " << result.description() << std::endl;
        return false;
    }

    // Iterate through SegmentTemplate elements
    for (pugi::xml_node adaptationSet : doc.child("MPD").child("Period").children("AdaptationSet")) {
        for (pugi::xml_node representation : adaptationSet.children("Representation")) {
            pugi::xml_node segmentTemplate = representation.child("SegmentTemplate");
            if (segmentTemplate) {
                std::string mediaAttributeValue = segmentTemplate.attribute("media").as_string();
                std::string newMediaAttributeValue = apiBaseUrl + mediaAttributeValue;

                std::string initAttributeValue = segmentTemplate.attribute("media").as_string();
                std::string newInitAttributeValue = apiBaseUrl + mediaAttributeValue;

                segmentTemplate.attribute("media").set_value(newMediaAttributeValue.c_str());
                segmentTemplate.attribute("initialization").set_value(newInitAttributeValue.c_str());

            }
        }
    }

    // Save the modified MPD file
    bool saveSucceeded = doc.save_file(mpdFilePath.c_str());
    return saveSucceeded;
}






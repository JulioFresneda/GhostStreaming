//
// Created by juliofgx on 12/27/23.
//



#include <iostream>
#include <string>
#include <filesystem>
#include "AddMedia.h"

using json = nlohmann::json;


AddMedia::AddMedia(const std::string& configPath) {
    std::string jsonPath = askForPath();

    if (!isDirectory(jsonPath))
    {
        collection = false;
        mediaJson = loadJSONPath(jsonPath);
        configJson = loadJSONPath(configPath);
        int cooked = mediaToChunks(mediaJson.value("sourcePath", ""), configJson.value("store_path", ""));
    }
}

int mediaToChunks(const std::string& sourcePath, const std::string& storePath)
{
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
MediaMetadata AddMedia::loadMediaMetadata(const json& j) {



    // Assuming 'j' is a JSON object representing a media item
    std::string title = j.value("title", "");
    std::string description = j.value("description", "");
    std::string releaseDate = j.value("releaseDate", "");
    int duration = j.value("duration", 0);
    std::string genre = j.value("genre", "");
    float rating = j.value("rating", NULL);
    std::string sourcePath = j.value("sourcePath", "");
    std::string thumbnailPath = j.value("thumbnailPath", "");




}

#include <json.hpp>
#include <fstream>
#include <iostream>
#include "MediaMetadata.h"
#include "MediaCollection.h"

using json = nlohmann::json;

int main() {
    return 0;

}

// Load a single media item from JSON
MediaMetadata loadMediaMetadata(const json& j) {
    // Assuming 'j' is a JSON object representing a media item
    int id = j.value("id", -1);
    std::string title = j.value("title", "");
    std::string description = j.value("description", "");
    std::string releaseDate = j.value("releaseDate", "");
    int duration = j.value("duration", 0);
    std::string genre = j.value("genre", "");
    std::string rating = j.value("rating", "");
    std::string thumbnailPath = j.value("thumbnailPath", "");

    return MediaMetadata(id, title, description, releaseDate, duration, genre, rating, thumbnailPath);
}

// Load a media collection along with its media items from a directory
MediaCollection loadMediaCollection(const std::string& directoryPath) {
    // Load the collection metadata JSON file
    std::ifstream collectionFile(directoryPath + "/collection.json");
    json collectionJson;
    collectionFile >> collectionJson;

    MediaCollection collection(
        collectionJson.value("title", ""),
        collectionJson.value("description", "")
    );

    // Load each media item JSON file
    // Assume file names are known or can be discovered (e.g., iterating over directory files)
    std::vector<std::string> mediaFilenames = {/* ... */};
    for (const auto& filename : mediaFilenames) {
        std::ifstream mediaFile(directoryPath + "/" + filename);
        json mediaJson;
        mediaFile >> mediaJson;

        MediaMetadata media = loadMediaMetadata(mediaJson);
        collection.addMedia(media);
    }

    return collection;
}

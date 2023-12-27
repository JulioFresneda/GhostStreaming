









/*
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
    std::vector<std::string> mediaFilenames = ;
    for (const auto& filename : mediaFilenames) {
        std::ifstream mediaFile(directoryPath + "/" + filename);
        json mediaJson;
        mediaFile >> mediaJson;

        MediaMetadata media = loadMediaMetadata(mediaJson);
        collection.addMedia(media);
    }

    return collection;
}
*/

#include <filesystem>
#include "AddMedia.h"

int main() {

        std::filesystem::path cwd = std::filesystem::current_path();
        std::filesystem::path configPath = cwd.parent_path() / "config.json";

        AddMedia add_media = AddMedia(std::filesystem::absolute(configPath));

        return 0;
}



// main.cpp

#include "VideoMetadata.h"
#include <iostream>

VideoMetadata promptForVideoMetadata() {
    VideoMetadata metadata;
    std::cout << "Enter video path: ";
    std::getline(std::cin, metadata.videoPath);
    std::cout << "Enter video title: ";
    std::getline(std::cin, metadata.title);
    std::cout << "Enter video description: ";
    std::getline(std::cin, metadata.description);
    return metadata;
}

int main() {
    MetadataDatabase db("/home/juliofgx/MetadataDB/metadata.db");  // Adjust the path to your database file
    VideoMetadata metadata = promptForVideoMetadata();

    if (db.addVideo(metadata)) {
        std::cout << "Video metadata added successfully." << std::endl;
    } else {
        std::cerr << "Failed to add video metadata." << std::endl;
    }db.listAllVideos();

    db.listAllVideos();

    return 0;
}


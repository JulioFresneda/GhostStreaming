// MediaCollection.cpp

#include "MediaCollection.h"

MediaCollection::MediaCollection() : id(-1) {}

MediaCollection::MediaCollection(const std::string& title,
    const std::string& description,
    const std::string& category,
    float rating,
    const std::string& genre,
    const std::string& thumbnailPath,
    std::vector<int> mediaList)
    : id(id), title(title),
    description(description),
    category(category),
    rating(rating),
    genre(genre),
    thumbnailPath(thumbnailPath),
    mediaList(mediaList){}




const std::vector<int>& MediaCollection::getMediaList() const {
    return mediaList;
}

// Implement other methods for managing the collection as needed ...

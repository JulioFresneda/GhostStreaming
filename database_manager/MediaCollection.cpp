// MediaCollection.cpp

#include "MediaCollection.h"

MediaCollection::MediaCollection() : id(-1) {}

MediaCollection::MediaCollection(const std::string& title, const std::string& description)
    : id(id), title(title), description(description){}




const std::vector<int>& MediaCollection::getMediaList() const {
    return mediaList;
}

// Implement other methods for managing the collection as needed ...

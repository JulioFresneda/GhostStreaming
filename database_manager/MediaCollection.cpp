// MediaCollection.cpp

#include "MediaCollection.h"

MediaCollection::MediaCollection() : id(-1) {}

MediaCollection::MediaCollection(const std::string& title, const std::string& description)
    : id(id), title(title), description(description) {}


// Implement other getters and setters ...

void MediaCollection::addMedia(const MediaMetadata& media) {
    mediaList.push_back(media);
}

const std::vector<MediaMetadata>& MediaCollection::getMediaList() const {
    return mediaList;
}

// Implement other methods for managing the collection as needed ...

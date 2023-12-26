// MediaCollection.h

#ifndef MEDIACOLLECTION_H
#define MEDIACOLLECTION_H

#include <string>
#include <vector>
#include "MediaMetadata.h"

class MediaCollection {
public:
    MediaCollection();
    MediaCollection(const std::string& title, const std::string& description);


    // ... Other getters and setters for each field ...

    void addMedia(const MediaMetadata& media);
    const std::vector<MediaMetadata>& getMediaList() const;
    // ... Other methods for managing the collection ...

private:
    int id = -1;                         // Unique identifier for the collection
    std::string title;
    std::string description;
    std::vector<MediaMetadata> mediaList; // List of MediaMetadata objects in this collection
};

#endif // MEDIACOLLECTION_H

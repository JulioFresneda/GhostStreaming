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


    void setId(int id){ this->id = id; }
    void addMediaToList(int id){ mediaList.push_back(id); }

    int getId(){ return id; }
    std::string getTitle(){ return title; }
    std::string getDescription(){ return description; }
    std::string getCategory(){ return category; }
    int getRating(){ return rating; }
    std::vector<int> getMediaList(){ return mediaList; }

    const std::vector<int>& getMediaList() const;
    // ... Other methods for managing the collection ...

private:
    int id = -1;                         // Unique identifier for the collection
    std::string title;
    std::string description;
    std::string category;
    int rating;
    std::vector<int> mediaList; // List of MediaMetadata objects in this collection
};

#endif // MEDIACOLLECTION_H

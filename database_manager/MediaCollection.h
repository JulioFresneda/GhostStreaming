// MediaCollection.h

#ifndef MEDIACOLLECTION_H
#define MEDIACOLLECTION_H

#include <string>
#include <vector>
#include "MediaMetadata.h"

class MediaCollection {
public:
    MediaCollection();
    MediaCollection(const std::string& title, const std::string& description,
        const std::string& category,
        float rating,
        const std::string& genre,
        const std::string& thumbnailPath,
        std::vector<int> mediaList);


    void setId(int id){ this->id = id; }
    void addMediaToList(int id){ mediaList.push_back(id); }

    int getId(){ return id; }
    std::string getTitle(){ return title; }
    std::string getDescription(){ return description; }
    std::string getCategory(){ return category; }
    float getRating(){ return rating; }
    std::string getThumbnailPath(){ return thumbnailPath; }
    std::string getGenre(){ return genre; }
    std::vector<int> getMediaList(){ return mediaList; }

    const std::vector<int>& getMediaList() const;
    // ... Other methods for managing the collection ...

private:
    int id = -1;                         // Unique identifier for the collection
    std::string title;
    std::string description;
    std::string category;
    float rating;
    std::string genre;
    std::string thumbnailPath;
    std::vector<int> mediaList; // List of MediaMetadata objects in this collection
};

#endif // MEDIACOLLECTION_H

// MediaMetadata.cpp

#include "MediaMetadata.h"

// Overload the << operator
std::ostream& operator<<(std::ostream& os, const MediaMetadata& media) {
    os << "MediaMetadata { id: " << media.id
       << ", title: " << media.title
       << " }";
    return os;
}

MediaMetadata::MediaMetadata() : duration(0), groupId(-1) {}

MediaMetadata::MediaMetadata(const std::string& title, const std::string& description,
                             const std::string& releaseDate, int duration, const std::string& genre,
                             float rating, const std::string& path, const std::string& thumbnailPath)
    : id(id), title(title), description(description), releaseDate(releaseDate),
      duration(duration), genre(genre), rating(rating), path(path), thumbnailPath(thumbnailPath) {}

    int collectionId = -1;
    int id = -1;


void MediaMetadata::setId(int id) {
    this->id = id;
}


int getId()
{
    return id;
};


const std::string& getDescription();
const std::string& getReleaseDate();
int getDuration();            // Duration in seconds
const std::string& getGenre();
float getRating();
const std::string& getPath();
const std::string& getThumbnailPath();
int getGroupId();



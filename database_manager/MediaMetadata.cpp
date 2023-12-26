// MediaMetadata.cpp

#include "MediaMetadata.h"

MediaMetadata::MediaMetadata() : id(-1), duration(0), groupId(-1) {}

MediaMetadata::MediaMetadata(int id, const std::string& title, const std::string& description,
                             const std::string& releaseDate, int duration, const std::string& genre,
                             const std::string& rating, const std::string& thumbnailPath)
    : id(id), title(title), description(description), releaseDate(releaseDate),
      duration(duration), genre(genre), rating(rating), thumbnailPath(thumbnailPath) {}

    int collectionId = -1;

int MediaMetadata::getId() const {
    return id;
}

void MediaMetadata::setId(int id) {
    this->id = id;
}

// Implement other getters and setters ...


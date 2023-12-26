// MediaMetadata.h

#ifndef MEDIAMETADATA_H
#define MEDIAMETADATA_H

#include <string>

class MediaMetadata {
public:
    MediaMetadata();
    MediaMetadata(int id, const std::string& title, const std::string& description,
                  const std::string& releaseDate, int duration, const std::string& genre,
                  const std::string& rating, const std::string& thumbnailPath);

    // Getters and Setters
    int getId() const;
    void setId(int id);
    // ... Other getters and setters for each field ...

private:
    int id;                  // Unique identifier
    std::string title;
    std::string description;
    std::string releaseDate;
    int duration;            // Duration in seconds
    std::string genre;
    std::string rating;
    std::string thumbnailPath;
    int groupId;             // ID of the group this media belongs to, if any
};

#endif // MEDIAMETADATA_H

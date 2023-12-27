// MediaMetadata.h

#ifndef MEDIAMETADATA_H
#define MEDIAMETADATA_H

#include <string>
#include <ostream>

class MediaMetadata {
public:
    MediaMetadata();
    MediaMetadata(const std::string& title, const std::string& description,
                  const std::string& releaseDate, int duration, const std::string& genre,
                  float rating, const std::string& path, const std::string& thumbnailPath);



    void setId(int id);
    // ... Other getters and setters for each field ...


    friend std::ostream& operator<<(std::ostream& os, const MediaMetadata& media);

private:
    int id;                  // Unique identifier
    std::string title;
    std::string description;
    std::string releaseDate;
    int duration;            // Duration in seconds
    std::string genre;
    float rating;
    std::string path;
    std::string thumbnailPath;
    int groupId;             // ID of the group this media belongs to, if any
};

#endif // MEDIAMETADATA_H

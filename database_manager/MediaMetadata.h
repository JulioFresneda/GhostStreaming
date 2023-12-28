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

    int getId();
    const std::string& getTitle() { return title; }
    const std::string& getDescription() { return description; }
    const std::string& getReleaseDate() { return releaseDate; }
    int getDuration() { return duration; }            // Duration in seconds
    const std::string& getGenre() { return genre; }
    float getRating() { return rating; }
    const std::string& getPath() { return path; }
    const std::string& getThumbnailPath() { return thumbnailPath; }
    int getGroupId() { return groupId; }

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

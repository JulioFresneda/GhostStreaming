// VideoMetadata.h

#ifndef VIDEOMETADATA_H
#define VIDEOMETADATA_H

#include <string>
#include <sqlite3.h>

struct VideoMetadata {
    std::string videoPath;
    std::string title;
    std::string description;
};

class MetadataDatabase {
public:
    MetadataDatabase(const std::string &dbPath);
    ~MetadataDatabase();
    bool addVideo(const VideoMetadata &metadata);
    void listAllVideos();

private:
    sqlite3 *db = nullptr;
};

#endif //VIDEOMETADATA_H

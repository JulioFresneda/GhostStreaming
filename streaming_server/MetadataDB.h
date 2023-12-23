//
// Created by juliofgx on 12/23/23.
//

#ifndef METADATADB_H
#define METADATADB_H

#include <sqlite3.h>
#include <string>

struct MovieMetadata {
    int id;
    std::string video_path;
    std::string title;
    std::string description;
};

class MetadataDB {
public:
    MetadataDB(const std::string &dbPath);

    ~MetadataDB();

    MovieMetadata fetchMetadata(int movieId);
    int loadMediaSegments(const std::string &mediaId);
    std::string getSegmentPath(const std::string &mediaId, int segmentNumber);

    [[nodiscard]] sqlite3 *getDB() const;


    // Other database methods...

private:
    sqlite3 *db;

    bool initDatabase(const std::string &dbPath);



    // Other private methods and members...
};


#endif //METADATADB_H

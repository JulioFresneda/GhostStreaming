// DatabaseManager.h

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>
#include <sqlite3.h>
#include "MediaMetadata.h"
#include "MediaCollection.h"

class DatabaseManager {
public:
    DatabaseManager(const std::string& dbPath);
    ~DatabaseManager();

    bool initializeDatabase();
    int addMediaItem(MediaMetadata& media);
    MediaMetadata getMediaItem(int id);
    void updateMediaItem(const MediaMetadata& media);
    void deleteMediaItem(int id);

    void addMediaCollection(const MediaCollection& collection);
    MediaCollection getMediaCollection(int id);
    // ... other methods as needed ...

private:
    sqlite3* db;
    std::string dbPath;

    void executeStatement(const std::string& sql);
    // ... other helper methods as needed ...
};

#endif // DATABASEMANAGER_H

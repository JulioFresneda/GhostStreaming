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

    int addMediaCollection(MediaCollection& collection);
    MediaCollection getMediaCollection(int id);

    bool getClientMetadata(const std::string& clientname, std::string &machineInfo, std::vector<std::string> &userList);
    void addTicket(const std::string& clientname, const std::string &machineInfo);

    sqlite3* loadDB(const std::string& dbPath);


private:
    std::string dbPath;

    void executeStatement(const std::string& sql);
    // ... other helper methods as needed ...
};

#endif // DATABASEMANAGER_H

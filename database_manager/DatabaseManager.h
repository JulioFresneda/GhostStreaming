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
    std::vector<MediaMetadata> getAllMediaItems();
    std::vector<int> getAllMediaItemIDs();

    int addMediaCollection(MediaCollection& collection);
    MediaCollection getMediaCollection(int id);

    bool getClientMetadata(const std::string& clientName, std::string& machineInfo, std::string& code);
    bool updateClientMetadata(const std::string& clientname, const std::vector<std::string>& userList);


    void addTicket(const std::string& clientName, const std::string &machineInfo);

    bool addUser(const std::string& clientName, const std::string &userName, const std::string &profilePic);
    bool deleteUser(const std::string& clientName, const std::string &userName);
    void getUsers(const std::string& clientName, std::vector<std::string>& user_list, std::vector<std::string>& profile_pics);

    sqlite3* loadDB(const std::string& dbPath);


private:
    std::string dbPath;

    void executeStatement(const std::string& sql);
    // ... other helper methods as needed ...
};

#endif // DATABASEMANAGER_H

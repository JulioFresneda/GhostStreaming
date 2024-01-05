//
// Created by juliofgx on 12/26/23.
//

// DatabaseManager.cpp

#include "DatabaseManager.h"
#include <iostream>
#include <sstream>


DatabaseManager::DatabaseManager(const std::string& dbPath) : dbPath(dbPath){
    initializeDatabase();
}

DatabaseManager::~DatabaseManager() {

}

sqlite3* DatabaseManager::loadDB(const std::string& dbPath) {
    sqlite3* db;
    sqlite3_open(dbPath.c_str(), &db);
    return db;
}

bool DatabaseManager::initializeDatabase() {



    // SQL statements to create tables
    const char* createMediaTableSql = R"(
        CREATE TABLE IF NOT EXISTS MediaMetadata (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT,
            description TEXT,
            releaseDate TEXT,
            duration INTEGER,
            genre TEXT,
            rating TEXT,
            path TEXT,
            thumbnailPath TEXT,
            groupId INTEGER
        );
    )";



    const char* createCollectionTableSql = R"(
        CREATE TABLE IF NOT EXISTS MediaCollection (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT,
            description TEXT,
            category TEXT,
            rating INTEGER,
            genre TEXT,
            thumbnailPath TEXT,
            mediaList TEXT
        );
    )";

    const char* createClientMetadataTableSql = R"(
        CREATE TABLE IF NOT EXISTS ClientMetadata (
            code TEXT PRIMARY KEY,
            clientName TEXT,
            machineInfo TEXT        );
    )";

    const char* createUserMetadataTableSql = R"(
        CREATE TABLE IF NOT EXISTS UserMetadata (
            userName TEXT,
            clientName TEXT,
            favList TEXT,
            repList TEXT,
            watchLater TEXT,
            watched TEXT,
            watching TEXT,
            PRIMARY KEY( userName, clientName)
        );
    )";

    const char* createTicketsTableSql = R"(
        CREATE TABLE IF NOT EXISTS Tickets (
            clientName TEXT,
            machineInfo TEXT
        );
    )";

    executeStatement(createMediaTableSql);
    executeStatement(createCollectionTableSql);
    executeStatement(createClientMetadataTableSql);
    executeStatement(createUserMetadataTableSql);
    executeStatement(createTicketsTableSql);



    return true;

}

MediaMetadata DatabaseManager::getMediaItem(int id)
{
    std::string sql = "SELECT id, title, description, releaseDate, duration, genre, rating, path, thumbnailPath, groupId "
                          "FROM MediaMetadata WHERE id = ?;";

    sqlite3_stmt* stmt;

    sqlite3* db = loadDB(dbPath);
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);

    MediaMetadata media = MediaMetadata();
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int metadata_id = sqlite3_column_int(stmt, 0);
        media = MediaMetadata(
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)),
            static_cast<float>(sqlite3_column_double(stmt, 6)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8))
        );
        media.setId(metadata_id);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return media;
}

std::vector<int> stringToVector(const std::string& str) {
    std::vector<int> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, ',')) {
        try {
            result.push_back(std::stoi(item));
        } catch (const std::invalid_argument& e) {
            // Handle the case where the conversion fails
            std::cerr << "Invalid argument: " << item << std::endl;
        } catch (const std::out_of_range& e) {
            // Handle the case where the integer is out of range
            std::cerr << "Integer out of range: " << item << std::endl;
        }
    }

    return result;
}


MediaCollection DatabaseManager::getMediaCollection(int id)
{
    std::string sql = "SELECT title, description, category, rating, genre, thumbnailPath, mediaList "
                          "FROM MediaCollection WHERE id = ?;";

    sqlite3_stmt* stmt;
    sqlite3* db = loadDB(dbPath);

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);

    MediaCollection collection = MediaCollection();
    if (sqlite3_step(stmt) == SQLITE_ROW) {

        std::string medialist_str = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        std::vector<int> mediaList = stringToVector(medialist_str);
        collection = MediaCollection(
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            static_cast<float>(sqlite3_column_double(stmt, 3)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)),
            mediaList
        );
        collection.setId(id);

    }

    sqlite3_finalize(stmt);

    sqlite3_close(db);
    return collection;
}


int DatabaseManager::addMediaItem(MediaMetadata& media) {
    std::string sql = "INSERT INTO MediaMetadata (title, description, releaseDate, duration, genre, rating, path, thumbnailPath, groupId) "
                          "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    sqlite3* db = loadDB(dbPath);

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    // Bind values to the statement
    sqlite3_bind_text(stmt, 1, media.getTitle().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, media.getDescription().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, media.getReleaseDate().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, media.getDuration());
    sqlite3_bind_text(stmt, 5, media.getGenre().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 6, media.getRating());
    sqlite3_bind_text(stmt, 7, media.getPath().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 8, media.getThumbnailPath().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 9, media.getGroupId());

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error inserting data: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    int lastId = sqlite3_last_insert_rowid(db);

    // Finalize the statement to prevent memory leaks
    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return lastId;
}


int DatabaseManager::addMediaCollection(MediaCollection& collection) {
    std::string sql = "INSERT INTO MediaCollection (title, description, category, rating, genre, thumbnailPath, mediaList) "
                          "VALUES (?, ?, ?, ?, ?, ?, ?);";

    std::stringstream ss;
    std::vector<int> vec = collection.getMediaList();
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != 0) ss << ",";
        ss << vec[i];
    }
    std::string vecAsString = ss.str();


    sqlite3_stmt* stmt;
    sqlite3* db = loadDB(dbPath);

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    // Bind values to the statement
    sqlite3_bind_text(stmt, 1, collection.getTitle().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, collection.getDescription().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, collection.getCategory().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, collection.getRating());
    sqlite3_bind_text(stmt, 5, collection.getGenre().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, collection.getThumbnailPath().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, vecAsString.c_str(), -1, SQLITE_TRANSIENT);


    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error inserting data: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    int lastId = sqlite3_last_insert_rowid(db);

    // Finalize the statement to prevent memory leaks
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return lastId;
}

void DatabaseManager::executeStatement(const std::string& sql) {
    sqlite3* db = loadDB(dbPath);
    char* errorMessage = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "SQL Error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    sqlite3_close(db);
}

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

bool DatabaseManager::getClientMetadata(const std::string& clientname, std::string &machineInfo, std::string &code) {
    std::string sqlQuery = "SELECT * FROM ClientMetadata WHERE clientName = ?";

    sqlite3_stmt* stmt;
    bool exists = false;

    sqlite3* db = loadDB(dbPath);

    if (sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, clientname.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = true;
            machineInfo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            code = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        }
    }
    else {
        std::cout << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_reset(stmt);

    // Finalize the statement to prevent memory leaks
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return exists;
}




void DatabaseManager::addTicket(const std::string& clientName, const std::string& machineInfo) {
    std::string sql = "INSERT INTO Tickets (clientName, machineInfo) "
                          "VALUES (?, ?);";

    sqlite3_stmt* stmt;
    sqlite3* db = loadDB(dbPath);

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    // Bind values to the statement
    sqlite3_bind_text(stmt, 1, clientName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, machineInfo.c_str(), -1, SQLITE_TRANSIENT);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error inserting data: " << sqlite3_errmsg(db) << std::endl;

    }


    // Finalize the statement to prevent memory leaks
    sqlite3_finalize(stmt);

    sqlite3_close(db);

}

bool DatabaseManager::addUser(const std::string& clientName, const std::string &userName) {
    sqlite3* db = loadDB(dbPath);

    std::string sqlQuery = "INSERT OR IGNORE INTO UserMetadata (userName, clientName, favList, "
                           "repList, watchLater, watched, watching) VALUES (?, ?, ?, ?, ?, ?, ?)";
    bool inserted = true;
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        // Bind values for UserID, RoleID, and AssignedDate

        sqlite3_bind_text(stmt, 1, userName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, clientName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, "", -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, "", -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, "", -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, "", -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, "", -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            inserted = false;
        }

        sqlite3_finalize(stmt);
    } else {
        inserted = false;
    }

    sqlite3_close(db);
    return inserted;
}

bool DatabaseManager::deleteUser(const std::string& clientName, const std::string &userName) {
    sqlite3* db = loadDB(dbPath);

    std::string sqlQuery = "DELETE FROM UserMetadata WHERE clientName = ? AND userName = ?";
    bool inserted = true;
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        // Bind values for UserID, RoleID, and AssignedDate

        sqlite3_bind_text(stmt, 2, userName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 1, clientName.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            inserted = false;
        }

        sqlite3_finalize(stmt);
    } else {
        inserted = false;
    }

    sqlite3_close(db);
    return inserted;
}





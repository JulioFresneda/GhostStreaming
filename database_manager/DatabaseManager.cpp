//
// Created by juliofgx on 12/26/23.
//

// DatabaseManager.cpp

#include "DatabaseManager.h"
#include <iostream>
#include <sstream>


DatabaseManager::DatabaseManager(const std::string& dbPath) : dbPath(dbPath), db(nullptr) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
}

DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
    }
}

bool DatabaseManager::initializeDatabase() {
    int rc = sqlite3_open(dbPath.c_str(), &db);

    if (rc) {
        std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

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

    executeStatement(createMediaTableSql);
    executeStatement(createCollectionTableSql);

    return true;

}

MediaMetadata DatabaseManager::getMediaItem(int id)
{
    std::string sql = "SELECT id, title, description, releaseDate, duration, genre, rating, path, thumbnailPath, groupId "
                          "FROM MediaMetadata WHERE id = ?;";

    sqlite3_stmt* stmt;
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
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);

    MediaCollection collection = MediaCollection();
    if (sqlite3_step(stmt) == SQLITE_ROW) {

        std::string medialist_str = "1,2";
        std::vector<int> mediaList = stringToVector(medialist_str);
        collection = MediaCollection(
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
            static_cast<float>(sqlite3_column_double(stmt, 5)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)),
            mediaList
        );
        collection.setId(id);

    }

    sqlite3_finalize(stmt);
    return collection;
}


int DatabaseManager::addMediaItem(MediaMetadata& media) {
    std::string sql = "INSERT INTO MediaMetadata (title, description, releaseDate, duration, genre, rating, path, thumbnailPath, groupId) "
                          "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;
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

    return lastId;
}

void DatabaseManager::executeStatement(const std::string& sql) {
    char* errorMessage = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "SQL Error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

// Implementations for addMediaItem, getMediaItem, updateMediaItem, deleteMediaItem,
// addMediaCollection, getMediaCollection, etc., would follow a similar pattern,
// preparing and executing SQL statements with sqlite3 functions.


//
// Created by juliofgx on 12/26/23.
//

// DatabaseManager.cpp

#include "DatabaseManager.h"
#include <iostream>



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
            description TEXT
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
        return 1;
    }

    // Finalize the statement to prevent memory leaks
    sqlite3_finalize(stmt);
    return 0;
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


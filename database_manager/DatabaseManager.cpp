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


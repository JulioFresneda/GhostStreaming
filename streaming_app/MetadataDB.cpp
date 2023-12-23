//
// Created by juliofgx on 12/23/23.
//

#include "MetadataDB.h"
#include <iostream>

MetadataDB::MetadataDB(const std::string &dbPath) {
    if (!initDatabase(dbPath)) {
        std::cerr << "Failed to initialize database." << std::endl;
        // Handle initialization failure...
    }
}

MetadataDB::~MetadataDB() {
    sqlite3_close(db);
}

bool MetadataDB::initDatabase(const std::string &dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &db);

    if (rc) {
        std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Create the metadata table
    const char* createTableSql =
        "CREATE TABLE IF NOT EXISTS videos ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "video_path TEXT NOT NULL, "
        "title TEXT, "
        "description TEXT);";

    char* errorMessage = nullptr;
    rc = sqlite3_exec(db, createTableSql, nullptr, nullptr, &errorMessage);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL Error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}


void MetadataDB::addNewVideo(const std::string &videoPath, const std::string &title, const std::string &description) {
    std::cout << "Adding video " << title << std::endl;

    const char* insertSql = "INSERT INTO videos (video_path, title, description) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, insertSql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement" << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, videoPath.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, description.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement" << std::endl;
    }

    sqlite3_finalize(stmt);
}


// Implement other database methods...

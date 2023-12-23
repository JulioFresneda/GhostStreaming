// MetadataDatabase.cpp

#include "VideoMetadata.h"
#include <iostream>

MetadataDatabase::MetadataDatabase(const std::string &dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
}

MetadataDatabase::~MetadataDatabase() {
    sqlite3_close(db);
}

bool MetadataDatabase::addVideo(const VideoMetadata &metadata) {
    const char *sql = "INSERT INTO videos (video_path, title, description) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, metadata.videoPath.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, metadata.title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, metadata.description.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

// Implement the method in MetadataDatabase.cpp
void MetadataDatabase::listAllVideos() {
    const char* sql = "SELECT id, video_path, title, description FROM videos;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "Listing all videos:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* videoPath = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        std::cout << "ID: " << id << std::endl;
        std::cout << "Path: " << videoPath << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Description: " << description << std::endl << std::endl;
    }

    sqlite3_finalize(stmt);
}


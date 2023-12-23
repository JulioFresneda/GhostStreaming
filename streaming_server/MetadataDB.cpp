//
// Created by juliofgx on 12/23/23.
//

#include "MetadataDB.h"
#include <iostream>
#include <cstdlib>

MetadataDB::MetadataDB(const std::string &dbPath) {
    if (!initDatabase(dbPath)) {
        std::cerr << "Failed to initialize database." << std::endl;
        // Handle initialization failure...
    }
}

MetadataDB::~MetadataDB() {
    sqlite3_close(db);
}

sqlite3 *MetadataDB::getDB() const {
    return db;
}

int MetadataDB::loadMediaSegments(const std::string &mediaId) {
    MovieMetadata metadata = fetchMetadata(std::stoi(mediaId));

    std::string command = "ffmpeg -i " + metadata.video_path + " -map 0:v -c:v libx264 -b:v:0 500k -b:v:1 1000k -s:v:1 1280x720 -keyint_min 60 -g 60 -use_timeline 1 -use_template 1 -adaptation_sets \"id=0,streams=v\" -f dash output.mpd";
    int result = system(command.c_str());

    if (result != 0) {
        // Handle error
    }
    return result;

}

std::string MetadataDB::getSegmentPath(const std::string &mediaId, int segmentNumber) {
    return "";
}



MovieMetadata MetadataDB::fetchMetadata(int movieId) {
    MovieMetadata metadata;
    sqlite3_stmt *stmt;
    std::string query = "SELECT id, video_path, title, description FROM videos WHERE id = ?";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return metadata;
    }

    sqlite3_bind_int(stmt, 1, movieId);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        metadata.id = sqlite3_column_int(stmt, 0);
        metadata.video_path = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        metadata.title = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        metadata.description = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
    } else {
        std::cerr << "No data found for ID: " << movieId << std::endl;
    }

    sqlite3_finalize(stmt);
    return metadata;
}

bool MetadataDB::initDatabase(const std::string &dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &db);

    if (rc) {
        std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Create the metadata table
    const char *createTableSql =
            "CREATE TABLE IF NOT EXISTS videos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "video_path TEXT NOT NULL, "
            "title TEXT, "
            "description TEXT);";

    char *errorMessage = nullptr;
    rc = sqlite3_exec(db, createTableSql, nullptr, nullptr, &errorMessage);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL Error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}


// Implement other database methods...

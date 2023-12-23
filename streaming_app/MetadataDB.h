//
// Created by juliofgx on 12/23/23.
//

#ifndef METADATADB_H
#define METADATADB_H

#include <sqlite3.h>
#include <string>

class MetadataDB {
    public:
        MetadataDB(const std::string &dbPath);
        ~MetadataDB();

        void addNewVideo(const std::string &videoPath, const std::string &title, const std::string &description);
        // Other database methods...

    private:
        sqlite3* db;
        bool initDatabase(const std::string &dbPath);
        // Other private methods and members...

};



#endif //METADATADB_H

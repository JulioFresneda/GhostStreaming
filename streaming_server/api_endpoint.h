//
// Created by juliofgx on 12/23/23.
//

#ifndef API_ENDPOINT_H
#define API_ENDPOINT_H

#include "crow.h"
#include "MetadataDB.h"

class APIEndpoint {
public:
    MetadataDB db;

    APIEndpoint(const MetadataDB &database);


    // Other database methods...

private:
    static std::string readFileContents(const std::string& filepath);
    static crow::json::wvalue fetchMetadata(MetadataDB &metadata_db, const int &mediaId);

    static crow::json::wvalue to_json(const MovieMetadata &metadata);
};


#endif //API_ENDPOINT_H

    //
    // Created by juliofgx on 12/23/23.
    //

    #ifndef API_ENDPOINT_H
    #define API_ENDPOINT_H

    #include "crow.h"
    #include "DatabaseManager.h"

    class APIEndpoint {
    public:
        DatabaseManager db;

        APIEndpoint(const DatabaseManager &database);
        ~APIEndpoint();


        // Other database methods...

    private:
        static std::string readFileContents(const std::string& filepath);
        static crow::json::wvalue fetchMetadata(DatabaseManager &metadata_db, const int &mediaId);
        static crow::json::wvalue fetchCollection(DatabaseManager &metadata_db, const int &collectionId);

        static crow::json::wvalue to_json(MediaMetadata &metadata);
        static crow::json::wvalue to_json(MediaCollection &metadata);

    };


    #endif //API_ENDPOINT_H

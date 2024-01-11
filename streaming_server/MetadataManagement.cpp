//
// Created by juliofgx on 1/11/24.
//

#include "MetadataManagement.h"

#include <DatabaseManager.h>




const std::unordered_map<std::string, std::vector<int>> MetadataManagement::getGenres(DatabaseManager& db) {
    std::vector<int> allMediaMetadata = db.getAllMediaItemIDs();
    std::unordered_map<std::string, std::vector<int>> genresMap;

    for(auto & i : allMediaMetadata) {
        MediaMetadata mm = db.getMediaItem(i);
        std::vector<std::string> genres = mm.getGenresSplitted();
        for(const auto & genre : genres) {
            genresMap[genre].push_back(i);
        }
    }

    return genresMap;
}

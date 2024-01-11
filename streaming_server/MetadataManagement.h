//
// Created by juliofgx on 1/11/24.
//

#ifndef METADATAMANAGEMENT_H
#define METADATAMANAGEMENT_H

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "DatabaseManager.h"


class MetadataManagement {
public:
    static const std::unordered_map<std::string, std::vector<int>> getGenres(DatabaseManager& db);
};



#endif //METADATAMANAGEMENT_H

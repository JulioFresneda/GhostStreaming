//
// Created by juliofgx on 1/4/24.
//

#include "UserManagement.h"


bool UserManagement::addUser(DatabaseManager& db, const std::string& clientName, const std::string &userName) {
    bool added = db.addUser(clientName, userName);
    return added;
}

std::vector<std::string> UserManagement::getUsers(DatabaseManager& db, const std::string& clientName) {
    return db.getUsers(clientName);
}
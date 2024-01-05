//
// Created by juliofgx on 1/4/24.
//

#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H


#include <string>
#include <sqlite3.h>
#include "DatabaseManager.h"




class UserManagement {
public:
    static bool addUser(DatabaseManager& db, const std::string& clientName, const std::string &userName);
};



#endif //USERMANAGEMENT_H

//
// Created by juliofgx on 1/4/24.
//

#ifndef CLIENTMANAGEMENT_H
#define CLIENTMANAGEMENT_H

#include <string>
#include <ostream>
#include <sqlite3.h>
#include "DatabaseManager.h"

enum class ClientStatus {
    NEW,
    NEW_MACHINE,
    USER,
    CODE_ERROR
};

class ClientManagement {
public:
    static ClientStatus checkClientStatus(DatabaseManager db, const std::string& clientname, const std::string &machineInfo, const std::string &code);
    static void generateTicket(const std::string& clientName, const std::string& machineInfo);

};



#endif //CLIENTMANAGEMENT_H

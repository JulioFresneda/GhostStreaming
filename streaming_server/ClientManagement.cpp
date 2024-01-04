//
// Created by juliofgx on 1/4/24.
//

#include "ClientManagement.h"



ClientStatus ClientManagement::checkClientStatus(DatabaseManager db, const std::string& clientname, const std::string &machineInfo) {
    std::string dbMachineInfo = "";
    std::vector<std::string> userlist;

    bool clientMetadata = db.getClientMetadata(clientname, dbMachineInfo, userlist);

    if (dbMachineInfo == machineInfo){return ClientStatus::USER;}
    db.addTicket(clientname, machineInfo);
    if (!clientMetadata){return ClientStatus::NEW;}
    {return ClientStatus::NEW_MACHINE;}
}



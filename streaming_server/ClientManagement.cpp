//
// Created by juliofgx on 1/4/24.
//

#include "ClientManagement.h"



ClientStatus ClientManagement::checkClientStatus(DatabaseManager db, const std::string& clientname, const std::string &machineInfo, const std::string &code) {
    std::string dbMachineInfo = "";
    std::string dbCode = "";

    bool clientMetadata = db.getClientMetadata(clientname, dbMachineInfo, dbCode);

    if (dbMachineInfo == machineInfo and code == dbCode){return ClientStatus::USER;}
    if (dbMachineInfo == machineInfo){return ClientStatus::CODE_ERROR;}
    db.addTicket(clientname, machineInfo);
    if (!clientMetadata){return ClientStatus::NEW;}
    {return ClientStatus::NEW_MACHINE;}
}



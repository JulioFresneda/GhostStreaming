

#include "DatabaseManager.h"
#include "api_endpoint.h"
#include <json.hpp>

using json = nlohmann::json;

json loadJSONPath(const std::string& jsonPath)
{
    std::ifstream collectionFile(jsonPath);
    json Json;
    collectionFile >> Json;
    return Json;

}


int main() {

    std::filesystem::path cwd = std::filesystem::current_path();
    std::filesystem::path configPath = std::filesystem::absolute(cwd.parent_path() / "config.json");

    json configJson = loadJSONPath(configPath);
    std::filesystem::path dbPath = std::filesystem::absolute(configJson.value("database_path",""));

    DatabaseManager db = DatabaseManager(dbPath);

    APIEndpoint api_endpoint = APIEndpoint(db);


    return 0;
}

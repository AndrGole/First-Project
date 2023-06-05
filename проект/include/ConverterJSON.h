#pragma once
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

class ConverterJSON {
private:
    nlohmann::json config;
    nlohmann::json requestsJS;
    std::string project_path;
public:
    ConverterJSON(std::string project_path_);
    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
};

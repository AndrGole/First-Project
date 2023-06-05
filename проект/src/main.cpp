#include "ConverterJSON.h"
#include "SearchEngine.h"
#include "InvertedIndex.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::string project_path_ = argv[0];
    project_path_ = project_path_.substr(0, project_path_.size()-17);
    ConverterJSON converterJson(project_path_);
    InvertedIndex invertedIndex;
    std::vector<std::string> text = converterJson.GetTextDocuments();
    SearchServer searchServer(invertedIndex, text);

    std::vector<std::string> requests = converterJson.GetRequests();
    std::vector<std::vector<RelativeIndex>> search_res = searchServer.search(requests);
    std::vector<std::vector<std::pair<int, float>>> res;
    for(int i = 0; i < search_res.size(); i++){
        std::vector<std::pair<int, float>> mini_res;
        for(int g = 0; g < search_res[i].size(); g++){
            mini_res.push_back({search_res[i][g].doc_id, search_res[i][g].rank});
        }
        res.push_back(mini_res);
        int VVVVVVVVVVV = 0;
    }
    std::cout << "relevance calculated" << std::endl;
    converterJson.putAnswers(res);
    std::cout << "the result is recorded" << std::endl;
}

#include <fstream>
#include "ConverterJSON.h"
using namespace std;

std::string n_to_tn(int n){
    string result = "";
    result += (n/100) + '0'; n -= (n/100)*100;
    result += (n/10) + '0'; n -= (n/10)*10;
    result += n + '0';
    return result;
}

ConverterJSON::ConverterJSON(std::string project_path_){
    project_path = project_path_;
    ifstream configFile(project_path + "config.json");
    configFile >> config;
    configFile.close();
    ifstream requestsFile(project_path + "requests.json");
    requestsFile >> requestsJS;
    requestsFile.close();
}
/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
std::vector<std::string> ConverterJSON::GetTextDocuments(){
    std::vector<string> files;
    for(int i = 0; i < config["files"].size(); i++){
        string path_name = to_string(config["files"][i]).substr(1, to_string(config["files"][i]).size()-2);
        path_name = project_path + "resources\\" + path_name;
        ifstream textFile(path_name);
        string FullText;
        while(!textFile.eof()){
            std::string text;
            textFile >> text;
            FullText += text + " ";
        }
        textFile.close();
        files.push_back(FullText);
    }
    return files;
}
/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
int ConverterJSON::GetResponsesLimit(){
    ifstream configFile("config.json");
    configFile >> config;
    configFile.close();
    return config["config"]["max_responses"];
};
/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
std::vector<std::string> ConverterJSON::GetRequests(){
    vector<string> requests;
    for(int i = 0; i < requestsJS["requests"].size(); i++){
        requests.push_back(requestsJS["requests"][i]);
    }
    return requests;
}
/**
* Положить в файл answers.json результаты поисковых запросов
*/
void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {
    ofstream answerFile("answers.json");
    answerFile << "{\n\t\"answer\": {\n";
    for(int i = 0; i < GetRequests().size(); i++){
        answerFile << "\t\t\"request" << n_to_tn(i+1) << "\": {\n";
        if(answers[i].empty()){
            if(i+1 == GetRequests().size()){
                answerFile << "\t\t\t\"result\": \"false\"\n\t\t}\n";
            }else{
                answerFile << "\t\t\t\"result\": \"false\"\n\t\t},\n";
            }
        }else if(answers[i][0].first != -1){
            answerFile << "\t\t\t\"result\": \"true\",\n";
            if(answers[i].size() > 1){
                answerFile << "\t\t\t\"relevance\": {\n";
                for(int g = 0; g < answers[i].size(); g++){
                    if(g+1 == GetResponsesLimit() || g+1 == answers[i].size()){
                        answerFile << "\t\t\t\t\"docid\": " << answers[i][g].first << ", \"rank\" : " << int(answers[i][g].second) << "." << n_to_tn((answers[i][g].second - int(answers[i][g].second)) * 1000) << "\n";
                        break;
                    }else{
                        answerFile << "\t\t\t\t\"docid\": " << answers[i][g].first << ", \"rank\" : " << int(answers[i][g].second) << "." << n_to_tn((answers[i][g].second - int(answers[i][g].second)) * 1000) << ",\n";
                    }
                }
                answerFile << "\t\t\t}\n";
            }else{
                answerFile << "\t\t\t\"docid\": " << answers[i][0].first << ", \"rank\" : " << int(answers[i][0].second) << "." << n_to_tn((answers[i][0].second - int(answers[i][0].second)) * 1000) << "\n";
            }
            if(i+1 == GetRequests().size()){
                answerFile << "\t\t}\n";
            }else{
                answerFile << "\t\t},\n";
            }
        }
    }
    answerFile << "\t}\n}";
    answerFile.close();
}
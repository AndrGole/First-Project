#include "SearchEngine.h"
#include <sstream>
#include <algorithm>
#include <iostream>

std::vector<std::vector<Entry>> sort(std::map<std::string, std::vector<Entry>> freq_dictionary){
    std::vector<std::vector<Entry>> value;
    for(auto it = freq_dictionary.begin(); it != freq_dictionary.end(); it++){
        value.push_back(it->second);
    }
    bool b = true;
    while (b) {
        b = false;
        for (int it = 0; it < value.size(); it++) {
            if (value[it].size() > value[it+1].size() && it + 1 !=  value.size()) {
                auto c = value[it];
                value[it] = value[it+1];
                value[it+1] = c;
                b = true;
            }
        }
    }
    return value;
}

std::vector<RelativeIndex> sort(std::vector<RelativeIndex> this_res){
    std::vector<RelativeIndex> res;
    for(int i = 0; i < this_res.size(); i++){
        res.push_back(this_res[i]);
    }
    bool b = true;
    while (b){
        b = false;
        for (int it = 0; it < res.size(); it++) {
            if (res[it].rank < res[(it + 1)].rank && it + 1 != res.size()) {
                auto c = res[it];
                res[it] = res[it+1];
                res[it+1] = c;
                b = true;
            }
        }
    }
    return res;
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    _index.UpdateDocumentBase(_text);
    std::cout << "documents uploaded" << std::endl;

    std::vector<std::vector<RelativeIndex>> res;
    for(int id = 0; id < queries_input.size(); id++){
        std::stringstream readable_request{queries_input[id]};
        std::string request_word;
        std::vector<std::string> word_list;
        word_list.clear();
        while(readable_request >> request_word){
            if(std::find(word_list.begin(), word_list.end(), request_word) == word_list.end()){
                word_list.push_back(request_word);
            }
        }
        std::map<std::string, std::vector<Entry>> this_freq_dictionary;
        for(int inv_id = 0; inv_id < word_list.size(); inv_id++){
            this_freq_dictionary.insert({word_list[inv_id], _index.GetWordCount(word_list[inv_id])});
        }
        auto filter = sort(this_freq_dictionary);
        std::vector<Entry> ids;
        for(int i = 0; i < filter[0].size(); i++){
            ids.push_back(filter[0][i]);
        }
        for(int it = 1; it < filter.size(); it++){
            auto this_it_it_id = filter[it].begin();
            for(int it_id = 0; it_id < filter[it].size(); it_id++){
                bool availability = false;
                for(int ids_id = 0; ids_id < ids.size(); ids_id++){
                    if(filter[it][it_id].doc_id == ids[ids_id].doc_id){
                        availability = true;
                        filter[it][it_id].count += ids[ids_id].count;
                    }
                }
                if(!availability){
                    filter[it].erase(this_it_it_id);
                    it_id--;
                    this_it_it_id--;
                }
                this_it_it_id++;
            }
            ids.clear();
            for(int i = 0; i < filter[it].size(); i++){
                ids.push_back(filter[it][i]);
            }
            if(ids.size() <= 1){
                break;
            }
        }
        std::vector<RelativeIndex> this_res;
        if(ids.size() == 0){
            this_res.clear();
            res.push_back(this_res);
        }else if(ids.size() == 1){
            this_res.push_back({ids[0].doc_id, 1});
            res.push_back(this_res);
        }else{
            int max_count = ids[0].count;
            for(int i = 1; i < ids.size(); i++){
                if(ids[i].count > max_count){
                    max_count = ids[i].count;
                }
            }
            for(int i = 0; i < ids.size(); i++){
                float rank = float(ids[i].count) / max_count;
                this_res.push_back({ids[i].doc_id, rank});
            }
            this_res = sort(this_res);
            res.push_back(this_res);
            int VVVVVVVVV = 0;
        }
    }
    return res;
}
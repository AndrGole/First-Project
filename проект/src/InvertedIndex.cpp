#include "InvertedIndex.h"
#include <thread>
#include <sstream>

void WordCount(std::map<std::string, std::vector<Entry>> &small_freq_dictionary, int thread_id, int number_of_threads, std::vector<std::string> docs) {
    int id = thread_id;
    while(id < docs.size()){
        std::stringstream readable_document{docs[id]};
        std::string word;
        while(readable_document >> word){
            bool founded = false;
            if(small_freq_dictionary.find(word) != small_freq_dictionary.end()){
                for(int index = 0; index < small_freq_dictionary.find(word)->second.size(); index++){
                    if(small_freq_dictionary.find(word)->second[index].doc_id == id){
                        founded = true;
                        small_freq_dictionary.find(word)->second[index].count++;
                    }
                }
                if(!founded){
                    small_freq_dictionary.find(word)->second.push_back({(size_t)id, 1});
                }
            }else{
                small_freq_dictionary.insert(std::pair<std::string, std::vector<Entry>>(word, std::vector<Entry>{{(size_t)id, 1}}));
            }
        }
        id += number_of_threads;
    }
}

std::map<std::string, std::vector<Entry>> AddingTwoFreqDictionaries(std::map<std::string, std::vector<Entry>> main_freq_dictionary, std::map<std::string, std::vector<Entry>> second_freq_dictionary){
    for(auto it = main_freq_dictionary.begin(); it != main_freq_dictionary.end(); it++){
        std::string word = it->first;
        if(second_freq_dictionary.find(word) != second_freq_dictionary.end()){
            for(int i = 0; i < second_freq_dictionary.find(word)->second.size(); i++){
                it->second.push_back(second_freq_dictionary.find(word)->second[i]);
            }
            second_freq_dictionary.erase(second_freq_dictionary.find(word));
        }
    }
    main_freq_dictionary.insert(second_freq_dictionary.begin(), second_freq_dictionary.end());
    return main_freq_dictionary;
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs){
    docs.clear();
    for(int i = 0; i < input_docs.size(); i++){
        docs.push_back(input_docs[i]);
    }
    std::map<std::string, std::vector<Entry>> small_freq_dictionary_id0;
    std::map<std::string, std::vector<Entry>> small_freq_dictionary_id1;
    std::map<std::string, std::vector<Entry>> small_freq_dictionary_id2;
    std::map<std::string, std::vector<Entry>> small_freq_dictionary_id3;
    std::map<std::string, std::vector<Entry>> small_freq_dictionary_id4;
    small_freq_dictionary_id0.clear(); small_freq_dictionary_id1.clear(); small_freq_dictionary_id2.clear(); small_freq_dictionary_id3.clear(); small_freq_dictionary_id4.clear();
    std::thread thread_word_count0(WordCount, std::ref(small_freq_dictionary_id0), 0, 5, docs);
    std::thread thread_word_count1(WordCount, std::ref(small_freq_dictionary_id1), 1, 5, docs);
    std::thread thread_word_count2(WordCount, std::ref(small_freq_dictionary_id2), 2, 5, docs);
    std::thread thread_word_count3(WordCount, std::ref(small_freq_dictionary_id3), 3, 5, docs);
    std::thread thread_word_count4(WordCount, std::ref(small_freq_dictionary_id4), 4, 5, docs);
    thread_word_count0.join();
    thread_word_count1.join();
    thread_word_count2.join();
    thread_word_count3.join();
    thread_word_count4.join();
    freq_dictionary.clear();
    freq_dictionary = AddingTwoFreqDictionaries(AddingTwoFreqDictionaries(AddingTwoFreqDictionaries(AddingTwoFreqDictionaries(small_freq_dictionary_id0, small_freq_dictionary_id1),
                                                                                                    small_freq_dictionary_id2), small_freq_dictionary_id3), small_freq_dictionary_id4);
}
std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    std::vector<Entry> res;
    res.clear();
    if(freq_dictionary.find(word) != freq_dictionary.end()){
        for(int i = 0; i < freq_dictionary.find(word)->second.size(); i++){
            res.push_back(freq_dictionary.find(word)->second[i]);
        }
    }
    return res;
}
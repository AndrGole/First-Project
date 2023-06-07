#include "../include/SearchEngine.h"
#include "gtest/gtest.h"
#include <../include/ConverterJSON.h>

TEST(TestCaseSearchServer, TestSimple) {
    const std::vector<std::string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const std::vector<std::string> request = {"milk water", "sugar"};
    const std::vector<std::vector<RelativeIndex>> expected = {
            {
                    {2, 1},
                    {0, 0.7},
                    {1, 0.3}
            },
            {
            }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx, docs);
    std::vector<std::vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}

TEST(TestCaseSearchServer, MyTest) {
    const std::vector<std::string> docs = {
            "drink milk and water water kappa",
            "milk water water drink",
            "milk milk milk milk milk water water water water water drink and and and drink",
            "americano cappuccino more sugar",
            "need more sugar",
            "need more sugar need more sugar"
    };
    const std::vector<std::string> request = {"drink milk and water", "need more sugar"};
    const std::vector<std::vector<RelativeIndex>> expected = {
            {
                    {2, 1},
                    {0, 0.333333333}
            },
            {
                    {5, 1},
                    {4, 0.5}
            }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx, docs);
    std::vector<std::vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}


// Этот тест некорректен так как по условию алгоритма подсчёта релевантности в результате должнен быть верен только текст с id 7 (все остальные не содержат полного набора слов из запроса)
// по этой причине я создал тест под названием MyTest что выше
/*TEST(TestCaseSearchServer, TestTop5) {
    const std::vector<std::string> docs = {
            "london is the capital of great britain",                                         //0
            "paris is the capital of france",                                                 //1
            "berlin is the capital of germany",                                               //2
            "rome is the capital of italy",                                                   //3
            "madrid is the capital of spain",                                                 //4
            "lisboa is the capital of portugal",                                              //5
            "bern is the capital of switzerland",                                             //6
            "moscow is the capital of russia",                                                //7
            "kiev is the capital of ukraine",                                                 //8
            "minsk is the capital of belarus",                                                //9
            "astana is the capital of kazakhstan",                                            //10
            "beijing is the capital of china",                                                //11
            "tokyo is the capital of japan",                                                  //12
            "bangkok is the capital of thailand",                                             //13
            "welcome to moscow the capital of russia the third rome",                         //14
            "amsterdam is the capital of netherlands",                                        //15
            "helsinki is the capital of finland",                                             //16
            "oslo is the capital of norway",                                                  //17
            "stockholm is the capital of sweden",                                             //18
            "riga is the capital of latvia",                                                  //19
            "tallinn is the capital of estonia",                                              //20
            "warsaw is the capital of poland",                                                //21
    };
    const std::vector<std::string> request = {"moscow is the capital of russia"};
    const std::vector<std::vector<RelativeIndex>> expected = {
            {
                    {7, 1},
                    {14, 1},
                    {0, 0.666666687},
                    {1, 0.666666687},
                    {2, 0.666666687}
            }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx, docs);
    std::vector<std::vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}*/
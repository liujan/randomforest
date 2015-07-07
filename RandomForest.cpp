#include "RandomForest.h"
#include "fstream"
#include "Node.h"
#include "Tree.h"
#include "memory.h"
using namespace std;
extern const int numOfFeatures;
extern const int numOfTypes;
extern const int numOfTest;

RandomForest::RandomForest(){
    memset(result, 0, sizeof(result));
}

//训练一棵决策树，然后预测结果
void RandomForest::build(){
    if (test_samples.empty()){
        cout << "[Error] test sample is empty" << endl;
        return;
    }
    Tree *tree = new Tree();
    if (tree->readSample(this->all_samples)){
        tree->buildTree();
        for (int j = 0; j < test_samples.size(); j++){
            int id = test_samples[j].first;
            int type = tree->predict(test_samples[j].second);
            result[id][type]++;
        }
    }
    delete tree;
}

//训练num棵决策树，并预测结果
bool RandomForest::buildTree(int num){
    if (all_samples.empty()){
        cout << "[Error] all sample is empty" << endl;
        return false;
    }
    
    for (int i = 0; i < num; i++){
        cout << i+1 << " ";
        this->build();
    }
    
    return true;
}


//将预测结果归总，并写入到文件中
void RandomForest::predict(){
    if (this->test_samples.empty()){
        cout << "[Error] test sample is empty" << endl;
        return;
    }
    ofstream out("result.csv");
    if (!out.is_open()){
        cout << "[Error] failed to open file result.csv" << endl;
        return;
    }
    cout << "predicting ..." << endl;
    out << "Id,label" << "\n";
    
    for (int i = 0; i < numOfTest; i++){
        int max_value = -1000, index = 0;
        for (int j = 0; j < numOfTypes+1; j++){
            if (result[i][j] > max_value){
                max_value = result[i][j];
                index = j;
            }
        }
        out << i << "," << index << "\n";
    }
    
    out.close();
    cout << "predicting completed" << endl;
}




bool RandomForest::readTrainSample(string file){
    ifstream train("train.csv");
    if (!train.is_open()){
        cout << "[Error] : Failed to open file " << file << endl;
        return false;
    }
    cout << "reading sample ..." << endl;
    
    string s;
    getline(train, s); //过滤掉第一行标签
    
    double value;
    char dot;
    int id;
    int label;
    while (true) {
        train >> id;
        if (train.eof())
            break;
        
        vector<double> features;
        for (int i = 0; i < numOfFeatures; i++){
            train >> dot;
            train >> value;
            features.push_back(value);
        }
        train >> dot;
        train >> label;
        all_samples.push_back(make_pair(label, features));
        
        if (train.peek() == '\n')
            train.get();
    }
    
    train.close();
    cout << "reading sample successful" << endl;
    return true;
}

bool RandomForest::readTestSample(string file){
    ifstream test("test.csv");
    if (!test.is_open()){
        cout << "[Error] : Failed to open file " << file << endl;
        return false;
    }
    cout << "reading test sample ..." << endl;
    test_samples.clear();
    string s;
    getline(test, s); //过滤掉第一行标签
    
    double value;
    char dot;
    int id;
    
    while (true) {
        test >> id;
        if (test.eof())
            break;
        
        vector<double> features;
        for (int i = 0; i < numOfFeatures; i++){
            test >> dot;
            test >> value;
            features.push_back(value);
        }
        
        test_samples.push_back(make_pair(id, features));
        
        if (test.peek() == '\n')
            test.get();
    }
    
    test.close();
    cout << "reading test sample successful" << endl;
    return true;
}

RandomForest::~RandomForest(){
    for (int i = 0; i < forest.size(); i++){
        if (forest[i] != NULL)
            delete forest[i];
    }
}

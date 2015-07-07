//
//  RandomForest.h
//  RandomForest
//
//  Created by 刘建安 on 6/23/15.
//  Copyright (c) 2015 刘建安. All rights reserved.
//

#ifndef __RandomForest__RandomForest__
#define __RandomForest__RandomForest__


#include "iostream"
#include "vector"
#include "string"
#include "Node.h"
#include "map"
using namespace std;
class Tree;
extern const int numOfTypes;
extern const int numOfTest;

class RandomForest{
private:
    vector<pair<int, vector<double> > > all_samples; //<label ,features> ,训练样本
    vector<pair<int, vector<double> > > test_samples; //<id, features>，预测样本
    vector<Tree*> forest;
    int result[numOfTest][numOfTypes+1];
public:
    bool readTrainSample(string file);
    bool buildTree(int num);
    ~RandomForest();
    bool readTestSample(string test);
    void predict();
    RandomForest();
    void build();
    
};

#endif /* defined(__RandomForest__RandomForest__) */

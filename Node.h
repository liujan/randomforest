//
//  Node.h
//  RandomForest
//
//  Created by 刘建安 on 6/11/15.
//  Copyright (c) 2015 刘建安. All rights reserved.
//

#ifndef __RandomForest__Node__
#define __RandomForest__Node__

#include <stdio.h>
#include "memory.h"
#include "vector"
using namespace std;

const int numOfTypes = 26; //类别数
const int numOfFeatures = 617;
const int numOfTest=1559;
struct Node{
    int attribute; //当前节点选取哪个属性来进行分裂
    double value; //当前节点选取属性的哪个值来进行分裂
    Node *left; //左子节点
    Node *right;  //右子节点
    int sum; //当前节点的样本总数
    int num[numOfTypes]; //当前节点每类的样本数
    int depth;
    vector<pair<int, vector<double> > > samples; //<label, features>
    Node();
    
    //拷贝构造函数
    Node(const Node &other);
    
};

#endif /* defined(__RandomForest__Node__) */
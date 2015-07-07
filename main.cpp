//
//  main.cpp
//  RandomForest
//
//  Created by 刘建安 on 6/11/15.
//  Copyright (c) 2015 刘建安. All rights reserved.
//

#include <iostream>
#include "fstream"
#include "math.h"
#include "stdio.h"
#include "string"
#include "RandomForest.h"
#include "stdlib.h"
using namespace std;

void fun(){
    ifstream in("train.csv");
    ofstream out("train1.csv");
    
    string s;
    getline(in, s);
    out << s << endl;
    while (1){
        if (in.eof())
            break;
        getline(in, s);
        double p = rand() * 1.0 / RAND_MAX;
        if (p <= 0.1)
            out << s << endl;
        if (in.peek() == '\n')
            in.get();
    }
    in.close();
    out.close();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    RandomForest forest;
    forest.readTrainSample("train.csv");
    forest.readTestSample("test.csv");
    forest.buildTree(7000);
    forest.predict();
    return 0;
}

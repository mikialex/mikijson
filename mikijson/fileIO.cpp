//
//  fileIO.cpp
//  mikijson
//
//  Created by MikiAlex on 16/12/6.
//  Copyright © 2016年 MikiAlex. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "fileIO.hpp"

using namespace std;

inline string readFileToString(const string filename){
    string all;
    string temp;
    ifstream in(filename);
    while(in>>temp){
//         cout << "Read from file: " << temp << endl;
        all=all+temp;
    }
    return all;
}


inline vector<string> readFiletoStringVectorByLine(const string filename){
    vector<string> all;
    string temp;
    ifstream in(filename);
    while(getline(in,temp)){
        all.push_back(temp);
    }
    return all;
}






//
//  main.cpp
//  mikijson
//
//  Created by MikiAlex on 16/12/5.
//  Copyright © 2016年 MikiAlex. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include "fileIO.hpp"
#include "parser.hpp"


using namespace std;


//JSON-text = ws value ws
//ws = *(%x20 / %x09 / %x0A / %x0D)
//value = null / false / true
//null  = "null"
//false = "false"
//true  = "true"



string test;
vector<string> raw;

int main(int argc, const char * argv[]) {
    
    string a="   0.23   ";
    cout<<"原始字符:"<<a<<endl;
    
    
    jsonNode root;

    
    cout<<"parse结果："<<jsonParse(root, a)<<endl;
    cout<<"节点类型："<<root.type<<endl;
    cout<<"节点数值："<<root.n<<endl;
    
    return 0;
}

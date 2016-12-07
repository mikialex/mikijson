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
//    string filename="/Users/mikialex/Desktop/testjson1.json";
//    vector<string> filecontentByLine=readFiletoStringVectorByLine(filename);
//    string filecontent=readFiletoString(filename);
//    for(auto b=filecontentByLine.cbegin();b!=filecontentByLine.cend();++b){
//        cout<<*b<<"\n";
//    }
    
    string a="   true   ";
    cout<<"原始字符"<<a<<endl;
    
    
    jsonNode root;

    
    cout<<jsonParse(root, a);
    
//    jsonContext testcontext=new jsonContext(a);
//    cout<<jsonParseWhitespace(testcontext);
//    cin>>test;
//    // insert code here...
//    cout << filecontent;
    return 0;
}

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

#include "fileIO.cpp"


using namespace std;

//JSON-text = ws value ws
//ws = *(%x20 / %x09 / %x0A / %x0D)
//value = null / false / true
//null  = "null"
//false = "false"
//true  = "true"


//json节点数据类型
enum jsonType{
    JSON_NULL,
    JSON_FALSE,
    JSON_TRUE,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
};

enum {
    JSON_PARSE_OK = 0,
    JSON_PARSE_EXPECT_VALUE,
    JSON_PARSE_INVALID_VALUE,
    JSON_PARSE_ROOT_NOT_SINGULAR
};

//json节点
class jsonNode{
public:
    jsonType type;
};

class jsonContext{
public:
    string json;
};


static void jsonParseWhitespace(jsonContext c) {
    string raw = c.json;
    for(auto b=raw.cbegin();b!=raw.cend();++b){
        cout<<*b<<"\n";
    };
    auto p=raw.cbegin();
    while(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r'){
        p++;
    }
    string back;
    for(auto d=p;d!=raw.cend();++d){
        back.push_back(*d);
    }
    c.json = back;
}

static int jsonParseNull(jsonContext c,jsonNode v);


static int jsonParseNode(jsonContext c, jsonNode v) {
    switch (*c.json.cbegin()) {
        case 'n':  return jsonParseNull(c, v);
        case '\0': return JSON_PARSE_EXPECT_VALUE;
        default:   return JSON_PARSE_INVALID_VALUE;
    }
}

//从json字符串解析json树
int jsonParse(jsonNode rootNode,  const string jsonRawString){
    jsonContext c;
//    assert(v != NULL);
    c.json = jsonRawString;
    rootNode.type = JSON_NULL;//如果失败正好是json_null
    jsonParseWhitespace(c);
    return jsonParseNode(c, rootNode);
}

//获取json节点数据类型
jsonType getJsonType(const jsonNode node);


string test;
vector<string> raw;

int main(int argc, const char * argv[]) {
    string filename="/Users/mikialex/Desktop/testjson1.json";
//    vector<string> filecontentByLine=readFiletoStringVectorByLine(filename);
//    string filecontent=readFileToString(filename);
//    for(auto b=filecontentByLine.cbegin();b!=filecontentByLine.cend();++b){
//        cout<<*b<<"\n";
//    }
    
    string a="   wer";
//    jsonContext testcontext=new jsonContext(a);
//    cout<<jsonParseWhitespace(testcontext);
//    cin>>test;
//    // insert code here...
//    cout << filecontent;
    return 0;
}

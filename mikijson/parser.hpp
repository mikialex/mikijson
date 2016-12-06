//
//  parser.hpp
//  mikijson
//
//  Created by MikiAlex on 16/12/6.
//  Copyright © 2016年 MikiAlex. All rights reserved.
//

#ifndef parser_hpp
#define parser_hpp

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

//json节点类型
enum jsonType{
    JSON_NULL,
    JSON_FALSE,
    JSON_TRUE,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
};

//json parse 结果
enum jsonParseResult{
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

//json文本内容
class jsonContext{
public:
    string json;
};

//获取json节点数据类型
jsonType getJsonType(const jsonNode node);


static void jsonParseWhitespace(jsonContext c){
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
};

static int jsonParseNull(jsonContext c,jsonNode v){
    //    if (c.json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
    //        return LEPT_PARSE_INVALID_VALUE;
    //    c->json += 3;
    //    v->type = LEPT_NULL;
    return JSON_PARSE_OK;
};

//解析json节点
static int jsonParseNode(jsonContext c, jsonNode v) {
    switch (*c.json.cbegin()) {
        case 'n':  return jsonParseNull(c, v);
        case '\0': return JSON_PARSE_EXPECT_VALUE;
        default:   return JSON_PARSE_INVALID_VALUE;
    }
};

//从json字符串解析json树
int jsonParse(jsonNode rootNode,  const string jsonRawString){
    jsonContext c;
    //    assert(v != NULL);
    c.json = jsonRawString;
    rootNode.type = JSON_NULL;//如果失败正好是json_null
    jsonParseWhitespace(c);
    return jsonParseNode(c, rootNode);
};



#endif /* parser_hpp */

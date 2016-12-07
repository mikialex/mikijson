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
    string s;
    double n;//对于数值节点，存放节点数值
    jsonType type;//节点类型
};

//json文本内容
class jsonContext{
public:
    string json;//文本内容
    string::iterator currentP;//当前解析位置
};

//获取json节点数据类型
jsonType getJsonType(const jsonNode node);


void jsonParseWhitespace(jsonContext &c);
int jsonParseTrue(jsonContext &c,jsonNode &v);
int jsonParseFalse(jsonContext &c,jsonNode &v);
int jsonParseNull(jsonContext &c,jsonNode &v);
int jsonParseNumber(jsonContext &c,jsonNode &v);

//解析json节点
int jsonParseNode(jsonContext &c, jsonNode &v);

//从json字符串解析json树
int jsonParse(jsonNode &rootNode,  const string &jsonRawString);



#endif /* parser_hpp */

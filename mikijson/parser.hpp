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
#include <vector>
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
string jsonTypeToString(jsonType t);

//json parse 结果
enum jsonParseResult{
    JSON_PARSE_OK = 0,
    JSON_PARSE_EXPECT_VALUE,
    JSON_PARSE_INVALID_VALUE,
    JSON_PARSE_ROOT_NOT_SINGULAR,
    JSON_PARSE_MISS_QUOTATION_MARK,
    JSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET,
    JSON_PARSE_ERROR_OBJECT_NAME,
    JSON_PARSE_MISS_COMMA_OR_CURLY_BRACKET
};
string jsonParseResultToString(jsonParseResult t);

//class jsonArrayType;//前向声明

//json节点
class jsonNode{
public:
    string name;//名称
    vector<jsonNode> objectNodes;//对象节点，存放对象成员
    vector<jsonNode> arrayNodes;//数组节点，存放数组成员
    string s; //字符串节点，存放字符串
    double n;//数值节点，存放节点数值
    jsonType type;//节点类型
};

//class jsonArrayType{
//public:
//    vector<jsonNode> nodes;
//};

//json文本内容
class jsonContext{
public:
    string json;//文本内容
    string::iterator currentP;//当前解析位置
};

//获取json节点数据类型
jsonType getJsonType(const jsonNode node);


void jsonParseWhitespace(jsonContext &c);
jsonParseResult jsonParseTrue(jsonContext &c,jsonNode &v);
jsonParseResult jsonParseFalse(jsonContext &c,jsonNode &v);
jsonParseResult jsonParseNull(jsonContext &c,jsonNode &v);
jsonParseResult jsonParseNumber(jsonContext &c,jsonNode &v);
jsonParseResult jsonParseString(jsonContext &c,jsonNode &v);
jsonParseResult jsonParseStringWithOutNode(jsonContext &c,string &out);
jsonParseResult jsonParseArray(jsonContext &c,jsonNode &v);
jsonParseResult jsonParseObject(jsonContext &c,jsonNode &v);

//解析json节点
jsonParseResult jsonParseNode(jsonContext &c, jsonNode &v);

//从json字符串解析json树
jsonParseResult jsonParse(jsonNode &rootNode,  const string &jsonRawString);



#endif /* parser_hpp */

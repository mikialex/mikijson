//
//  parser.cpp
//  mikijson
//
//  Created by MikiAlex on 16/12/6.
//  Copyright © 2016年 MikiAlex. All rights reserved.
//

#include "parser.hpp"

string jsonTypeToString(jsonType t){
    switch (t) {
        case JSON_STRING:
            return "字符串JSON_STRING";
        case JSON_ARRAY:
            return "数组JSON_ARRAY";
        default:
            return "unknow type";
    }
};

//JSON_PARSE_OK = 0,
//JSON_PARSE_EXPECT_VALUE,
//JSON_PARSE_INVALID_VALUE,
//JSON_PARSE_ROOT_NOT_SINGULAR,
//JSON_PARSE_MISS_QUOTATION_MARK
string jsonParseResultToString(jsonParseResult t){
    switch (t) {
        case JSON_PARSE_OK:
            return "JSON_PARSE_OK";
        case JSON_PARSE_EXPECT_VALUE:
            return "JSON_PARSE_EXPECT_VALUE";
        case JSON_PARSE_INVALID_VALUE:
            return "JSON_PARSE_INVALID_VALUE";
        case JSON_PARSE_ROOT_NOT_SINGULAR:
            return "JSON_PARSE_ROOT_NOT_SINGULAR";
        case JSON_PARSE_MISS_QUOTATION_MARK:
            return "JSON_PARSE_MISS_QUOTATION_MARK";
        default:
            return "unknow result";
    }
};

void jsonParseWhitespace(jsonContext &c){
    auto p=c.currentP;
    while(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r'){
        p++;
    }
    c.currentP=p;
};

jsonParseResult jsonParseNull(jsonContext &c,jsonNode &v){
    auto p=c.currentP;
    if (*p != 'n' || *(p+1) != 'u' || *(p+2) != 'l' || *(p+3) != 'l'){
        return JSON_PARSE_INVALID_VALUE;
    }
    p=p+4;
    c.currentP=p;
    v.type = JSON_NULL;
    return JSON_PARSE_OK;
};
jsonParseResult jsonParseTrue(jsonContext &c,jsonNode &v){
    auto p=c.currentP;
    if (*p != 't' || *(p+1) != 'r' || *(p+2) != 'u' || *(p+3) != 'e'){
        return JSON_PARSE_INVALID_VALUE;
    }
    p=p+4;
    c.currentP=p;
    v.type = JSON_TRUE;
    return JSON_PARSE_OK;
};
jsonParseResult jsonParseFalse(jsonContext &c,jsonNode &v){
    auto p=c.currentP;
    if (*p != 'f' || *(p+1) != 'a' || *(p+2) != 'l' || *(p+3) != 's'|| *(p+4) != 'e'){
        return JSON_PARSE_INVALID_VALUE;
    }
    p=p+5;
    c.currentP=p;
    v.type = JSON_FALSE;
    return JSON_PARSE_OK;
};

inline bool isDigital(char c){
    if (c == '0' || c == '1'||c == '2'||c == '3'||c == '4' || c == '5'||c == '6'||c == '7'||c == '8'||c == '9'){
        return true;
    }
    return false;
};

inline bool isDigitalWithoutZero(char c){
    if ( c == '1'||c == '2'||c == '3'||c == '4' || c == '5'||c == '6'||c == '7'||c == '8'||c == '9'){
        return true;
    }
    return false;
};

jsonParseResult jsonParseNumber(jsonContext &c,jsonNode &v){
    auto p=c.currentP;
    
    //判断数字是否合法，同时推进解析迭代器前进
    //小数点前
    if (*p == '-') p++;
    if (*p == '0') p++;
    else {
        if (!isDigitalWithoutZero(*p)) return JSON_PARSE_INVALID_VALUE;//第一位要不是负号要不是非零数字
        for (p++; isDigital(*p); p++);        //一串数字
    }
    //小数点后
    if (*p == '.') {
        p++;
        if (!isDigital(*p)) return JSON_PARSE_INVALID_VALUE;//小数点后一定是数字
        for (p++; isDigital(*p); p++);//一串数字
    }
    //科学计数法部分
    if (*p == 'e' || *p == 'E') {
        p++;
        if (*p == '+' || *p == '-') p++;//可能有＋－号
        if (!isDigital(*p)) return JSON_PARSE_INVALID_VALUE;//一定是数字
        for (p++; isDigital(*p); p++);//一串数字
    }
    
    v.n = stod(c.json);
    c.currentP=p;
    v.type = JSON_NUMBER;
    return JSON_PARSE_OK;
};


jsonParseResult jsonParseString(jsonContext &c,jsonNode &v){
    auto p=c.currentP;
    string s;
    p++;
    for (;;) {
        char ch = *p;
        switch (ch) {
            case '\"':
                p++;
                c.currentP=p;
                v.s=s;
                v.type = JSON_STRING;
                return JSON_PARSE_OK;
            case '\0':
                return JSON_PARSE_MISS_QUOTATION_MARK;
            default:
                s.push_back(ch);
        }
        p++;
    }
};



//解析json节点
jsonParseResult jsonParseNode(jsonContext &c, jsonNode &v) {
    
    switch (*c.currentP) {
        case 't': return jsonParseTrue(c,v);
        case 'f': return jsonParseFalse(c, v);
        case 'n':  return jsonParseNull(c, v);
        default:   return jsonParseNumber(c, v);
        case '"':  return jsonParseString(c, v);
        case '\0': return JSON_PARSE_EXPECT_VALUE;
        //        default:   return JSON_PARSE_INVALID_VALUE;
    }
};

//从json字符串解析json树
jsonParseResult jsonParse(jsonNode &rootNode,  const string &jsonRawString){
    
    jsonContext c;
    c.json = jsonRawString;
    c.currentP=c.json.begin();
    jsonParseResult ret;
//    assert(v != NULL);
    rootNode.type = JSON_NULL;
    jsonParseWhitespace(c);
    if ((ret = jsonParseNode(c, rootNode)) == JSON_PARSE_OK) {
        jsonParseWhitespace(c);
        if (*c.currentP != '\0')
            ret = JSON_PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
    
};





//
//  parser.cpp
//  mikijson
//
//  Created by MikiAlex on 16/12/6.
//  Copyright © 2016年 MikiAlex. All rights reserved.
//

#include "parser.hpp"

void jsonParseWhitespace(jsonContext &c){
    auto p=c.currentP;
    while(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r'){
        p++;
    }
    c.currentP=p;
};

int jsonParseNull(jsonContext &c,jsonNode &v){
    auto p=c.currentP;
    if (*p != 'n' || *(p+1) != 'u' || *(p+2) != 'l' || *(p+3) != 'l'){
        return JSON_PARSE_INVALID_VALUE;
    }
    p=p+4;
    c.currentP=p;
    v.type = JSON_NULL;
    return JSON_PARSE_OK;
};
int jsonParseTrue(jsonContext &c,jsonNode &v){
    auto p=c.currentP;
    if (*p != 't' || *(p+1) != 'r' || *(p+2) != 'u' || *(p+3) != 'e'){
        return JSON_PARSE_INVALID_VALUE;
    }
    p=p+4;
    c.currentP=p;
    v.type = JSON_TRUE;
    return JSON_PARSE_OK;
};
int jsonParseFalse(jsonContext &c,jsonNode &v){
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

int jsonParseNumber(jsonContext &c,jsonNode &v){
    auto p=c.currentP;
    
    if (*p == '-') p++;
    if (*p == '0') p++;
    else {
        if (!isDigitalWithoutZero(*p)) return JSON_PARSE_INVALID_VALUE;
        for (p++; isDigital(*p); p++);
    }
    
    if (*p == '.') {
        p++;
        if (!isDigital(*p)) return JSON_PARSE_INVALID_VALUE;
        for (p++; isDigital(*p); p++);
    }
    if (*p == 'e' || *p == 'E') {
        p++;
        if (*p == '+' || *p == '-') p++;
        if (!isDigital(*p)) return JSON_PARSE_INVALID_VALUE;
        for (p++; isDigital(*p); p++);
    }
    
    v.n = stod(c.json);
    c.currentP=p;
    v.type = JSON_NUMBER;
    return JSON_PARSE_OK;
}




//解析json节点
int jsonParseNode(jsonContext &c, jsonNode &v) {
    
    switch (*c.currentP) {
        case 't': return jsonParseTrue(c,v);
        case 'f': return jsonParseFalse(c, v);
        case 'n':  return jsonParseNull(c, v);
        default:   return jsonParseNumber(c, v);
        case '\0': return JSON_PARSE_EXPECT_VALUE;
        //        default:   return JSON_PARSE_INVALID_VALUE;
    }
};

//从json字符串解析json树
int jsonParse(jsonNode &rootNode,  const string &jsonRawString){
    
    jsonContext c;
    c.json = jsonRawString;
    c.currentP=c.json.begin();
    int ret;
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





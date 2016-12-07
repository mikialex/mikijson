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

int jsonParseNumber(jsonContext &c,jsonNode &v){
//    char* end;
//    /* \TODO validate number */
//    v->n = strtod(c->json, &end);
//    if (c->json == end)
//        return LEPT_PARSE_INVALID_VALUE;
//    c->json = end;
//    v.type = JSON_NUMBER;
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





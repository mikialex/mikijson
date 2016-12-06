//
//  parser.cpp
//  mikijson
//
//  Created by MikiAlex on 16/12/6.
//  Copyright © 2016年 MikiAlex. All rights reserved.
//

#include "parser.hpp"

void jsonParseWhitespace(jsonContext &c){
    string raw = c.json;
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

int jsonParseNull(jsonContext &c,jsonNode &v){
    if (c.json[0] != 'n' || c.json[1] != 'l' || c.json[2] != 'l'){
        return JSON_PARSE_INVALID_VALUE;
    }
    //    c->json += 3;
    //    v->type = LEPT_NULL;
    return JSON_PARSE_OK;
};



//解析json节点
int jsonParseNode(jsonContext &c, jsonNode &v) {
    switch (c.json[0]) {
//        case 't': return jsonParseTrue(c,v);
//        case 'f': return jsonParseFalse(c, v);
        case 'n':  return jsonParseNull(c, v);
        case '\0': return JSON_PARSE_EXPECT_VALUE;
        default:   return JSON_PARSE_INVALID_VALUE;
    }
};

//从json字符串解析json树
int jsonParse(jsonNode rootNode,  const string jsonRawString){
//    jsonContext c;
//    //    assert(v != NULL);
//    c.json = jsonRawString;
//    rootNode.type = JSON_NULL;//如果失败正好是json_null
//    jsonParseWhitespace(c);
//    return jsonParseNode(c, rootNode);
    
    jsonContext c;
    c.json = jsonRawString;
    int ret;
//    assert(v != NULL);
    rootNode.type = JSON_NULL;
    jsonParseWhitespace(c);
    if ((ret = jsonParseNode(c, rootNode)) == JSON_PARSE_OK) {
        jsonParseWhitespace(c);
        if (c.json[0] != '\0')
            ret = JSON_PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
    
};





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
    if (c.json[0] != 'n' || c.json[1] != 'u' || c.json[2] != 'l' || c.json[3] != 'l'){
        return JSON_PARSE_INVALID_VALUE;
    }
    string back;
    for(auto d=c.json.begin()+4;d!=c.json.end();++d){
        back.push_back(*d);
    }
    c.json=back;
    v.type = JSON_NULL;
    return JSON_PARSE_OK;
};
int jsonParseTrue(jsonContext &c,jsonNode &v){
    if (c.json[0] != 't' || c.json[1] != 'r' || c.json[2] != 'u' || c.json[3] != 'e'){
        return JSON_PARSE_INVALID_VALUE;
    }
    string back;
    for(auto d=c.json.begin()+4;d!=c.json.end();++d){
        back.push_back(*d);
    }
    c.json=back;
    v.type = JSON_TRUE;
    return JSON_PARSE_OK;
};
int jsonParseFalse(jsonContext &c,jsonNode &v){
    if (c.json[0] != 'f' || c.json[1] != 'a' || c.json[2] != 'l' || c.json[3] != 's'|| c.json[4] != 'e'){
        return JSON_PARSE_INVALID_VALUE;
    }
    string back;
    for(auto d=c.json.begin()+5;d!=c.json.end();++d){
        back.push_back(*d);
    }
    c.json=back;
    v.type = JSON_FALSE;
    return JSON_PARSE_OK;
};




//解析json节点
int jsonParseNode(jsonContext &c, jsonNode &v) {
    switch (c.json[0]) {
        case 't': return jsonParseTrue(c,v);
        case 'f': return jsonParseFalse(c, v);
        case 'n':  return jsonParseNull(c, v);
        case '\0': return JSON_PARSE_EXPECT_VALUE;
        default:   return JSON_PARSE_INVALID_VALUE;
    }
};

//从json字符串解析json树
int jsonParse(jsonNode &rootNode,  const string &jsonRawString){
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





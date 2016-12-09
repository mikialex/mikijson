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
        case JSON_NULL:
            return "JSON_NULL";
        case JSON_TRUE:
            return "JSON_TRUE";
        case JSON_FALSE:
            return "JSON_FALSE";
        case JSON_NUMBER:
            return "数字JSON_NUMBER";
        case JSON_OBJECT:
            return "对象JSON_OBJECT";
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
        case JSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET:
            return "JSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET";
        case JSON_PARSE_ERROR_OBJECT_NAME:
            return "JSON_PARSE_ERROR_OBJECT_NAME";
        case JSON_PARSE_MISS_COMMA_OR_CURLY_BRACKET:
            return "JSON_PARSE_MISS_COMMA_OR_CURLY_BRACKET";
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
    auto pOld=p;
    
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
    string numParseString;;
    while(pOld!=p){
        numParseString.push_back(*pOld);
        pOld++;
    }
    v.n = stod(numParseString);
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
jsonParseResult jsonParseStringWithOutNode(jsonContext &c,string &out){
    auto p=c.currentP;
    string s;
    p++;
    for (;;) {
        char ch = *p;
        switch (ch) {
            case '\"':
                p++;
                c.currentP=p;
                out=s;
                return JSON_PARSE_OK;
            case '\0':
                return JSON_PARSE_MISS_QUOTATION_MARK;
            default:
                s.push_back(ch);
        }
        p++;
    }
};

jsonParseResult jsonParseArray(jsonContext &c,jsonNode &v){
    auto p=c.currentP;
    jsonParseResult ret;
    p++;
    c.currentP=p;
    jsonParseWhitespace(c);
    if(*p==']'){ //空数组
        p++;
        v.type = JSON_ARRAY;   //node的type是array，array却是空的，那就是[]
        return JSON_PARSE_OK;
    }
    for(;;){
        jsonNode node;
        jsonParseWhitespace(c);
        ret=jsonParseNode(c, node);
        jsonParseWhitespace(c);
        p=c.currentP;
        if(ret==JSON_PARSE_OK){
            v.arrayNodes.push_back(node);
        }else{
            return JSON_PARSE_INVALID_VALUE;
        }
        
        if(*p==','){//还有内容
            p++;
            c.currentP=p;
            continue;
        }else if(*p==']'){//结束
            p++;
            c.currentP=p;
            v.type = JSON_ARRAY;
            return JSON_PARSE_OK;
        }else{
            ret= JSON_PARSE_MISS_COMMA_OR_SQUARE_BRACKET;
            break;
        }
    }
    return ret;
}


jsonParseResult jsonParseObject(jsonContext &c,jsonNode &v){
    auto p=c.currentP;
    jsonParseResult ret;
    p++;
    c.currentP=p;
    jsonParseWhitespace(c);
    if(*p=='}'){ //空对象
        p++;
        v.type = JSON_ARRAY;   //node的type是object，object却是空的，那就是{}
        return JSON_PARSE_OK;
    }
    for(;;){
        string name;
        if(jsonParseStringWithOutNode(c,name)==JSON_PARSE_OK){
            p=c.currentP;
            p++;c.currentP++;
            jsonNode node;
            node.name=name;
            jsonParseWhitespace(c);
            ret=jsonParseNode(c, node);
            jsonParseWhitespace(c);
            p=c.currentP;
            if(ret==JSON_PARSE_OK){
                v.objectNodes.push_back(node);
            }else{
                return JSON_PARSE_INVALID_VALUE;
            }
            
            if(*p==','){//还有内容
                p++;
                c.currentP=p;
                continue;
            }else if(*p=='}'){//结束
                p++;
                c.currentP=p;
                v.type = JSON_OBJECT;
                return JSON_PARSE_OK;
            }else{
                ret= JSON_PARSE_MISS_COMMA_OR_CURLY_BRACKET;
                break;
            }
            
        }else{
            return JSON_PARSE_ERROR_OBJECT_NAME;
        }
    }
    
    return ret;
}


//解析json节点
jsonParseResult jsonParseNode(jsonContext &c, jsonNode &v) {
    
    switch (*c.currentP) {
        case '\0': return JSON_PARSE_EXPECT_VALUE;
        case 't': return jsonParseTrue(c,v);
        case 'f': return jsonParseFalse(c, v);
        case 'n':  return jsonParseNull(c, v);
        case '"':  return jsonParseString(c, v);
        case '[':  return jsonParseArray(c, v);
        case '{':  return jsonParseObject(c, v);
        default:   return jsonParseNumber(c, v);
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





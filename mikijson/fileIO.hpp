//
//  fileIO.hpp
//  mikijson
//
//  Created by MikiAlex on 16/12/6.
//  Copyright © 2016年 MikiAlex. All rights reserved.
//

#ifndef fileIO_hpp
#define fileIO_hpp

#include <stdio.h>
#include <vector>

using namespace std;

//读取文本文件至单独一个string
inline string readFiletoString(const string filename);

//读取文本文件至vector，每个元素为一行
inline vector<string> readFiletoStringVectorByLine(const string filename);

#endif /* fileIO_hpp */

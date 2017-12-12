/*
 *
 * 
 * 
 * 
 * 
 */


#ifndef __FIND_WAY__
#define __FIND_WAY__

#include "procnode.h"
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

/* 
 * 同过pid查找迭代器，用于find_if函数
 */
class findByPid{
private:
    int pid;

public:
    findByPid(char * pid);
    bool operator()(vector<proc_node>::value_type &value);
};


#endif
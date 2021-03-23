#ifndef UTIL_H
#define UTIL_H

#include<vector>
#include<cmath>
#include<iostream>

namespace car{
    void extendLuby(std::vector<int> &luby);
    bool generateLuby(std::vector<int> &luby, int totalExponent = 16);
    void printLuby(std::vector<int> &luby);
}

#endif
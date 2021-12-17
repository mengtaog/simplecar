#ifndef SETTINGS_H
#define SETTINGS_H

#include<iostream>

namespace car
{

struct Settings
{
    bool forward = false;
    bool verbose = false;
    bool evidence = false;
    bool minimal_uc = false;
    bool restart = false;
    bool gv = false;
    bool begin = false;
    bool end = true;
    bool inter = false;
    bool rotate = false;
    bool inputS = false;
    int timelimit = 0; 
    std::string aigFilePath;
    std::string outputDir;
};


}

#endif
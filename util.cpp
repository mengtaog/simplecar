#include"util.h"

namespace car{
    bool generateLuby(std::vector<int> &luby, int totalExponent = 16){
        if(luby.size() > 0){
            return false;
        }
        //init
        luby.push_back(1);
        luby.push_back(1);
        
        int total = pow(2, totalExponent) - 2; 
        int i = 2,n = 4;
        while(i <= total){
            if(i == n - 2){
                luby.push_back(n/2);
                n = n * 2;
                ++i;
            }
            else{
                luby.push_back(luby[i - n/2 + 1]);
                ++i;
            }
        }
    }

    void printLuby(std::vector<int> &luby){
        for(std::vector<int>::iterator it = luby.begin(); it != luby.end(); ++it){
            std::cout<<*it<<std::endl;
        }
    }

    void extendLuby(std::vector<int> &luby){
        int length = luby.size();
        int exp;
        for(int i = 1; ;++i){
            if(pow(2,i)-1 == length){
                exp = i;
                break;
            }
        }
        int i = length,total = pow(2,exp+1)-2;
        while(i <=total){
            if(i == total){
                luby.push_back((total+2)/2);
                ++i;
            }
            else{
                luby.push_back(luby[i - (total+2)/2 + 1]);
                ++i;
            }
        }
    }
}
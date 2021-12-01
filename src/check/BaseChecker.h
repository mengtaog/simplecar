#ifndef BASECHECKER_H
#define BASECHECKER_H

#include "../model/AigerModel.h"
#include "../model/Settings.h"

namespace car
{

    class BaseChecker
    {
    public:
        virtual bool Check() = 0;
    };

} //namespace car



#endif

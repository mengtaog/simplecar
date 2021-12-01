#ifndef BASECHECKER_H
#define BASECHECKER_H

#include "../model/AigerModel.h"

namespace car
{

    class BaseChecker
    {
    public:
        virtual bool Check() = 0;
    private:
        AigerModel* m_model;
    };

} //namespace car



#endif

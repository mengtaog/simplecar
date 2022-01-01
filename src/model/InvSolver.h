#ifndef INVSOLVER_H
#define INVSOLVER_H

#include "CarSolver.h"
namespace car
{

class InvSolver : public CarSolver
{
public:
    InvSolver(std::shared_ptr<AigerModel> model);
private:
};

}//namespace car

#endif
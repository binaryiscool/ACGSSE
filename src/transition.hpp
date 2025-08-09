#ifndef TRANSITION
#define TRANSITION

#include <srl.hpp>
#include "RedVelvet/rv.hpp"

using namespace SRL::Types;
using namespace SRL::Math::Types;

class Transition {
    public:
        static int transState;

        /*
        0 = Not Active
        1 = In Anim
        2 = Covered
        3 = Out Anim
        */

        static Vector2D transPoints[4];
};

#endif
#include "Position_Generator_Outside.h"

#include "Fishy_GUI.h"
#include "Fishy_Tank_GUI.h"
#include "Constants.h"

#include <cstdlib>

namespace GUI{
    void PosGen_Outside::operator() (Fishy& fish, const Tank& tank)const{
        bool right = std::rand()%2u;
        fish.setPosition(
            right*tank.getSize().x + Constant::arb_shift*(right*2-1),
            std::rand()%static_cast<unsigned>(tank.getSize().y)
        );
    }
}

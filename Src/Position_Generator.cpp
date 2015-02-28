#include "Position_Generator.h"

#include "Fishy_GUI.h"
#include "Fishy_Tank_GUI.h"

#include <cstdlib>

namespace GUI{
    void PosGen::operator() (Fishy& fish, const Tank& tank)const{
        fish.setPosition(
            std::rand()%static_cast<unsigned>(tank.getSize().x),
            std::rand()%static_cast<unsigned>(tank.getSize().y)
        );
    }
}
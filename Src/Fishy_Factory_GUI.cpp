#include "Fishy_Factory_GUI.h"

#include "Collision_Detection.h"
#include "Player_Fishy_AI.h"
#include "Oblivious_Fishy_AI.h"
#include "Practice_Fishy_AI.h"
#include "Practice_Fishy_AI2.h"
#include "Fishy_Tank_GUI.h"

namespace GUI{
    Fishy* Fishy_Factory::breed(
        Fishy::mass_type newMass, Fishy::code_type newCode,
        const Resource::Manager& newResource
    ) throw(std::invalid_argument) {
        switch(newCode){
            case Fishy::code_type::Missingno:
                return new Player_Fishy(
                    newMass, newCode,
                    Collision::BoundEllipse{32, 12, 122, 25}, newResource
                    );
            case Fishy::code_type::Small_Feeder:
            case Fishy::code_type::Medium_Feeder:
            case Fishy::code_type::Large_Feeder:
                return new Oblivious_Fishy(
                    newMass, newCode,
                    Collision::BoundEllipse{28, 19, 118, 28}, newResource
                    );
            case Fishy::code_type::Small_Basic:
            case Fishy::code_type::Medium_Basic:
            case Fishy::code_type::Large_Basic:
                return new Practice_Fishy(
                    newMass, newCode,
                    Collision::BoundEllipse{32, 16, 110, 28}, newResource
                    );
/*
            case Fishy::code_type::Shark:
                return new Practice_Fishy2(
                    newMass, newCode,
                    Collision::BoundEllipse{59, 10, 120, 26}, newResource,
                    40u, 2.0/3.0
                    );
*/
            default:
                throw std::invalid_argument("Invalid code");
        }
    }

    void Fishy_Factory::addFish(
        Fishy::mass_type newMass, Fishy::code_type newCode,
        unsigned newPop, Tank& target, const PosGen& posGen
    ) throw(std::invalid_argument){
        while(newPop-- > 0u){
            Fishy* newFish = Fishy_Factory::breed(
                newMass, newCode,
                target.getResource()
                );
            posGen(*newFish, target);
            target.addFish(Tank::fishPtr(newFish));
        }
    }

    void Fishy_Factory::fillTank(
            Fishy::mass_type newMass, Fishy::code_type newCode,
            unsigned newPop, Tank& target, const PosGen& posGen
    ) throw(std::invalid_argument) {
        target.breed(newCode, newMass, newPop);
        for(auto it = target.begin(); it != target.end(); ++it)
            posGen(*it->second, target);
    }
}
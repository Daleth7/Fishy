#include "Oblivious_Fishy_AI.h"

#include "Constants_GUI.h"

#include <cstdlib>

namespace GUI{
    Oblivious_Fishy::Oblivious_Fishy(
        mass_type newMass, code_type newCode,
        BoundType newBound,
        const Resource::Manager& newResource,
        unsigned newFrameRateLimit
    )
        : Fishy(newMass, newCode, newBound, newResource)
        , mDecisionDelay(0), mFLim(newFrameRateLimit)
    {}

    Oblivious_Fishy::~Oblivious_Fishy(){}

    void Oblivious_Fishy::eat_concrete(const Data::Fishy& target)
        {this->grow(target.mass()/10000.0);}

    void Oblivious_Fishy::updateConcrete(){
        if(mDecisionDelay == 0){
            if(std::rand()%2u)  this->flip();
                // Make decision every 1 to 3 seconds
            mDecisionDelay = mFLim * (1u + (std::rand()%3u) + 1);
        }
        this->move(
            Constant::baseSpeed*(this->flipped() ? -1 : 1),
            Constant::baseSpeed*(std::rand()%2u - 1.0)/16.0
        );
        --mDecisionDelay;
    }
}
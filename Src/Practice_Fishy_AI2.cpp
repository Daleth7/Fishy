#include "Practice_Fishy_AI2.h"

#include "Constants_GUI.h"
#include "Constants.h"

#include <cmath>
#include <cstdlib>

namespace GUI{
    Practice_Fishy2::Practice_Fishy2(
        mass_type newMass, code_type newCode, BoundType newBound,
        const Resource::Manager& newResource,
        unsigned newFrameRateLimit, double newFreq
    )
        : Fishy(newMass, newCode, newBound, newResource)
        , mDecisionDelay(0), mFLim(newFrameRateLimit), mTime(0), mFreq(newFreq)
    {}

    Practice_Fishy2::~Practice_Fishy2(){}

    void Practice_Fishy2::eat_concrete(const Data::Fishy& target)
        {this->grow(target.mass()/100.0);}

    void Practice_Fishy2::updateConcrete(){
        if(mDecisionDelay == 0){
            if(std::rand()%2u)  this->flip();
                // Make decision every 1 to 10 seconds
            mDecisionDelay = mFLim * (1u + (std::rand()%10u) + 1);
        }
        this->move(
            Constant::baseSpeed*(this->flipped() ? -1 : 1),
            Constant::baseSpeed*std::sin(2.0*::Constant::pi*mFreq*mTime)
                + (std::rand()%3-1)
        );
        --mDecisionDelay;
        mTime += 1.0/mFLim;
    }
}

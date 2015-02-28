/**
 *  \file Position_Generator_Outside.h
 *  \brief Contains the abstract interface for a position generator
 *      that sets fish inside a tank. This generator positions the
 *      fish outside the visible tank area.
 */

#ifndef POSGEN_OUTSIDE_TANK_HEADERHHHH_3823893289
#define POSGEN_OUTSIDE_TANK_HEADERHHHH_3823893289

#include "Position_Generator.h"

namespace GUI{
    struct PosGen_Outside : PosGen {
        /**
         *  \brief Moves the fish to a position outside the visible
         *      tank area.
         *  
         *  \param [in] fish Fish to set the position for.
         *  \param [in] tank Area to place the fish in.
         *  
         *  \details Randomly generates using std::rand().
         */
        virtual void operator()
            (Fishy& fish, const Tank& tank)const override;

        virtual ~PosGen_Outside(){}
    };
}

#endif
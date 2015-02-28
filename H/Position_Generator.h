/**
 *  \file Position_Generator.h
 *  \brief Contains the interface to a position generator for
 *      positioning fish inside a given tank.
 */

#ifndef POSITION_HEADER_INTERFACE_32893892HHHH_
#define POSITION_HEADER_INTERFACE_32893892HHHH_

namespace GUI{
    class Fishy;
    class Tank;

    struct PosGen{
        /**
         *  \brief Generates a random position for the fish to
         *      sit in the tank.
         *  
         *  \param [in] fish Fish to set the position for.
         *  \param [in] tank Area to place the fish in.
         *  
         *  \details By default, the position is just a random
         *      location inside the visible tank area.
         */
        virtual void operator() (Fishy& fish, const Tank& tank)const;

        virtual ~PosGen(){}
    };
}

#endif

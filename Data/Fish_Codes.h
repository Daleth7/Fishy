/**
 *  \file Fish_Codes.h
 *  \brief Contains unique identifiers for types of fish.
 */

#ifndef TILE_DATA_ENUMERATION_TYPE_HHH221231225_HHHH_H_
#define TILE_DATA_ENUMERATION_TYPE_HHH221231225_HHHH_H_

namespace Data{
    namespace Fish{
        typedef short raw_type;
        enum class code : raw_type{
            Missingno = 0,
            Small_Feeder, Medium_Feeder, Large_Feeder,
            Small_Basic, Medium_Basic, Large_Basic,
            Shark, Turtle, Ray, Shrimp,
        // Non-fishy stuff
            Button, ButtonPressed, ReturnButton, ReturnButtonPressed,
        };
    }
}

#endif
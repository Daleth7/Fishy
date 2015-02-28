/**
 *  \file Fishy_Factory_GUI.h
 *  \brief Contains all factory methods to simplify generating fish.
 */

#ifndef FISHY_FACTORY_HEADER_HH2323838HHHH
#define FISHY_FACTORY_HEADER_HH2323838HHHH

#include "Fishy_GUI.h"
#include "Position_Generator.h"

#include <stdexcept>

namespace GUI{
    struct Fishy_Factory{
        /**
         *  \brief Create a single fish object on the heap.
         *  
         *  \param [in] newMass Starting mass of the fish.
         *  \param [in] newCode Unique identifier of the fish type.
         *  \param [in] newResource Resource manager that the fish
         *      sprite will use.
         *  \return A pointer to the new fish on the heap.
         *  
         *  \details May throw an exception if the fish
         *      code is invalid.
         */
        static Fishy* breed(
            Fishy::mass_type newMass, Fishy::code_type newCode,
            const Resource::Manager& newResource
        ) throw(std::invalid_argument);
        /**
         *  \brief Create a fish and add it to an existing tank.
         *  
         *  \param [in] newMass Starting mass of the fish.
         *  \param [in] newCode Unique identifier of the fish type.
         *  \param [in] newPop Number of fish to add to generate.
         *  \param [in] target The tank to add the fish to.
         *  \param [in] posGen Position generator to determine
         *      where in the tank the fish will be.
         *  
         *  \details Does not empty the tank of any existing fish.
         *      May throw an exception if the fish code is invalid.
         */
        static void addFish(
            Fishy::mass_type newMass, Fishy::code_type newCode,
            unsigned newPop, Tank& target, const PosGen& posGen
        ) throw(std::invalid_argument);
        /**
         *  \brief Fill an empty tank with one type of fish.
         *  
         *  \param [in] newMass Starting mass of the fish.
         *  \param [in] newCode Unique identifier of the fish type.
         *  \param [in] newPop Number of fish to add to generate.
         *  \param [in] target The tank to add the fish to.
         *  \param [in] posGen Position generator to determine
         *      where in the tank the fish will be.
         *  
         *  \details Assumes the tank is empty. Any existing fish
         *      will be repositioned. May throw an exception if
         *      the fish code is invalid.
         */
        static void fillTank(
            Fishy::mass_type newMass, Fishy::code_type newCode,
            unsigned newPop, Tank& target, const PosGen& posGen
        ) throw(std::invalid_argument);
    };
}

#endif
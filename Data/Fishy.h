/**
 *  \file Fishy.h
 *  \brief Contains the class that represents the data model of
 *      the "fish".
 */

#ifndef FISHY_HEADER_2872828HHH_HHHH_____
#define FISHY_HEADER_2872828HHH_HHHH_____

#include "Units.h"
#include "Fish_Codes.h"

namespace Data{
    class Fishy{
        public:
            using mass_type = Unit::gram;
            using code_type = Fish::code;

            /**
             *  \brief Returns the mass of the fish.
             *  
             *  \return mass in grams
             */
            mass_type mass()const;
            /**
             *  \brief Returns a code that uniquely
             *      identifies the fish type.
             *  
             *  \return enumerated code name
             */
            code_type code()const;
            /**
             *  \brief Determine if "this" fish would be
             *      able to eat the target.
             *  
             *  \param [in] target Potential victim.
             *  \return Code number that indicates one of three
             *      possibilities:
             *      2 ~ Neither fish is large enough to eat the other.
             *      1 ~ This fish is big enough to eat target.
             *    0 ~ Target fish is big enough to eat this fish.
             *  
             *  \details The "eat" action does not occur. Merely
             *      an indication determined by mass.
             */
            short try_to_eat(const Fishy& target)const;

            /**
             *  \brief Use target fish's information to update
             *      this fish.
             *  
             *  \param [in] target Victim.
             *  
             *  \details This function assumes that
             *      this->try_to_eat(target) returns 1.
             */
            void eat(const Fishy& target);
            /**
             *  \brief Sole constructor.
             *  
             *  \param [in] new_mass Set the
             *      starting mass of the fish.
             *  \param [in] new_code Fish type identification code.
             *  
             *  \details Call only in children classes since this
             *      class is an abstract interface.
             */
            Fishy(mass_type new_mass, code_type new_code);

            Fishy(const Fishy&)             = default;
            Fishy(Fishy&&)                  = default;
            Fishy& operator=(const Fishy&)  = default;
            Fishy& operator=(Fishy&&)       = default;
            virtual ~Fishy();

        protected:
            /**
             *  \brief Concrete method for users to implement.
             *  
             *  \param [in] target The victim.
             *  
             *  \details Called by void Fishy::eat(const Fishy&).
             *      Use information from the target to update this
             *      fish.
             */
            virtual void eat_concrete(const Fishy& target) = 0;

            mass_type   m_mass;
            code_type   m_code;
    };
}

#endif
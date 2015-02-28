#include "Fishy.h"

namespace Data{
    Fishy::mass_type Fishy::mass()const
        {return m_mass;}

    Fishy::code_type Fishy::code()const
        {return m_code;}

    short Fishy::try_to_eat(const Fishy& target)const{
            // Determine which fish is larger with
            //  some margin of error.
        const double err = 1e-1;
        if(target.m_mass < this->m_mass-err)    return 1;
        if(this->m_mass < target.m_mass-err)    return 0;
                                                return 2;
    }

    void Fishy::eat(const Fishy& target)
        {this->eat_concrete(target);}

    Fishy::Fishy(mass_type new_mass, code_type new_code)
        : m_mass(new_mass)
        , m_code(new_code)
    {}

    Fishy::~Fishy(){}
}
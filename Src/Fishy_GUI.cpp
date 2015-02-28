#include "Fishy_GUI.h"

#include "Fish_Texture_Manager_GUI.h"
#include "Collision_Detection.h"
#include "Constants_GUI.h"

#include "SFML/Graphics/Sprite.hpp"

namespace GUI{
    bool Fishy::flipped()const
        {return mFlipped;}

    const Fishy::BoundType& Fishy::bound()const
        {return mBound;}

    bool Fishy::collided(const Fishy& other)const
        {return Collision::check(*this, other, mBound, other.mBound);}

    void Fishy::update()
        {this->updateConcrete();}

    void Fishy::setTexture(
        const sf::Texture& texture,
        BoundType::pixel newLen,
        BoundType::pixel newHei,
        BoundType::pixel newCenX,
        BoundType::pixel newCenY,
        bool resetRect
    ){
        sf::Sprite::setTexture(texture, resetRect);
        mBound = BoundType{newLen, newHei, newCenX, newCenY};
    }

    void Fishy::flip(){
        mFlipped = !mFlipped;
        sf::IntRect newRect = this->getTextureRect();
        mResourcePtr->flipArea(newRect, true, false);
        this->setTextureRect(newRect);
        const double xShift
            (FishTextureManager::flipFactor(m_code, mFlipped));
        this->move(xShift, 0);
        mBound.centerX -= xShift;
    }

    void Fishy::grow(mass_type addMass){
            // No shrinking allowed
        if(addMass < 0)     return;
        const mass_type scalingFactor((addMass+mass())/mass());
        this->scale(scalingFactor, scalingFactor);
        mBound.radiusX *= scalingFactor*1.5;    //Why
        mBound.radiusY *= scalingFactor;
        m_mass += addMass;
    }

    Fishy::Fishy(
        mass_type newMass, code_type newCode,
        BoundType newBound,
        const Resource::Manager& newResource
    )
        : Data::Fishy(Constant::baseMass, newCode)
        , sf::Sprite()
        , mBound(newBound)
        , mFlipped(false)
        , mResourcePtr(&newResource)
    {
        sf::Sprite::setTexture(mResourcePtr->getSheet());
        this->setTextureRect(mResourcePtr->getArea(newCode));
        this->grow(newMass-Constant::baseMass);
    }

    Fishy::~Fishy(){}
}
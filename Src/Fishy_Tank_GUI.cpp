#include "Fishy_Tank_GUI.h"

#include "Fishy_Factory_GUI.h"
#include "Constants.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <utility>

namespace GUI{
    const Tank::fishTank& Tank::rawTank()const
        {return mTank;}

    Tank::fishTank::size_type Tank::population()const
        {return mTank.size();}

    const Resource::Manager& Tank::getResource()const
        {return *mRsrcPtr;}

    void Tank::breed(
        fishCode fish, Fishy::mass_type newMass,
        unsigned pop
    ){
        while(pop-- > 0u){
            fishPtr temp((Fishy_Factory::breed(newMass, fish, *mRsrcPtr)));
            mTank.insert({fish, std::move(temp)});
        }
    }

    void Tank::addFish(const fishPtr& newFish){
        mTank.insert({newFish->code(), newFish});
    }

    void Tank::update(){
        for(auto it = mTank.begin(); it != mTank.end(); ++it){
            const fishTank::mapped_type& fish = it->second;
            fish->update();
            float
                dx(fish->getPosition().x - mBg.getPosition().x),
                dy(fish->getPosition().y - mBg.getPosition().y)
            ;
        // Totally arbitrary shifts
            using Constant::arb_shift;
            const sf::Vector2f& bound = mBg.getSize();
            if(dx > arb_shift + bound.x){
                fish->setPosition(
                    -arb_shift - fish->getGlobalBounds().width,
                    fish->getPosition().y
                );
            } else if(dx < -arb_shift - fish->getGlobalBounds().width){
                fish->setPosition(
                    bound.x + arb_shift,
                    fish->getPosition().y
                );
            }
            if(dy > arb_shift + bound.y){
                fish->setPosition(
                    fish->getPosition().x,
                    -arb_shift - fish->getGlobalBounds().height
                );
            } else if(dy < -arb_shift - fish->getGlobalBounds().height){
                fish->setPosition(
                    fish->getPosition().x,
                    bound.y + arb_shift
                );
            }
        }
    }

    void Tank::setResource(const Resource::Manager& newRsrc)
        {mRsrcPtr = &newRsrc;}

    void Tank::draw(
        sf::RenderTarget& target,
        sf::RenderStates states
    )const{
        target.draw(mBg, states);
        for(auto it = mTank.begin(); it != mTank.end(); ++it){
            const fishTank::mapped_type& fish = it->second;
            target.draw(*fish, states);
        }
    }

    Tank::constIterator Tank::cbegin()const
        {return mTank.cbegin();}

    Tank::constIterator Tank::cend()const
        {return mTank.cend();}

    Tank::constIterator Tank::begin()const
        {return mTank.cbegin();}

    Tank::constIterator Tank::end()const
        {return mTank.cend();}

    Tank::iterator Tank::begin()
        {return mTank.begin();}

    Tank::iterator Tank::end()
        {return mTank.end();}

    void Tank::remove(iterator it)
        {mTank.erase(it);}

    void Tank::setSize(const sf::Vector2f& v)
        {mBg.setSize(v);}

    const sf::Vector2f& Tank::getSize()const
        {return mBg.getSize();}

    void Tank::setTexture(const sf::Texture& newTex)
        {mBg.setTexture(&newTex);}

    void Tank::setFillColor(const sf::Color& newCol)
        {mBg.setFillColor(newCol);}

    void Tank::clear()
        {mTank.clear();}
}

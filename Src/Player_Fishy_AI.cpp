#include "Player_Fishy_AI.h"

#include "Constants_GUI.h"

#include <SFML/Window/Mouse.hpp>

namespace GUI{
    Player_Fishy::Player_Fishy(
        mass_type newMass, code_type newCode, BoundType newBound,
        const Resource::Manager& newResource,
        KeyType newLeftCom, KeyType newAltLeft,
        KeyType newRightCom, KeyType newAltRight,
        KeyType newUpCom, KeyType newAltUp,
        KeyType newDownCom, KeyType newAltDown
    )
        : Fishy(newMass, newCode, newBound, newResource)
        , mLeftCom(newLeftCom), mAltLeft(newAltLeft)
        , mRightCom(newRightCom), mAltRight(newAltRight)
        , mUpCom(newUpCom), mAltUp(newAltUp)
        , mDownCom(newDownCom), mAltDown(newAltDown)
    {}

    Player_Fishy::~Player_Fishy(){}

    void Player_Fishy::eat_concrete(const Data::Fishy& target)
        {this->grow(target.mass()/100.0);}

    void Player_Fishy::updateConcrete(){
        if(sf::Keyboard::isKeyPressed(mLeftCom) || sf::Keyboard::isKeyPressed(mAltLeft)){
            if(!this->flipped())
                this->flip();
            this->move(-Constant::baseSpeed, 0);
        }else if(sf::Keyboard::isKeyPressed(mRightCom) || sf::Keyboard::isKeyPressed(mAltRight)){
            if(this->flipped())
                this->flip();
            this->move(Constant::baseSpeed, 0);
        }
        this->move(0
            , -Constant::baseSpeed
            * (sf::Keyboard::isKeyPressed(mUpCom) || sf::Keyboard::isKeyPressed(mAltUp)));
        this->move(0
            , Constant::baseSpeed
            * (sf::Keyboard::isKeyPressed(mDownCom) || sf::Keyboard::isKeyPressed(mAltDown)));
    }
}
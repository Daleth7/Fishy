/**
 *  \file Player_Fishy_AI.h
 *  \brief AI implementation for the player-controlled fish.
 */

#ifndef PLAYER_CONTROLLED_FISH_8388383838HHHFHFHFH_
#define PLAYER_CONTROLLED_FISH_8388383838HHHFHFHFH_

#include "Fishy_GUI.h"

#include <SFML/Window/Keyboard.hpp>

namespace GUI{
    class Player_Fishy : public Fishy {
        public:
/* Inherited from GUI::Fishy
            using BoundType;
            bool flipped()const;
            const BoundType& bound()const;
            bool collided(const Fishy& target)const;
            void update();
            void setTexture(
                const sf::Texture& texture,
                pixel newLength, pixel newHeight,
                pixel newCenterX, pixel newCenterY,
                bool resetRect = false
            );
            void flip();
            void grow(mass_type addMass);
*/

            using KeyType = sf::Keyboard::Key;
            /**
             *  \brief Sole constructor.
             *  
             *  \param [in] newMass Starting mass of the fish.
             *  \param [in] newCode Fish type identifier. This should
             *      usually be Missingno as that identifier is reserved
             *      for the player.
             *  \param [in] newBound area that will represent the
             *      collision boundary of the fish.
             *  \param [in] newResource Resource manager that will
             *      provide the texture for drawing the fish.
             *  \param [in] newLeftCom Keybind for moving left.
             *  \param [in] newAltLeft Same as previous.
             *  \param [in] newRightCom Keybind for moving right.
             *  \param [in] newAltright Same as previous.
             *  \param [in] newUpCom Keybind for moving up.
             *  \param [in] newAltUp Same as previous.
             *  \param [in] newDownCom Keybind for moving down.
             *  \param [in] newAltDown Same as previous.
             */
            Player_Fishy(
                mass_type newMass, code_type newCode,
                BoundType newBound,
                const Resource::Manager& newResource,
                KeyType newLeftCom = KeyType::A,
                KeyType newAltLeft = KeyType::Left,
                KeyType newRightCom = KeyType::D,
                KeyType newAltright = KeyType::Right,
                KeyType newUpCom = KeyType::W,
                KeyType newAltUp = KeyType::Up,
                KeyType newDownCom = KeyType::S,
                KeyType newAltDown = KeyType::Down
            );
            Player_Fishy(const Player_Fishy&)             = default;
            Player_Fishy(Player_Fishy&&)                  = default;
            Player_Fishy& operator=(const Player_Fishy&)  = default;
            Player_Fishy& operator=(Player_Fishy&&)       = default;
            virtual ~Player_Fishy();

        protected:
/* Inherited from GUI::Fishy
            BoundType                   mBound;
            bool                        mFlipped;
            const Resource::Manager*    mResourcePtr;
*/
            /**
             *  \brief Update the size of the player fish using the
             *      mass of the target fish.
             *  
             *  \param [in] target Victim.
             */
            virtual void eat_concrete(const Data::Fishy& target) override;
            /**
             *  \brief Update the position of the player based
             *      on which key was pressed.
             */
            virtual void updateConcrete() override;

        private:
            KeyType
                mLeftCom, mAltLeft, mRightCom, mAltRight,
                mUpCom, mAltUp, mDownCom, mAltDown
            ;
    };
}

#endif
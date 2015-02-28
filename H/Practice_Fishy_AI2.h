#ifndef PRACTICEAIFISH_HEA333IDER200_
#define PRACTICEAIFISH_HEA333IDER200_

#include "Fishy_GUI.h"

namespace GUI{
    class Practice_Fishy2 : public Fishy {
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
            /**
             *  \brief Sole constructor.
             *  
             *  \param [in] newMass Starting mass of the fish.
             *  \param [in] newCode Fish type identifier.
             *  \param [in] newBound area that will represent the
             *      collision boundary of the fish.
             *  \param [in] newResource Resource manager that will
             *      provide the texture for drawing the fish.
             *  \param [in] newFrameRateLimit Find out the
             *      maximum framerate of the window to help timing.
             */
            Practice_Fishy2(
                mass_type newMass, code_type newCode,
                BoundType newBound,
                const Resource::Manager& newResource,
                unsigned newFrameRateLimit = 40u,
                double newFreq = 1.0
            );
            Practice_Fishy2(const Practice_Fishy2&)             = default;
            Practice_Fishy2(Practice_Fishy2&&)                  = default;
            Practice_Fishy2& operator=(const Practice_Fishy2&)  = default;
            Practice_Fishy2& operator=(Practice_Fishy2&&)       = default;
            virtual ~Practice_Fishy2();

        protected:
/* Inherited from GUI::Fishy
            BoundType                   mBound;
            bool                        mFlipped;
            const Resource::Manager*    mResourcePtr;
*/
            /**
             *  \brief Update the size of the fish using the
             *      mass of the target fish.
             *  
             *  \param [in] target Victim.
             */
            virtual void eat_concrete(const Data::Fishy& target) override;
            /**
             *  \brief Update the position of the fish.
             *  
             *  \details Moves the fish at a constant speed but random
             *      directions. The fish will move in a direction
             *      regardless of other fish in the way.
             */
            virtual void updateConcrete() override;

        private:
            unsigned mDecisionDelay, mFLim;
            double mTime, mFreq;
    };
}

#endif
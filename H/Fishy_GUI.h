/**
 *  \file Fishy_GUI.h
 *  \brief Contains the interface to all fish drawn to the GUI.
 */

#ifndef GUI_FISHY_HEADER_HH383888_
#define GUI_FISHY_HEADER_HH383888_

#include "Fishy.h"
#include "Manager_GUI.h"
#include "Collision_Detection.h"

#include <SFML/Graphics/Sprite.hpp>

namespace sf{
    class Texture;
}

namespace GUI{
    namespace Resource{
        typedef BasicManager<sf::Texture, Data::Fish::code> Manager;
    }

    namespace Collision{
        struct BoundEllipse;
    }

    class Fishy : public Data::Fishy, public sf::Sprite {
        public:
            using BoundType = Collision::BoundEllipse;
            /**
             *  \brief Get whether or not the sprite is flipped.
             *
             *  \return True if the sprite is flipped horizontally.
             */
            bool flipped()const;
            /**
             *  \brief Get the boundary shape that is used
             *      for collision detection.
             *
             *  \return An object of the boundary type.
             */
            const BoundType& bound()const;
            /**
             *  \brief Determine if this fish has collided
             *      with the other.
             *
             *  \param [in] target The fish to check
             *      a collision against.
             *  \return True if there is a collision.
             *
             *  \details Collision is determined by the boundary
             *      objects as returned by bound().
             */
            bool collided(const Fishy& target)const;

            /**
             *  \brief Update the model of the fish,
             *      including position.
             *
             *  \details Calls updateConcrete().
             */
            void update();
            /**
             *  \brief Set a new texture as well as set the
             *      new boundary of the sprite.
             *
             *  \param [in] texture A reference to the new
             *      texture to use.
             *  \param [in] newLength 1/2 length of the boundary
             *      along the x-axis.
             *  \param [in] newHeight 1/2 the height of the boundary
             *      along the y-axis.
             *  \param [in] newCenterX Center of the boundary with
             *      respect to the sprite along the x-axis.
             *  \param [in] newCenterY Center of the boundary with
             *      respect to the sprite along the y-axis.
             *  \param [in] resetRect Reset the rectangle area being
             *      used to mark a section of the texture.
             */
            void setTexture(
                const sf::Texture& texture,
                BoundType::pixel newLength,
                BoundType::pixel newHeight,
                BoundType::pixel newCenterX,
                BoundType::pixel newCenterY,
                bool resetRect = false
            );
            /**
             *  \brief Flip the sprite horizontally.
             */
            void flip();
            /**
             *  \brief Increase the mass and size of the fish.
             *
             *  \param [in] addMass Additional mass to increase
             *      the fish size by.
             *
             *  \details Does not allow shrinking.
             */
            void grow(mass_type addMass);

            /**
             *  \brief Sole constructor.
             *
             *  \param [in] newMass Starting mass of the fish.
             *  \param [in] newCode Unique identifier of the fish type.
             *  \param [in] newBound Boundary used for
             *      collision detecting.
             *  \param [in] newResource Resource manager the fish
             *      sprite will use.
             */
            Fishy(
                mass_type newMass, code_type newCode,
                BoundType newBound,
                const Resource::Manager& newResource
            );
            Fishy(const Fishy&)             = default;
            Fishy(Fishy&&)                  = default;
            Fishy& operator=(const Fishy&)  = default;
            Fishy& operator=(Fishy&&)       = default;
            virtual ~Fishy();
        protected:
/* Inherited from Data::Fishy
            virtual void eat_concrete(const Data::Fishy& target) = 0;
*/
            /**
             *  \brief Concrete function for the child classes to
             *      implement.
             *
             *  \details Update the model of the fish.
             */
            virtual void updateConcrete() = 0;

                // Relative to the number of pixels
                //  on the actual sprite. Length and
                //  height are for approximating the
                //  boundary of the fish using an
                //  ellipse (length ~ major, height
                //  ~ minor).
            BoundType                   mBound;
            bool                        mFlipped;
            const Resource::Manager*    mResourcePtr;
    };
}

#endif

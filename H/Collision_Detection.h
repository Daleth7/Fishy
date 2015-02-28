/**
 *  \file Collision_Detection.h
 *  \brief Contains an interface to collision detection algorithms.
 */

#ifndef COLLISION_DETE11C000TION383883_HEADEHHHR_
#define COLLISION_DETE11C000TION383883_HEADEHHHR_

namespace sf{
    class Sprite;
    class Transform;
}

namespace GUI{
    namespace Collision{
        struct BoundEllipse {
            typedef double pixel;
            pixel radiusX, radiusY;
                // Center is with respect to the top left corner of the sprite
            pixel centerX, centerY;

            /**
             *  \brief Determine if this boundary contains
             *      a pixel at the specified global coordinate.
             *  
             *  \param [in] x Pixel coordinate along the x-axis.
             *  \param [in] y Pixel coordinate along the y-axis.
             *  \return True if the boundary does include the pixel.
             */
            bool contains(pixel x, pixel y)const;
        };

        /**
         *  \brief Translate the boundary according to
         *      the specified transform.
         *  
         *  \return The new, translated boundary.
         *  
         *  \details Does not rotate the boundary.
         */
        BoundEllipse transform(const BoundEllipse&, const sf::Transform&);

        /**
         *  \brief Check if two sprites have collided based on the
         *      boundary.
         *  
         *  \param [in] s1 Sprite 1
         *  \param [in] s2 Sprite 2
         *  \param [in] b1 Boundary belonging to sprite 1
         *  \param [in] b2 Boundary belonging to sprite 2
         *  \return True if a collision has occurred.
         *  
         *  \details Does not account for rotation.
         */
        bool check(
            const sf::Sprite& s1, const sf::Sprite& s2,
            const BoundEllipse& b1, const BoundEllipse& b2
        );
    }
}

#endif
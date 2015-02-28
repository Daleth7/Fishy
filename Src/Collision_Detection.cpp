#include "Collision_Detection.h"

#include "Constants.h"

#include "SFML/Graphics/Sprite.hpp"

#include <cmath>

namespace GUI{
    namespace Collision{
        bool BoundEllipse::contains(pixel x, pixel y)const{
            // Perimeter equation of an ellipse: (x/a)^2 + (y/b)^2 = 1
            const pixel
                xTerm = (x-centerX)*(x-centerX)/radiusX/radiusX,
                yTerm = (y-centerY)*(y-centerY)/radiusY/radiusY
            ;
            return (1.0 + 1e-7) > (xTerm + yTerm);
        }

        BoundEllipse transform(
            const BoundEllipse& oldBound,
            const sf::Transform& settings
        ){
            BoundEllipse toreturn(oldBound);
            const sf::Vector2f newCenter(settings.transformPoint
                (oldBound.centerX, oldBound.centerY));
            toreturn.centerX = newCenter.x;
            toreturn.centerY = newCenter.y;
            return toreturn;
        }

        void findMidpoint(
            BoundEllipse::pixel x1,
            BoundEllipse::pixel y1,
            BoundEllipse::pixel x2,
            BoundEllipse::pixel y2,
            BoundEllipse::pixel& outX,
            BoundEllipse::pixel& outY
        ){
            outX = (x2 + x1)/2.0;
            outY = (y2 + y1)/2.0;
        }

            // So far, does not account for rotation
        bool check(
            const sf::Sprite& s1, const sf::Sprite& s2,
            const BoundEllipse& b1, const BoundEllipse& b2
        ){
            if(!s1.getGlobalBounds().intersects(s2.getGlobalBounds()))
                return false;
            const sf::Transform&
                t1(s1.getTransform()),
                t2(s2.getTransform())
            ;
                // Calculate the actual coordinates of the
                //  center of the boundaries
            const BoundEllipse
                relB1(transform(b1, t1)),
                relB2(transform(b2, t2))
            ;
                // Now find the midpoint
            BoundEllipse::pixel midX, midY;
                findMidpoint(
                    relB1.centerX, relB1.centerY,
                    relB2.centerX, relB2.centerY,
                    midX, midY
                );
                // Finally, see if both ellipses contain that midpoint
            return
                relB1.contains(midX, midY) &&
                relB2.contains(midX, midY)
            ;
        }
    }
}

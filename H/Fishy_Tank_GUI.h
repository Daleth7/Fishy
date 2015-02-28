/**
 *  \file Fishy_Tank_GUI.h
 *  \brief Contains an interface to the fish tank in the GUI.
 */

#ifndef TANKHEADER_FOR_FISHY_GAME_HHHH_3829832_H
#define TANKHEADER_FOR_FISHY_GAME_HHHH_3829832_H

#include "Fishy_GUI.h"

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include <unordered_map>
#include <memory>
#include <functional>
#include <cstddef>

namespace std{
    template <>
    struct hash<Data::Fish::code>{
        typedef Data::Fish::raw_type    result_type;
        typedef Data::Fish::code        argument_type;

        result_type operator() (const argument_type& arg)const
            {return static_cast<result_type>(arg);}
    };
}

namespace GUI{
    class Tank : public sf::Drawable {
        public:
                // Using shared since unique is move-only
            using fishPtr   = std::shared_ptr<Fishy>;
            using fishCode  = Data::Fish::code;
            using fishTank  = std::unordered_multimap<fishCode, fishPtr>;
            using bgType    = sf::RectangleShape;
            /**
             *  \brief Get a reference to the raw container if the
             *      user needs to access specific information
             *      about the container.
             *  
             *  \return A reference to the underlying container.
             *  
             *  \details The underlying container is of type
             *      std::unordered_multimap<fishCode, fishPtr>.
             *      fishPtr is of type std::shared_ptr<Fishy>.
             */
            const fishTank& rawTank()const;
            /**
             *  \brief Return the population of fish currently in the tank.
             */
            fishTank::size_type population()const;
            /**
             *  \brief Access the resource manager the tank is using.
             *  
             *  \return A reference to the resource manager.
             */
            const Resource::Manager& getResource()const;
            /**
             *  \brief Create new fish and add them to the tank.
             *  
             *  \param [in] fish The new fish type to create.
             *  \param [in] newMass Starting mass of the fish type.
             *  \param [in] pop The number of fish to create.
             *  
             *  \details This function takes advantage of Fishy_Factory.
             */
            void breed(
                fishCode fish, Fishy::mass_type newMass,
                unsigned pop = 1u
            );
            /**
             *  \brief Add an existing fish to the tank.
             *  
             *  \param [in] newFish The new fish to add to the tank.
             *  
             *  \details Although fishPtr is of type std::shared_ptr,
             *      instantiations of this class will not check if
             *      the pointer is valid. Assume that the Tank object
             *      will take ownership of the pointer.
             */
            void addFish(const fishPtr& newFish);
            /**
             *  \brief Update all the fish within the tank.
             * 
             *  \details Calls the update() function of all the
             *      fish within the tank. If any of the fish goes
             *      beyond the acceptable boundary of the tank, they
             *      will be placed on the opposite side of the tank.
             */
            virtual void update();
            /**
             *  \brief Set a new resource manager for the tank to use.
             *  
             *  \param [in] newRsrc A reference to the resource manager
             *      to use.
             */
            void setResource(const Resource::Manager& newRsrc);

            using iterator = fishTank::iterator;
            using constIterator = fishTank::const_iterator;

            /**
             *  \brief Get a constant iterator from the underlying
             *      iterator.
             *  
             *  \return A const_iterator for the first element of the
             *      container.
             */
            constIterator cbegin()const;
            /**
             *  \brief Get a constant iterator from the underlying
             *      iterator.
             *  
             *  \return A const_iterator for the last element of the
             *      container.
             */
            constIterator cend()const;
            /**
             *  \brief Get a constant iterator from the underlying
             *      iterator.
             *  
             *  \return A const_iterator for the first element of the
             *      container.
             */
            constIterator begin()const;
            /**
             *  \brief Get a constant iterator from the underlying
             *      iterator.
             *  
             *  \return A const_iterator for the end element of the
             *      container.
             */
            constIterator end()const;

            /**
             *  \brief Get an iterator from the underlying
             *      iterator.
             *  
             *  \return An iterator for the first element of the
             *      container.
             */
            iterator begin();
            /**
             *  \brief Get an iterator from the underlying
             *      iterator.
             *  
             *  \return An iterator for the last element of the
             *      container.
             */
            iterator end();
            /**
             *  \brief Remove a fish from the tank via an iterator.
             *  
             *  \param [in] iterator The target fish to remove.
             */
            void remove(iterator);
            /**
             *  \brief Set the width and height of the
             *      visible tank area.
             *  
             *  \param [in] newSize The new size of the visible
             *      tank area.
             *  
             *  \details The "size" of the tank only dictates how
             *      much of the tank will be visible to the screen.
             *      There is no size to the actual tank.
             *      
             */
            void setSize(const sf::Vector2f& newSize);
            /**
             *  \brief Get the width and height of the visible
             *      tank area.
             *  
             *  \return The width and height of the tank.
             */
            const sf::Vector2f& getSize()const;
            /**
             *  \brief Set the background of the
             *      tank to a new texture.
             *  
             *  \param [in] newTexture A reference to the new texture
             *      to set the background to.
             */
            void setTexture(const sf::Texture& newTexture);
            /**
             *  \brief Set a new fill colour for the background.
             *  
             *  \param [in] newColor The new colour to set the
             *      background to.
             */
            void setFillColor(const sf::Color& newColor);
            /**
             *  \brief Remove all fish from the tank.
             */
            void clear();

            Tank()                          = default;
            Tank(const Tank&)               = default;
            Tank(Tank&&)                    = default;
            Tank& operator=(const Tank&)    = default;
            Tank& operator=(Tank&&)         = default;
            virtual ~Tank(){}

        private:
            /**
             *  \brief Draw the tank and the fish inside to the
             *      render target.
             *  
             *  \param [in] target The render target to draw to.
             *  \param [in] states Render states to configure
             *      how the tank is drawn to the target.
             */
            virtual void draw(
                sf::RenderTarget& target,
                sf::RenderStates states
                )const override;

            fishTank                    mTank;
            const Resource::Manager*    mRsrcPtr;
            bgType                      mBg;
    };
}

#endif
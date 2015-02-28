/**
 *  \file Fish_Texture_Manager_GUI.h
 *  \brief Contains the specific resource manager for managing
 *      fish sprites.
 */

#ifndef TILEMANAGER_GUI_FOR_BASIC_TILE_SPRITE_TEXURES_HHHH_HHH_H_HH_
#define TILEMANAGER_GUI_FOR_BASIC_TILE_SPRITE_TEXURES_HHHH_HHH_H_HH_

#include "Manager_GUI.h"
#include "Tile_Constants.h"

#include "Fish_Codes.h"

#include <SFML/Graphics/Texture.hpp>

namespace GUI{
    class FishTextureManager
        : public Resource::BasicManager<sf::Texture, Data::Fish::code>
    {
        using BasicType = Resource::BasicManager<sf::Texture, Data::Fish::code>;
        public:
            using BasicType::TextureType;
            using BasicType::CodeType;

/* Inherited from GUI::Resource::BasicManager<sf::Texture, Data::Fish::code>
            const TextureType& getSheet()const;
            const TextureType* getSheetPtr()const;
            sf::IntRect getArea(CodeType code)const;
            sf::IntRect getFlippedArea(CodeType code, bool hor, bool ver)const;
            bool loadFromFile(
                const std::string& filePath,
                const sf::IntRect& rect = sf::IntRect()
            );
            bool loadFromMemory(
                const void* rawData, std::size_t size,
                const sf::IntRect& rect = sf::IntRect()
            );
            bool loadFromStream(
                InputStream& streamIn,
                const sf::IntRect& rect = sf::IntRect()
            );
            bool loadFromImage(
                const sf::Image& img,
                const sf::IntRect& rect = sf::IntRect()
            );
            sf::Vector2u getSize()const;
            sf::Image copyToImage()const;
            void setSmooth(bool smoothTrue);
            bool isSmooth()const;
            void flipArea(sf::IntRect& orig, bool hor, bool ver)const;
*/
            /**
             *  \brief Returns a shift value required when
             *      flipping the image horizontally.
             *
             *  \param [in] fish Determines what the shift value
             *      should be based on the fish sprite.
             *  \param [in] flipToLeft Determines if shift value
             *      should be to the left or to the right.
             *  \return The value to shift horizontally by.
             */
            static double flipFactor(Data::Fish::code fish, bool flipToLeft);

            FishTextureManager()                                        = default;
            FishTextureManager(const FishTextureManager&)               = default;
            FishTextureManager(FishTextureManager&&)                    = default;
            FishTextureManager& operator=(const FishTextureManager&)    = default;
            FishTextureManager& operator=(FishTextureManager&&)         = default;
            virtual ~FishTextureManager(){}

        private:
            /**
             *  \brief Get the sprite / texture sheet the manager
             *      contains.
             *
             *  \return A reference to the texture sheet.
             */
            virtual const TextureType& getSheetConcrete()const override;
            /**
             *  \brief The same as getSheet().
             *
             *  \return A pointer to the texture sheet.
             */
            virtual const TextureType* getSheetPtrConcrete()const override;
            /**
             *  \brief Get a rectangular area that corresponds
             *      to the texture sheet. This area will refer
             *      to a specific "sprite" image.
             *
             *  \param [in] code Code that determines which area
             *      on the texture sheet to return.
             *  \return The rectangular area of the image on the
             *      texture sheet.
             */
            virtual sf::IntRect getAreaConcrete(CodeType code)const override;
            /**
             *  \brief Load the texture sheet from a file.
             *
             *  \param [in] filePath The location of the image file
             *      that contains the texture sheet.
             *  \param [in] rect Optionally load only a specific
             *      section of the texture sheet.
             *  \return An indication of whether or not the
             *      texture sheet was loaded successfully.
             *
             *  \details The file types supported are dependent on
             *      the child classes.
             */
            virtual bool loadFromFileConcrete(
                const std::string& filePath,
                const sf::IntRect& rect = sf::IntRect()
            ) override;
            /**
             *  \brief Load the texture sheet from memory via
             *      a pointer.
             *
             *  \param [in] rawData A pointer to the data in
             *      memory to load the sheet from.
             *  \param [in] size The number of bytes the data is.
             *  \param [in] rect Optionally load only a specific
             *      section of the texture sheet.
             *  \return An indication of whether or not the
             *      texture sheet was loaded successfully.
             */
            virtual bool loadFromMemoryConcrete(
                const void* rawData, std::size_t size,
                const sf::IntRect& rect
            ) override;
            /**
             *  \brief Load the texture sheet from an input
             *      stream.
             *
             *  \param [in] streamIn The input stream from which
             *      to request the texture sheet from.
             *  \param [in] rect Optionally load only a specific
             *      section of the texture sheet.
             *  \return An indication of whether or not the
             *      texture sheet was loaded successfully.
             *
             *  \details How the stream will be manipulated is
             *      dependent on the child classes.
             */
            virtual bool loadFromStreamConcrete(
                sf::InputStream& streamIn,
                const sf::IntRect& rect
            ) override;
            /**
             *  \brief Load the texture sheet from an Image object.
             *
             *  \param [in] img The object to "convert" to a
             *      texture sheet.
             *  \param [in] rect Optionally load only a specific
             *      section of the texture sheet.
             *  \return An indication of whether or not the
             *      texture sheet was loaded successfully.
             *
             *  \details Note that going from Texture to Image and vice
             *      versa will be slow due to copying and that one
             *      object exists in the GPU while the other in RAM.
             */
            virtual bool loadFromImageConcrete(
                const sf::Image& img,
                const sf::IntRect& rect
            ) override;
            /**
             *  \brief Get the size of the sheet being used.
             *
             *  \return A width by height measurement of the sheet.
             */
            virtual sf::Vector2u getSizeConcrete()const override;
            /**
             *  \brief "Convert" the texture sheet to an image
             *      object.
             *
             *  \return An object of type Image.
             *
             *  \details Note that going from Texture to Image
             *      and vice versa will be slow due to copying
             *      and that one object exists in the GPU while
             *      the other in RAM.
             */
            virtual sf::Image copyToImageConcrete()const override;
            /**
             *  \brief Set the texture sheet to be smoothed, i.e.
             *      blending colours to avoid a pixelated look.
             *
             *  \param [in] smoothTrue Turn on or off the smoothing
             *      function.
             */
            virtual void setSmoothConcrete(bool smoothTrue) override;
            /**
             *  \brief Get whether or not the texture has been
             *      set to be smoothed.
             *
             *  \return True if the texture is set to be smoothed
             *      and false otherwise.
             */
            virtual bool isSmoothConcrete()const override;

        private:
            TextureType mTex;
    };
}

#endif

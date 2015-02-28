/**
 *  \file Manager_GUI.h
 *  \brief Contains the interface to a resource manager for
 *      GUI applications.
 */

#ifndef MANAAGER_INTERFACE_FOR_GUI_RESOURCES_HHHHHH_HHHH_H_H_
#define MANAAGER_INTERFACE_FOR_GUI_RESOURCES_HHHHHH_HHHH_H_H_

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Image.hpp>

#include <cstddef>

namespace std{
    template <typename>
    class char_traits;

    template <typename>
    class allocator;

    template <typename, typename, typename>
    class basic_string;

    typedef basic_string<char, char_traits<char>, allocator<char> > string;
}

namespace sf{
    class InputStream;

    template <typename>
    class Vector2;

    class Image;

    typedef Vector2<unsigned int> Vector2u;
}

namespace GUI{
    namespace Resource{
        template <typename TextureTypeParam, typename CodeTypeParam>
        class BasicManager{
            public:
                using TextureType   = TextureTypeParam;
                using CodeType      = CodeTypeParam;
                /**
                 *  \brief Get the sprite / texture sheet the manager
                 *      contains.
                 *  
                 *  \return A reference to the texture sheet.
                 */
                const TextureType& getSheet()const
                    {return this->getSheetConcrete();}
                /**
                 *  \brief The same as getSheet().
                 *  
                 *  \return A pointer to the texture sheet.
                 */
                const TextureType* getSheetPtr()const
                    {return this->getSheetPtrConcrete();}
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
                sf::IntRect getArea(CodeType code)const
                    {return this->getAreaConcrete(code);}
                /**
                 *  \brief Like getArea(CodeType) except returns
                 *      the area flipped either vertically or
                 *      horizontally.
                 *  
                 *  \param [in] code Code that determines which area
                 *      on the texture sheet to return.
                 *  \param [in] hor Get the area flipped horizontally.
                 *  \param [in] ver Get the area flipped vertically.
                 *  \return The rectangular area of the image on the
                 *      texture sheet.
                 */
                sf::IntRect getFlippedArea(CodeType code, bool hor, bool ver)const
                    {return this->getFlippedAreaConcrete(code, hor, ver);}
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
                bool loadFromFile(
                    const std::string& filePath,
                    const sf::IntRect& rect = sf::IntRect()
                ){return this->loadFromFileConcrete(filePath, rect);}
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
                bool loadFromMemory(
                    const void* rawData, std::size_t size,
                    const sf::IntRect& rect = sf::IntRect()
                ){return this->loadFromMemoryConcrete(rawData, rect);}
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
                bool loadFromStream(
                    sf::InputStream& streamIn,
                    const sf::IntRect& rect = sf::IntRect()
                ){return this->loadFromFileConcrete(streamIn, rect);}
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
                 *  \details Note that going from Texture to Image
                 *      and vice versa will be slow due to copying
                 *      and that one object exists in the GPU while
                 *      the other in RAM.
                 */
                bool loadFromImage(
                    const sf::Image& img,
                    const sf::IntRect& rect = sf::IntRect()
                ){return this->loadFromImageConcrete(img, rect);}
                /**
                 *  \brief Get the size of the sheet being used.
                 *  
                 *  \return A width by height measurement of the sheet.
                 */
                sf::Vector2u getSize()const
                    {return this->getSizeConcrete();}
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
                sf::Image copyToImage()const
                    {return this->copyToImageConcrete();}
                /**
                 *  \brief Set the texture sheet to be smoothed, i.e.
                 *      blending colours to avoid a pixelated look.
                 *  
                 *  \param [in] smoothTrue Turn on or off the smoothing
                 *      function.
                 */
                void setSmooth(bool smoothTrue)
                    {this->setSmoothConcrete(smoothTrue);}
                /**
                 *  \brief Get whether or not the texture has been
                 *      set to be smoothed.
                 *  
                 *  \return True if the texture is set to be smoothed
                 *      and false otherwise.
                 */
                bool isSmooth()const
                    {return this->isSmoothConcrete();}
                /**
                 *  \brief Take an existing area and flip it either
                 *      vertically or horizontally.
                 *  
                 *  \param [in] orig A reference to the are to flip.
                 *  \param [in] hor Flip the area horizontally.
                 *  \param [in] ver Flip the area vertically.
                 */
                void flipArea(sf::IntRect& orig, bool hor, bool ver)const
                    {this->flipAreaConcrete(orig, hor, ver);}

                virtual ~BasicManager(){}

            private:
                /**
                 *  \brief Get the sprite / texture sheet the manager
                 *      contains.
                 *  
                 *  \return A reference to the texture sheet.
                 */
                virtual const TextureType& getSheetConcrete()const = 0;
                /**
                 *  \brief The same as getSheet().
                 *  
                 *  \return A pointer to the texture sheet.
                 */
                virtual const TextureType* getSheetPtrConcrete()const = 0;
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
                virtual sf::IntRect getAreaConcrete(CodeType code)const = 0;
                /**
                 *  \brief Like getArea(CodeType) except returns
                 *      the area flipped either vertically or
                 *      horizontally.
                 *  
                 *  \param [in] code Code that determines which area
                 *      on the texture sheet to return.
                 *  \param [in] hor Get the area flipped horizontally.
                 *  \param [in] ver Get the area flipped vertically.
                 *  \return The rectangular area of the image on the
                 *      texture sheet.
                 */
                virtual sf::IntRect getFlippedAreaConcrete(
                    CodeType code, bool hor, bool ver
                )const{
                    sf::IntRect toreturn = this->getAreaConcrete(code);
                    this->flipAreaConcrete(toreturn, hor, ver);
                    return toreturn;
                }
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
                ) = 0;
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
                ) = 0;
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
                ) = 0;
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
                 *  \details Note that going from Texture to Image
                 *      and vice versa will be slow due to copying
                 *      and that one object exists in the GPU while
                 *      the other in RAM.
                 */
                virtual bool loadFromImageConcrete(
                    const sf::Image& img,
                    const sf::IntRect& rect
                ) = 0;
                /**
                 *  \brief Get the size of the sheet being used.
                 *  
                 *  \return A width by height measurement of the sheet.
                 */
                virtual sf::Vector2u getSizeConcrete()const = 0;
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
                virtual sf::Image copyToImageConcrete()const = 0;
                /**
                 *  \brief Set the texture sheet to be smoothed, i.e.
                 *      blending colours to avoid a pixelated look.
                 *  
                 *  \param [in] smoothTrue Turn on or off the smoothing
                 *      function.
                 */
                virtual void setSmoothConcrete(bool smoothTrue) = 0;
                /**
                 *  \brief Get whether or not the texture has been
                 *      set to be smoothed.
                 *  
                 *  \return True if the texture is set to be smoothed
                 *      and false otherwise.
                 */
                virtual bool isSmoothConcrete()const = 0;
                /**
                 *  \brief Take an existing area and flip it either
                 *      vertically or horizontally.
                 *  
                 *  \param [in] orig A reference to the are to flip.
                 *  \param [in] hor Flip the area horizontally.
                 *  \param [in] ver Flip the area vertically.
                 */
                virtual void flipAreaConcrete(
                    sf::IntRect& orig,
                    bool hor, bool ver
                )const{
                    orig.left += hor*orig.width;
                    orig.width *= static_cast<int>(!hor)*2-1;
                    orig.top += ver*orig.height;
                    orig.height *= static_cast<int>(!ver)*2-1;
                }
        };
    }
}

#endif
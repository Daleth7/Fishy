#include "Fish_Texture_Manager_GUI.h"

namespace GUI{
    double FishTextureManager::flipFactor(
        Data::Fish::code fish,
        bool flipToLeft
    ){
        const double f = (flipToLeft*2.0)-1.0;
        typedef Data::Fish::code FishCode;
        switch(fish){
            case FishCode::Missingno:       return 23.5*f;
            case FishCode::Small_Feeder:
            case FishCode::Medium_Feeder:
            case FishCode::Large_Feeder:    return 11.5*f;
            default:                        return 0.0;
        }
    }

    auto FishTextureManager::getSheetConcrete()const -> const TextureType&
        {return mTex;}

    auto FishTextureManager::getSheetPtrConcrete()const -> const TextureType*
        {return &mTex;}

    sf::IntRect FishTextureManager::getAreaConcrete(CodeType code)const{
        const Data::Fish::raw_type raw
            (static_cast<Data::Fish::raw_type>(code));
        using namespace Constant;
        switch(code){
            case Data::Fish::code::Button:
                return sf::IntRect{21, 1137, 151, 55};
            case Data::Fish::code::ButtonPressed:
                return sf::IntRect{210, 1137, 151, 55};
            case Data::Fish::code::ReturnButton:
                return sf::IntRect{66, 1090, 49, 41};
            case Data::Fish::code::ReturnButtonPressed:
                return sf::IntRect{126, 1090, 49, 41};
            default:
                return sf::IntRect{
                    static_cast<int>(imgWidth*(raw%spriteCount)),
                    static_cast<int>(imgHeight*(raw/spriteCount)),
                    imgWidth, imgHeight};
        }
    }

    bool FishTextureManager::loadFromFileConcrete(
        const std::string& filePath,
        const sf::IntRect& rect
    ){return mTex.loadFromFile(filePath, rect);}

    bool FishTextureManager::loadFromMemoryConcrete(
        const void* rawData, std::size_t size,
        const sf::IntRect& rect
    ){return mTex.loadFromMemory(rawData, size, rect);}

    bool FishTextureManager::loadFromStreamConcrete(
        sf::InputStream& streamIn,
        const sf::IntRect& rect
    ){return mTex.loadFromStream(streamIn, rect);}

    bool FishTextureManager::loadFromImageConcrete(
        const sf::Image& img,
        const sf::IntRect& rect
    ){return mTex.loadFromImage(img, rect);}

    sf::Vector2u FishTextureManager::getSizeConcrete()const
        {return mTex.getSize();}

    sf::Image FishTextureManager::copyToImageConcrete()const
        {return mTex.copyToImage();}

    void FishTextureManager::setSmoothConcrete(bool smoothTrue)
        {mTex.setSmooth(smoothTrue);}

    bool FishTextureManager::isSmoothConcrete()const
        {return mTex.isSmooth();}
}
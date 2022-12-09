#pragma once

// SDL
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include <array>
#include <chrono>

#include <sgraphics/engine/polygon.h>
#include <sgraphics/convertion/convertion.h>
#include <sgraphics/geometry/olc.h>

namespace sg {

namespace engine {

template<class SpriteImpl>
struct ISprite
{
    using renderer_type = SDL_Renderer*;

protected:

    typedef std::chrono::nanoseconds duration;
    typedef std::chrono::time_point<std::chrono::system_clock, duration> time_point;

public:

    ISprite(ISprite&&) = default;
    ISprite& operator =(ISprite&&) = default;
    ISprite(const ISprite&) = delete;
    ISprite& operator =(const ISprite&) = delete;

    //!
    //! \brief ISprite
    //!
    ISprite(const std::string& path,  const std::array<uint8_t, 3>& rbg) {

        if(polygonPtr == nullptr){

            std::string err("Unable to get polygon pointer");
            throw std::runtime_error(err);
        }

        img_ = IMG_Load(path.c_str());
        if (img_ == nullptr) {

            std::string err("Unable to load background");
            throw std::runtime_error(err);
        }

        auto renderer = polygonPtr->getRenderer();
        if(renderer == nullptr){

            std::string err("Unable to get polygon renderer");
            throw std::runtime_error(err);
        }

        texture_ = SDL_CreateTextureFromSurface(renderer, img_);
        if(texture_ == nullptr){

            throw std::runtime_error("Unable to load background image");
        }
    }

    //!
    //! \brief ISprite
    //!
    ~ISprite() {

        SDL_DestroyTexture(texture_);
        SDL_FreeSurface(img_);
    }

    //!
    //! \brief renderCopy
    //! \param src
    //! \param dest
    //!
    void renderCopy(const olc::aabb::rect<float>& src, const olc::aabb::rect<float>& dest){

        if(polygonPtr == nullptr)
            return;

        auto renderer = polygonPtr->getRenderer();
        if(renderer == nullptr)
            return;

        SDL_FRect destSdl = convertion::convert(dest);
        SDL_FRect srcFSdl = convertion::convert(src);

        SDL_Rect srcSdl { (int)srcFSdl.x, (int)srcFSdl.y, (int)srcFSdl.w, (int)srcFSdl.h};


        SDL_RenderCopyF(renderer, texture_, &srcSdl, &destSdl);
    }

    //!
    //! \brief renderCopy
    //! \param src
    //! \param dest
    //!
    void renderCopy(const olc::aabb::rect<int32_t>& src, const olc::aabb::rect<int32_t>& dest){

        if(polygonPtr == nullptr)
            return;

        auto renderer = polygonPtr->getRenderer();
        if(renderer == nullptr)
            return;

        SDL_Rect destSdl = convertion::convert(dest);
        SDL_Rect srcFSdl = convertion::convert(src);

        SDL_Rect srcSdl { (int)srcFSdl.x, (int)srcFSdl.y, (int)srcFSdl.w, (int)srcFSdl.h};

        SDL_RenderCopy(renderer, texture_, &srcSdl, &destSdl);
    }

private:

    SpriteImpl* impl(){
        return static_cast<SpriteImpl*>(this);
    }

private:

    SDL_Surface* img_;
    SDL_Texture* texture_;
};

}}

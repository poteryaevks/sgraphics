#pragma once

// SDL
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <memory>
#include <chrono>
#include <string>
#include <stdexcept>

#include <alm/misc/singleton.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

#include <sgraphics/geometry/olc.h>
#include <sgraphics/engine/ipolygon.h>


namespace sg {

namespace engine {

extern IPolygon* polygonPtr;

//!
//! \brief The ZGame class
//!
template <class GameImpl>
class Polygon final
        : public IPolygon,
        public alm::misc::Singleton<Polygon<GameImpl>>
{
    friend class alm::misc::Singleton<Polygon>;
    using game_ptr_type = std::shared_ptr<GameImpl>;
private:

    //!
    //! \brief Game
    //!
    Polygon()
        : game_(std::make_shared<GameImpl>()),
          window_(nullptr),
          renderer_(nullptr),
          quit_(false)
    {}

    //!
    ~Polygon(){

        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);

        IMG_Quit();
        SDL_Quit();
    }

public:

    //!
    //! \brief ZGame
    //! \param width
    //! \param height
    //!
    void init(int width = 800, int hight = 640){

        polygonPtr = this;

        width_ = width;
        hight_ = hight;

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::string err("Unable to init SDL, error: ");
            err += std::string(SDL_GetError());
            throw std::runtime_error(err);
        }

        if (IMG_Init(IMG_INIT_PNG) == 0)
        {
            std::string err("Unable to init Img");
            throw std::runtime_error(err);
        }

        window_ = SDL_CreateWindow("SDL2 Sprite Sheets",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   width, hight, 0);

        if(window_ == nullptr) {

            std::string err("Unable to create window");
            throw std::runtime_error(err);
        }

        renderer_ = SDL_CreateRenderer(window_, -1, 0);
        if(renderer_ == nullptr) {

            std::string err("Unable to create renderer");
            throw std::runtime_error(err);
        }

        game_->initImpl();
    }

    //!
    //! \brief run
    //!
    void run(){

        auto tp1 = std::chrono::system_clock::now();
        auto tp2 = std::chrono::system_clock::now();

        // main loop
        while(!quit_)
        {
            tp2 = std::chrono::system_clock::now();
            std::chrono::duration<float> elapsedTime = tp2 - tp1;
            tp1 = tp2;
            float fElapsedTime = elapsedTime.count();

            SDL_PollEvent(&event_);
            getEvents();

            SDL_RenderClear(renderer_);

            game_->updateImpl(
                        fElapsedTime
                        );

            SDL_RenderPresent(renderer_);
        }

        game_->quitImpl();  // free all used resources
    }

public:


    virtual SDL_Renderer* getRenderer() noexcept override {

        return renderer_;
    }

    virtual int getHeight() noexcept override{

        return hight_;
    }

    virtual int getWidth() noexcept override{

        return width_;
    }

    virtual std::vector<SDL_Rect> getRects() noexcept override{

        return std::vector<SDL_Rect>();
    }

    virtual const SDL_Event& getEvent() noexcept override{

        return event_;
    }

private:

    //!
    //! \brief getEvents
    //! \param event
    //!
    void getEvents(){

        switch (event_.type)
        {

        case SDL_QUIT:
            quit_ = true;
            break;

        default:
            break;
        }
    }

private:


    game_ptr_type game_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    int width_;
    int hight_;
    SDL_Event event_;
    bool quit_;
};


}}



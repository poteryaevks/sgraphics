#include <sgraphics/engine/polygon_funcs.h>


// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

namespace {

void set_pixel(SDL_Renderer* rend, const olc::vf2d& point, const std::array<uint8_t, 4>& rbg)
{
    SDL_SetRenderDrawColor(rend, rbg[0], rbg[1], rbg[2], rbg[3]);
    SDL_RenderDrawPoint(rend, point.x, point.y);
}

void draw_circle(SDL_Renderer *surface, const olc::vi2d& point, std::int32_t radius, const std::array<uint8_t, 4>& rgb)
{
    // if the first pixel in the screen is represented by (0,0) (which is in sdl)
    // remember that the beginning of the circle is not in the middle of the pixel
    // but to the left-top from it:
    double error = (double)-radius;
    double x = (double)radius - 0.5;
    double y = (double)0.5;
    double cx = point.x - 0.5;
    double cy = point.y - 0.5;

    while (x >= y)
    {
        set_pixel(surface, {(int)(cx + x), (int)(cy + y)}, rgb);
        set_pixel(surface, {(int)(cx + y), (int)(cy + x)}, rgb);

        if (x != 0)
        {
            set_pixel(surface, {(int)(cx - x), (int)(cy + y)}, rgb);
            set_pixel(surface, {(int)(cx + y), (int)(cy - x)}, rgb);
        }

        if (y != 0)
        {
            set_pixel(surface, {(int)(cx + x), (int)(cy - y)}, rgb);
            set_pixel(surface, {(int)(cx - y), (int)(cy + x)}, rgb);
        }

        if (x != 0 && y != 0)
        {
            set_pixel(surface, {(int)(cx - x), (int)(cy - y)}, rgb);
            set_pixel(surface, {(int)(cx - y), (int)(cy - x)}, rgb);
        }

        error += y;
        ++y;
        error += y;

        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}

void fill_circle(SDL_Renderer *gRenderer, const olc::vi2d& point, int radius, const std::array<uint8_t, 4>& rgb)
{

    for (double dy = 1; dy <= radius; dy += 1.0)
    {
        double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
        SDL_SetRenderDrawColor(gRenderer, rgb[0], rgb[1], rgb[2], rgb[3]);
        SDL_RenderDrawLine(gRenderer, point.x - dx, point.y + dy - radius, point.x + dx, point.y + dy - radius);
        SDL_RenderDrawLine(gRenderer, point.x - dx, point.y - dy + radius, point.x + dx, point.y - dy + radius);
    }
}

}


namespace sg {

namespace engine {

const SDL_Event DUMP_EVENT = SDL_Event();


void drawRect(const olc::aabb::rect<float>& rect,
              const std::array<uint8_t, 4>& rbg,
              bool fill)
{
    if(polygonPtr == nullptr)
        return;

    auto renderer = polygonPtr->getRenderer();
    if(renderer == nullptr)
        return;

    auto sdlRect = convertion::convert(rect);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, rbg[0], rbg[1], rbg[2], rbg[3]);

    fill ? SDL_RenderFillRectF(renderer, &sdlRect)
         : SDL_RenderDrawRectF(renderer, &sdlRect);
}

void drawRect(const olc::aabb::rect<std::int32_t>& rect,
              const std::array<uint8_t, 4>& rbg,
              bool fill )
{
    if(polygonPtr == nullptr)
        return;

    auto renderer = polygonPtr->getRenderer();
    if(renderer == nullptr)
        return;

    auto sdlRect = convertion::convert(rect);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, rbg[0], rbg[1], rbg[2], rbg[3]);

    fill ? SDL_RenderFillRect(renderer, &sdlRect)
         : SDL_RenderDrawRect(renderer, &sdlRect);
}


void drawLine(const olc::vf2d& point1,
              const olc::vf2d& point2,
              const std::array<uint8_t, 4>& rbg)
{
    if(polygonPtr == nullptr)
        return;

    auto renderer = polygonPtr->getRenderer();
    if(renderer == nullptr)
        return;

    auto sdlPoint1 = convertion::convert(point1);
    auto sdlPoint2 = convertion::convert(point2);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, rbg[0], rbg[1], rbg[2], rbg[3]);
    SDL_RenderDrawLine(renderer, sdlPoint1.x, sdlPoint1.y, sdlPoint2.x, sdlPoint2.y);
}


std::pair<int, int> getMousePosition()
{
    std::pair<int, int> xy;
    SDL_GetMouseState(&(xy.first), &(xy.second));
    return xy;
}

void clearScreen(std::array<uint8_t, 4> rgb)
{
    if(polygonPtr == nullptr)
        return;

    auto renderer = polygonPtr->getRenderer();
    if(renderer == nullptr)
        return;

    SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], rgb[3]);
    SDL_RenderClear(renderer);
}

bool mousePressed()
{
    if(polygonPtr == nullptr)
        return false;

    const auto& event = polygonPtr->getEvent();

    switch (event.type){

    case SDL_MOUSEBUTTONDOWN:
    {
        switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            return true;
            break;
        default:
            break;
        }
    }

    case SDL_MOUSEMOTION:
    {
        switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            return true;
            break;
        default:
            break;
        }

    default:
            break;
        }
    }

    return false;
}

bool A_DOWN()
{
    if(polygonPtr == nullptr)
        return false;

    const auto& event = polygonPtr->getEvent();

    switch (event.type) {
    case SDL_KEYDOWN:

        switch (event.key.keysym.sym) {
        case SDLK_a:
            return true;
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }

    return false;
}

bool D_DOWN()
{
    if(polygonPtr == nullptr)
        return false;

    const auto& event = polygonPtr->getEvent();

    switch (event.type) {
    case SDL_KEYDOWN:

        switch (event.key.keysym.sym) {
        case SDLK_d:
            return true;
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }

    return false;
}

bool S_DOWN()
{
    if(polygonPtr == nullptr)
        return false;

    const auto& event = polygonPtr->getEvent();

    switch (event.type) {
    case SDL_KEYDOWN:

        switch (event.key.keysym.sym) {
        case SDLK_s:
            return true;
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }

    return false;
}

bool W_DOWN()
{
    if(polygonPtr == nullptr)
        return false;

    const auto& event = polygonPtr->getEvent();
    switch (event.type) {
    case SDL_KEYDOWN:

        switch (event.key.keysym.sym) {
        case SDLK_w:
            return true;
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }

    return false;
}

bool A_UP(){

    if(polygonPtr == nullptr)
        return false;

    const auto& event = polygonPtr->getEvent();
    switch (event.type) {
    case SDL_KEYUP:

        switch (event.key.keysym.sym) {
        case SDLK_a:
            return true;
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }

    return false;
}

bool D_UP(){
    if(polygonPtr == nullptr)
        return false;

    const auto& event = polygonPtr->getEvent();
    switch (event.type) {
    case SDL_KEYUP:

        switch (event.key.keysym.sym) {
        case SDLK_d:
            return true;
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }

    return false;
}

bool S_UP(){
    if(polygonPtr == nullptr)
        return false;

    const auto& event = polygonPtr->getEvent();
    switch (event.type) {
    case SDL_KEYUP:

        switch (event.key.keysym.sym) {
        case SDLK_s:
            return true;
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }

    return false;
}

bool W_UP(){

    if(polygonPtr == nullptr)
        return false;

    const auto& event = polygonPtr->getEvent();
    switch (event.type) {
    case SDL_KEYUP:

        switch (event.key.keysym.sym) {
        case SDLK_w:
            return true;
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }

    return false;
}

int getWidth()
{
    if(polygonPtr == nullptr)
        return false;

    return polygonPtr->getWidth();
}

int getHeight()
{
    if(polygonPtr == nullptr)
        return false;

    return polygonPtr->getHeight();
}

const SDL_Event& getEvent()
{
    if(polygonPtr == nullptr)
        return DUMP_EVENT;

    return polygonPtr->getEvent();
}

void drawCircle(const olc::vi2d &point, int32_t radius, const std::array<uint8_t, 4>& rbg, bool fill)
{
    if(polygonPtr == nullptr)
        return;

    auto renderer = polygonPtr->getRenderer();
    if(renderer == nullptr)
        return;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    fill ? fill_circle(renderer, point, radius, rbg)
         : draw_circle(renderer, point, radius, rbg);

}


}}




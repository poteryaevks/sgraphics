#pragma once

#include <string>
#include <array>
#include <initializer_list>
#include <cmath>

/*
 *
 * 	+-------------------------------------------------------------+
    |           OneLoneCoder Pixel Game Engine v2.16              |
    |  "What do you need? Pixels... Lots of Pixels..." - javidx9  |
    +-------------------------------------------------------------+

 *License (OLC-3)
    ~~~~~~~~~~~~~~~

    Copyright 2018 - 2021 OneLoneCoder.com

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:

    1. Redistributions or derivations of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    2. Redistributions or derivative works in binary form must reproduce the above
    copyright notice. This list of conditions and the following	disclaimer must be
    reproduced in the documentation and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its contributors may
    be used to endorse or promote products derived from this software without specific
    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS	"AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL,	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.

Links
~~~~~
YouTube:	https://www.youtube.com/javidx9
            https://www.youtube.com/javidx9extra
Discord:	https://discord.gg/WhwHUMV
Twitter:	https://www.twitter.com/javidx9
Twitch:		https://www.twitch.tv/javidx9
GitHub:		https://www.github.com/onelonecoder
Homepage:	https://www.onelonecoder.com
Patreon:	https://www.patreon.com/javidx9
Community:  https://community.onelonecoder.com
*/

namespace olc
{

template <class T>
struct v2d_generic
{
    T x = 0;
    T y = 0;
    v2d_generic() : x(0), y(0) {}
    v2d_generic(T _x, T _y) : x(_x), y(_y) {}
    v2d_generic(const v2d_generic& v) : x(v.x), y(v.y) {}
    v2d_generic(v2d_generic&&) = default;
    v2d_generic& operator=(const v2d_generic& v) = default;
    v2d_generic& operator=(v2d_generic&& v) = default;
    T mag() const { return T(std::sqrt(x * x + y * y)); }
    T mag2() const { return x * x + y * y; }
    v2d_generic  norm() const { T r = 1 / mag(); return v2d_generic(x * r, y * r); }
    v2d_generic  perp() const { return v2d_generic(-y, x); }
    v2d_generic  floor() const { return v2d_generic(std::floor(x), std::floor(y)); }
    v2d_generic  ceil() const { return v2d_generic(std::ceil(x), std::ceil(y)); }
    v2d_generic  max(const v2d_generic& v) const { return v2d_generic(std::max(x, v.x), std::max(y, v.y)); }
    v2d_generic  min(const v2d_generic& v) const { return v2d_generic(std::min(x, v.x), std::min(y, v.y)); }
    v2d_generic  cart() { return { std::cos(y) * x, std::sin(y) * x }; }
    v2d_generic  polar() { return { mag(), std::atan2(y, x) }; }
    T dot(const v2d_generic& rhs) const { return this->x * rhs.x + this->y * rhs.y; }
    T cross(const v2d_generic& rhs) const { return this->x * rhs.y - this->y * rhs.x; }
    v2d_generic  operator +  (const v2d_generic& rhs) const { return v2d_generic(this->x + rhs.x, this->y + rhs.y); }
    v2d_generic  operator -  (const v2d_generic& rhs) const { return v2d_generic(this->x - rhs.x, this->y - rhs.y); }
    v2d_generic  operator *  (const T& rhs)           const { return v2d_generic(this->x * rhs, this->y * rhs); }
    v2d_generic  operator *  (const v2d_generic& rhs) const { return v2d_generic(this->x * rhs.x, this->y * rhs.y); }
    v2d_generic  operator /  (const T& rhs)           const { return v2d_generic(this->x / rhs, this->y / rhs); }
    v2d_generic  operator /  (const v2d_generic& rhs) const { return v2d_generic(this->x / rhs.x, this->y / rhs.y); }
    v2d_generic& operator += (const v2d_generic& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
    v2d_generic& operator -= (const v2d_generic& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
    v2d_generic& operator *= (const T& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
    v2d_generic& operator /= (const T& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
    v2d_generic& operator *= (const v2d_generic& rhs) { this->x *= rhs.x; this->y *= rhs.y; return *this; }
    v2d_generic& operator /= (const v2d_generic& rhs) { this->x /= rhs.x; this->y /= rhs.y; return *this; }
    v2d_generic  operator +  () const { return { +x, +y }; }
    v2d_generic  operator -  () const { return { -x, -y }; }
    bool operator == (const v2d_generic& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
    bool operator != (const v2d_generic& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }
    const std::string str() const { return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }
    friend std::ostream& operator << (std::ostream& os, const v2d_generic& rhs) { os << rhs.str(); return os; }
    operator v2d_generic<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
    operator v2d_generic<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
    operator v2d_generic<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y) }; }
};

// Note: joshinils has some good suggestions here, but they are complicated to implement at this moment,
// however they will appear in a future version of PGE
template<class T> inline v2d_generic<T> operator * (const float& lhs, const v2d_generic<T>& rhs)
{ return v2d_generic<T>((T)(lhs * (float)rhs.x), (T)(lhs * (float)rhs.y)); }

template<class T> inline v2d_generic<T> operator * (const double& lhs, const v2d_generic<T>& rhs)
{ return v2d_generic<T>((T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y)); }

template<class T> inline v2d_generic<T> operator * (const int& lhs, const v2d_generic<T>& rhs)
{ return v2d_generic<T>((T)(lhs * (int)rhs.x), (T)(lhs * (int)rhs.y)); }

template<class T> inline v2d_generic<T> operator / (const float& lhs, const v2d_generic<T>& rhs)
{ return v2d_generic<T>((T)(lhs / (float)rhs.x), (T)(lhs / (float)rhs.y)); }

template<class T> inline v2d_generic<T> operator / (const double& lhs, const v2d_generic<T>& rhs)
{ return v2d_generic<T>((T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y)); }

template<class T> inline v2d_generic<T> operator / (const int& lhs, const v2d_generic<T>& rhs)
{ return v2d_generic<T>((T)(lhs / (int)rhs.x), (T)(lhs / (int)rhs.y)); }

// To stop dandistine crying...
template<class T, class U> inline bool operator < (const v2d_generic<T>& lhs, const v2d_generic<U>& rhs)
{ return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x); }

template<class T, class U> inline bool operator > (const v2d_generic<T>& lhs, const v2d_generic<U>& rhs)
{ return lhs.y > rhs.y || (lhs.y == rhs.y && lhs.x > rhs.x); }

typedef v2d_generic<int32_t> vi2d;
typedef v2d_generic<uint32_t> vu2d;
typedef v2d_generic<float> vf2d;
typedef v2d_generic<double> vd2d;

namespace aabb
{

template <class T>
struct rect
{
    v2d_generic<T> pos;   //!<
    v2d_generic<T> size;  //!<
    v2d_generic<T> vel;   //!<

    std::array<olc::aabb::rect<T>*, 4> contact;
};


template <>
struct rect<float>
{
    vf2d pos;   //!<
    vf2d size;  //!<
    vf2d vel;   //!<

    std::array<olc::aabb::rect<float>*, 4> contact;
};


template <>
struct rect<int32_t>
{
    vi2d pos;   //!<
    vi2d size;  //!<
    vi2d vel;   //!<

    std::array<olc::aabb::rect<int32_t>*, 4> contact;
};


template<class T>
inline bool PointVsRect(const v2d_generic<T>& p, const olc::aabb::rect<T>* r)
{
    return (p.x >= r->pos.x && p.y >= r->pos.y && p.x < r->pos.x + r->size.x && p.y < r->pos.y + r->size.y);
}


template<>
inline bool PointVsRect(const olc::vf2d& p, const olc::aabb::rect<float>* r)
{
    return (p.x >= r->pos.x && p.y >= r->pos.y && p.x < r->pos.x + r->size.x && p.y < r->pos.y + r->size.y);
}

template<>
inline bool PointVsRect(const olc::vi2d& p, const olc::aabb::rect<int32_t>* r)
{
    return (p.x >= r->pos.x && p.y >= r->pos.y && p.x < r->pos.x + r->size.x && p.y < r->pos.y + r->size.y);
}


template<class T>
inline bool RectVsRect(const olc::aabb::rect<T>* r1, const olc::aabb::rect<T>* r2)
{
    return (r1->pos.x < r2->pos.x + r2->size.x && r1->pos.x + r1->size.x > r2->pos.x && r1->pos.y < r2->pos.y + r2->size.y && r1->pos.y + r1->size.y > r2->pos.y);
}


//////////////////////////

inline bool RayVsRect(const olc::vf2d& ray_origin, const olc::vf2d& ray_dir, const rect<float>* target, olc::vf2d& contact_point, olc::vf2d& contact_normal, float& t_hit_near)
{
    contact_normal = { 0,0 };
    contact_point = { 0,0 };

    // Cache division
    olc::vf2d invdir = 1.0f / ray_dir;

    // Calculate intersections with rectangle bounding axes
    olc::vf2d t_near = (target->pos - ray_origin) * invdir;
    olc::vf2d t_far = (target->pos + target->size - ray_origin) * invdir;

    if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
    if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

    // Sort distances
    if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
    if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

    // Early rejection
    if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

    // Closest 'time' will be the first contact
    t_hit_near = std::max(t_near.x, t_near.y);

    // Furthest 'time' is contact on opposite side of target
    float t_hit_far = std::min(t_far.x, t_far.y);

    // Reject if ray direction is pointing away from object
    if (t_hit_far < 0)
        return false;

    // Contact point of collision from parametric line equation
    contact_point = ray_origin + t_hit_near * ray_dir;

    if (t_near.x > t_near.y)
        if (invdir.x < 0)
            contact_normal = { 1, 0 };
        else
            contact_normal = { -1, 0 };
    else if (t_near.x < t_near.y)
        if (invdir.y < 0)
            contact_normal = { 0, 1 };
        else
            contact_normal = { 0, -1 };

    // Note if t_near == t_far, collision is principly in a diagonal
    // so pointless to resolve. By returning a CN={0,0} even though its
    // considered a hit, the resolver wont change anything.
    return true;
}
inline bool DynamicRectVsRect(const olc::aabb::rect<float>* r_dynamic, const float fTimeStep, const olc::aabb::rect<float>& r_static,

                              olc::vf2d& contact_point, olc::vf2d& contact_normal, float& contact_time)
{
    // Check if dynamic rectangle is actually moving - we assume rectangles are NOT in collision to start
    if (r_dynamic->vel.x == 0 && r_dynamic->vel.y == 0)
        return false;

    // Expand target rectangle by source dimensions
    olc::aabb::rect<float> expanded_target;
    expanded_target.pos = r_static.pos - r_dynamic->size / 2;
    expanded_target.size = r_static.size + r_dynamic->size;

    if (RayVsRect(r_dynamic->pos + r_dynamic->size / 2, r_dynamic->vel * fTimeStep, &expanded_target, contact_point, contact_normal, contact_time))
        return (contact_time >= 0.0f && contact_time < 1.0f);
    else
        return false;
}



inline bool ResolveDynamicRectVsRect(olc::aabb::rect<float>* r_dynamic, const float fTimeStep, olc::aabb::rect<float>* r_static)
{
    olc::vf2d contact_point, contact_normal;
    float contact_time = 0.0f;
    if (DynamicRectVsRect(r_dynamic, fTimeStep, *r_static, contact_point, contact_normal, contact_time))
    {
        r_dynamic->contact[0] = (contact_normal.y > 0) ? r_static : nullptr;
        r_dynamic->contact[1] = (contact_normal.x < 0) ? r_static : nullptr;
        r_dynamic->contact[2] = (contact_normal.y < 0) ? r_static : nullptr;
        r_dynamic->contact[3] = (contact_normal.x > 0) ? r_static : nullptr;

        r_dynamic->vel += contact_normal * olc::vf2d(std::abs(r_dynamic->vel.x), std::abs(r_dynamic->vel.y)) * (1 - contact_time);
        return true;
    }

    return false;
}
}

}




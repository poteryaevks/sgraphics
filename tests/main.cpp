//#include <gtest/gtest.h>

#include <iostream>

#include "sgraphics/geometry/olc.h"

#include "sgraphics/engine/polygon.h"
#include "sgraphics/engine/polygon_funcs.h"

//!
//! \brief The SgTest class
//!
class SgTest
{

public:

    SgTest() = default;
    ~SgTest() = default;

    //!
    //! \brief initImpl
    //!
    void initImpl(){

    }

    //!
    //! \brief updateImpl
    //! \param fElapsedTime
    //!
    void updateImpl(float fElapsedTime){

        using rect_type = olc::aabb::rect<float>;

        sg::engine::clearScreen({255, 255, 255, 255});

        sg::engine::drawRect(
                    rect_type({{0, 0}, {20, 20}}),
        {255, 0, 0, 100},
                    true
                    );

        sg::engine::drawCircle(
        {500, 500},
                    100,
        {255, 0, 0, 100},
                    true
                    );
    }

    //!
    //! \brief quitImpl
    //!
    void quitImpl(){

    }

};

//!
//! \brief main
//! \param argc
//! \param argv
//! \return
//!
int main(int argc, char *argv[])
{/*
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/
    try{

        sg::engine::Polygon<SgTest>::instance().init();
        sg::engine::Polygon<SgTest>::instance().run();
    }
    catch(const std::exception& ex){

        std::cout << ex.what() << std::endl;
        return -1;
    }

    return 0;
}

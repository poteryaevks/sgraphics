// #include "examples/three_triangles.hpp"
// #include "examples/grid.hpp"
#include "examples/dda_algorithm.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    try
    {
        DdaAlgorithm game("DdaAlgorithm");
        game.Run();
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    return 0;
}

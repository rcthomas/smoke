
#include <iostream>

#include "luaxx.h"

#include "Grid.hh"
#include "Zone.hh"

int main( int argc, char* argv[] )
{

    std::cout << "loading model ... " << std::endl;
    Grid< Zone > grid = Grid< Zone >::load( argv[ 1 ] );
    std::cout << " ... finished " << std::endl;

    for( int id = 0; id < grid.size(); ++ id )
    {
        Node node = grid.node( id );
        std::cout << node << "    " << grid( id ) << std::endl;
    }

    return 0;
}

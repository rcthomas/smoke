
#include <iostream>
#include <sstream>

#include "luaxx.h"

#include "Grid.hh"
#include "Zone.hh"

int main( int argc, char* argv[] )
{

    lua::state lua;
    lua.openlibs();
    lua.loadfile( argv[ 1 ] );

    double  d;
    int     n;

    {
        std::stringstream ss;
        ss << argv[ 2 ];
        ss >> d;

        ss.clear();
        ss << argv[ 3 ];
        ss >> n;
    }

    Grid< Zone > grid = Grid< Zone >::cubic( d, n );

    std::cout << "creating model ... " << std::endl;
    for( int id = 0; id < grid.size(); ++ id )
    {

        int progress = 100.0 * double( id ) / double( grid.size() );
        std::cout << "\rprogress: " << progress << "%";

        Node node = grid.node( id );

        lua.getglobal( "density" );
        lua.push( node.x );
        lua.push( node.y );
        lua.push( node.z );
        lua.pcall( 3, 1 ).to( grid( id ).density ).pop();

        lua.getglobal( "nickel" );
        lua.push( node.x );
        lua.push( node.y );
        lua.push( node.z );
        lua.pcall( 3, 1 ).to( grid( id ).nickel ).pop();

    }
    std::cout << "\rprogress: complete" << std::endl;

    std::cout << "saving model ... " << std::endl;
    grid.save( argv[ 4 ] );
    std::cout << " ... finished " << std::endl;

    return 0;
}

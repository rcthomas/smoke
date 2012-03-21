
#include "Index.hh"
#include "Node.hh"

Node::Node( const Index& index, int const id_ ) :
    id( id_ )
{
    i = id;
    k = i % index._nz;
    i = ( i - k ) / index._nz;
    j = i % index._ny;
    i = ( i - j ) / index._ny;
    x = index._xc + index._d * i;
    y = index._yc + index._d * j;
    z = index._zc + index._d * k;
}

Node::Node( const Index& index, int const i_, int const j_, int const k_ ) :
    i( i_ ), j( j_ ), k( k_ )
{
    id = k + index._nz * ( j + index._ny * i );
    x  = index._xc + index._d * i;
    y  = index._yc + index._d * j;
    z  = index._zc + index._d * k;
}

Node::Node( const Index& index, double const x_, double const y_, double const z_ ) :
    x( x_ ), y( y_ ), z( z_ )
{
    i  = ( x - index._xl ) / index._d;
    j  = ( y - index._yl ) / index._d;
    k  = ( z - index._zl ) / index._d;
    id = k + index._nz * ( j + index._ny * i );
}

Node::Node( const Node& node ) :
    id( node.id ),
    i ( node.i  ), j( node.j ), k( node.k ),
    x ( node.x  ), y( node.y ), z( node.z )
{}

Node& Node::operator = ( const Node& node )
{
    if( this != &node )
    {
        id = node.id;
        i  = node.i ; j = node.j; k = node.k;
        x  = node.x ; y = node.y; z = node.z;
    }
    return *this;
}

std::ostream& operator << ( std::ostream& stream, const Node& node )
{
    stream << node.id << "   " << node.i << " " << node.j << " " << node.k << "  " << node.x << " " << node.y << " " << node.z;
    return stream;
}

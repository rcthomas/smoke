
#ifndef NODE__HH
#define NODE__HH

#include <iostream>

class Index;

class Node
{

    public :

        /// Constructor given id.
        Node( const Index& index, int const id );

        /// Constructor given indices.
        Node( const Index& index, int const i, int const j, int const k );

        /// Constructor given coordinates.
        Node( const Index& index, double const x, double const y, double const z );

        /// Copy constructor.
        Node( const Node& node );

        /// Destructor.
        ~Node() {}

        /// Assignment operator.
        Node& operator = ( const Node& node );

    public :

        int     id;
        int     i, j, k;
        double  x, y, z;

};

std::ostream& operator << ( std::ostream& stream, const Node& node );

#endif

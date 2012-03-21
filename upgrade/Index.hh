
#ifndef INDEX__HH
#define INDEX__HH

#include "Node.hh"

class Index
{

    public :

        friend class Node;

        /// Constructor.
        Index( double const d, int const nx, int const ny, int const nz );

        /// Copy constructor.
        Index( const Index& index );

        /// Destructor.
        ~Index() {}

        /// Total number of nodes.
        int size() const { return _nx * _ny * _nz; }

        /// Node spacing.
        double d() const { return _d; }

        /// Dimensions.
        ///@{
        int nx() const { return _nx; }
        int ny() const { return _ny; }
        int nz() const { return _nz; }
        ///@}

        /// Coordinate value to coordinate index.
        ///@{
        int i( double const x ) const { return ( x - _xl ) / _d; }
        int j( double const y ) const { return ( y - _yl ) / _d; }
        int k( double const z ) const { return ( z - _zl ) / _d; }
        ///@}

        /// Coordinate index to coordinate value.
        ///@{
        double x( int const i ) const { return _xc + _d * i; }
        double y( int const j ) const { return _yc + _d * j; }
        double z( int const k ) const { return _zc + _d * k; }
        ///@}

        /// Coordinate index/value to identifier.
        ///@{
        int id( int    const i, int    const j, int    const k ) const { return k + _nz * ( j + _ny * i );    }
        int id( double const x, double const y, double const z ) const { return id( i( x ), j( y ), k( z ) ); }
        ///@}

        /// All node meta-data.
        ///@{
        Node node( int const id ) const { return Node( *this, id ); }
        Node node( int const i, int const j, int const k ) const { return Node( *this, i, j, k ); }
        Node node( double const x, double const y, double const z ) const { return Node( *this, x, y, z ); }
        ///@}

        /// Assignment operator.
        Index& operator = ( const Index& index );

    private :

        double  _d;             ///< Node spacing.
        int     _nx, _ny, _nz;  ///< Dimensions.

        double  _xl, _yl, _zl;  ///< Cell face coordinate zero point.
        double  _xc, _yc, _zc;  ///< Node coordinate zero point.

};

#endif

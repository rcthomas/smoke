
#ifndef GRID__HH
#define GRID__HH

#include "H5Cpp.h"

#include "Index.hh"

template< typename T >
class Grid : public Index
{

    public :

        /// Load from HDF5 file.
        static Grid load( const char* file );

        /// Rectangular grid.
        static Grid rectangular( double const d, int const nx, int const ny, int const nz );

        /// Cubic grid.
        static Grid cubic( double const d, int const n );

    private :

        /// Constructor.
        Grid( double const d, int const nx, int const ny, int const nz );

    public :

        /// Copy constructor.
        Grid( const Grid& grid );

        /// Destructor.
        ~Grid();

        /// Save to HDF5 file.
        void save( const char* file );

        /// Access by ID.
        ///@{
        T  operator() ( int const id ) const { return _data[ id ]; }
        T& operator() ( int const id )       { return _data[ id ]; }
        ///@}

        /// Access by indices.
        ///@{
        T  operator() ( int const i, int const j, int const k ) const { return _data[ id( i, j, k ) ]; }
        T& operator() ( int const i, int const j, int const k )       { return _data[ id( i, j, k ) ]; }
        ///@}

        /// Access by coordinates.
        ///@{
        T  operator() ( double const x, double const y, double const z ) const { return _data[ id( x, y, z ) ]; }
        T& operator() ( double const x, double const y, double const z )       { return _data[ id( x, y, z ) ]; }
        ///@}

        /// Assignment operator.
        Grid& operator = ( const Grid& grid );

    private :

        T* _data;

};

template< typename T >
struct HDF5
{
    static H5::DataType type() { return T::hdf5_type(); }
};

template<>
struct HDF5< int >
{
    static H5::DataType type() { return H5::PredType::NATIVE_INT; }
};

template<>
struct HDF5< double >
{
    static H5::DataType type() { return H5::PredType::NATIVE_DOUBLE; }
};

template< typename T >
Grid< T > Grid< T >::load( const char* file )
{

    H5::H5File      h5file( file, H5F_ACC_RDONLY );
    H5::DataSet     data_set = h5file.openDataSet( file );
    H5::DataSpace   data_space = data_set.getSpace();

    H5::FloatType   float_type( H5::PredType::NATIVE_DOUBLE );
    H5::DataSpace   attr_space( H5S_SCALAR );
    H5::Attribute   attr = data_set.openAttribute( "d" );

    double d;
    attr.read( float_type, &d );

    hsize_t dims[ 3 ];
    int ndims = data_space.getSimpleExtentDims( dims, NULL );

    Grid< T > grid( d, dims[ 0 ], dims[ 1 ], dims[ 2 ] );

    data_set.read( grid._data, HDF5< T >::type() );

    h5file.close();

    return grid;
}

template< typename T >
Grid< T > Grid< T >::rectangular( double const d, int const nx, int const ny, int const kz )
{
    return Grid< T >( d, nx, ny, nz );
}

template< typename T >
Grid< T > Grid< T >::cubic( double const d, int const n )
{
    return Grid< T >( d, n, n, n );
}

template< typename T >
Grid< T >::Grid( double const d, int const nx, int const ny, int const nz ) :
    Index( d, nx, ny, nz )
{
    _data = new T [ size() ];
}

template< typename T >
Grid< T >::Grid( const Grid< T >& grid ) :
    Index( grid )
{
    T* new_data = new T [ size() ];
    std::copy( grid._data, grid._data + size(), new_data );
    delete [] _data;
    _data = new_data;
}

template< typename T >
Grid< T >::~Grid()
{
    delete [] _data;
}

template< typename T >
void Grid< T >::save( const char* file )
{

    // Data space, dimensions.

    int rank = 3;
    hsize_t dims[ rank ];
    dims[ 0 ] = nx();
    dims[ 1 ] = ny();
    dims[ 2 ] = nz();
    H5::DataSpace data_space( rank, dims );

    // Write data set; name is same as file, not too creative, could improve.

    H5::H5File h5file( file, H5F_ACC_TRUNC );
    H5::DataSet data_set( h5file.createDataSet( file, HDF5< T >::type(), data_space ) );
    data_set.write( _data, HDF5< T >::type() );

    // Attribute.

    double d = this->d();

    H5::FloatType float_type( H5::PredType::NATIVE_DOUBLE );
    H5::DataSpace attr_space( H5S_SCALAR );
    H5::Attribute attr = data_set.createAttribute( "d", float_type, attr_space );
    attr.write( float_type, &d );

    h5file.close();

}

template< typename T >
Grid< T >& Grid< T >::operator = ( const Grid< T >& grid )
{
    if( this != &grid )
    {
        Index::operator = ( grid );
        T* new_data = new T [ size() ];
        std::copy( grid._data, grid._data + size(), new_data );
        delete [] _data;
        _data = new_data;
    }
    return *this;
}

#endif

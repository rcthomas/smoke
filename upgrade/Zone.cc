
#include "H5Cpp.h"

#include "Zone.hh"

H5::DataType Zone::hdf5_type() 
{
    H5::CompType data_type( sizeof( Zone ) );
    data_type.insertMember( "density", HOFFSET( Zone, density ), H5::PredType::NATIVE_DOUBLE );
    data_type.insertMember( "nickel" , HOFFSET( Zone, nickel  ), H5::PredType::NATIVE_DOUBLE );
    return data_type;
}

std::ostream& operator << ( std::ostream& stream, const Zone& zone )
{
    stream << zone.density << " " << zone.nickel << " " << zone.other;
    return stream;
}

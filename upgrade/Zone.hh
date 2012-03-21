
#ifndef ZONE__HH
#define ZONE__HH

#include <iostream>

namespace H5
{
    class DataType;
}

struct Zone
{
    double density;
    double nickel;
    double other;

    static H5::DataType hdf5_type();
};

std::ostream& operator << ( std::ostream& stream, const Zone& zone );

#endif

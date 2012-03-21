
#include "Index.hh"

Index::Index( double const d, int const nx, int const ny, int const nz ) :
    _d ( d  ), 
    _nx( nx ), _ny( ny ), _nz( nz )
{
    _xl = -0.5 * _d * _nx;
    _yl = -0.5 * _d * _ny;
    _zl = -0.5 * _d * _nz;
    _xc = _xl + 0.5 * _d;
    _yc = _yl + 0.5 * _d;
    _zc = _zl + 0.5 * _d;
}

Index::Index( const Index& index ) :
    _d ( index._d  ), 
    _nx( index._nx ), _ny( index._ny ), _nz( index._nz ),
    _xl( index._xl ), _yl( index._yl ), _zl( index._zl ),
    _xc( index._xc ), _yc( index._yc ), _zc( index._zc )
{}

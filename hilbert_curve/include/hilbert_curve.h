#ifndef __HILBERT_CURVE__
#define __HILBERT_CURVE__

#include <bitset>
#include <vector>
#include <iostream>
#include <initializer_list>
#include <string>

// internal includes
#include <error_handling.h>

// =======================================================================================


template< const size_t dim = 2,
	  const size_t depth = 8 >
struct hilbert_coord_t {

  using bitsetfix = std::bitset< depth >;
  using vecbitset = std::vector< bitsetfix >;

  hilbert_coord_t () = default;

  hilbert_coord_t ( std::initializer_list< bitsetfix > list ) {
    
    if ( list.size() != dim )
      throw sico_err::size_invalid { "Error in initialization, provided list has wrong size!" };

    _container = list;

  }

  ~hilbert_coord_t () = default;

  bitsetfix & operator[] ( std::size_t idx ) { return _container[ idx ]; }
  const bitsetfix & operator[] ( std::size_t idx ) const { return _container[ idx ]; }

  // push-backing here should not cost anything since the usual number
  // of push-backs should be in the order <~4-5 at most (==3 for 3d space)
  std::vector< std::size_t > operator() () {

    std::vector< std::size_t > container;
    for ( auto&& _c : _container )
      container.push_back( _c.to_ulong() );
    return container;

  }

  size_t operator() ( const size_t idx ) { return _container[ idx ].to_ulong(); }
  size_t operator() ( const size_t idx ) const { return _container[ idx ].to_ulong(); }

  size_t size () const { return dim; }

private:

  vecbitset _container = vecbitset( dim, bitsetfix { size_t( 0 ) } );

}; // endstruct hilbert_coord_t  

// ==============================================================================================
// ==============================================================================================
// ==============================================================================================

template< std::size_t N >
bool operator< ( const std::bitset< N > & xx, const std::bitset< N > & yy ) {
  
    for ( int ii = N - 1; ii >= 0; ii--) {
        if ( xx[ ii ] ^ yy[ ii ] ) return yy[ ii ];
    }
    return false;
}

template< std::size_t N >
bool operator<= ( const std::bitset< N > & xx, const std::bitset< N > & yy ) { return !( yy < xx ); }

template< std::size_t N >
bool operator> ( const std::bitset< N > & xx, const std::bitset< N > & yy ) { return ( yy < xx ); }

template< std::size_t N >
bool operator>= ( const std::bitset< N > & xx, const std::bitset< N > & yy ) { return !( xx < yy ); }

// ==============================================================================================

template< std::size_t N >
std::bitset< N > minus1 ( std::bitset< N > bits ) {

    std::bitset< N > mm { 1 };
  
  while ( !( ( bits & mm ).any() ) ) {    
    bits = bits ^ mm;
    mm <<= 1;
  }

  bits = bits ^ mm;

  return bits;
  
}

// ==============================================================================================
// ==============================================================================================
// ==============================================================================================

template < const size_t dim = 2,
	   const size_t depth = 8 >
class hilbert_curve {
  
  using bitsetfix = std::bitset< depth >;
  bitsetfix _mask1 {};
  size_t _levhilbert = depth;
  
public:
  
  hilbert_curve () { _mask1.flip(); _mask1.flip( 0 ); }

  ~hilbert_curve () = default;

  std::bitset< dim * depth > get_key ( const hilbert_coord_t< dim, depth > & xx ) const;

  hilbert_coord_t< dim, depth > get_axes ( const hilbert_coord_t< dim, depth > & xx ) const;

  hilbert_coord_t< dim, depth > get_grid ( const hilbert_coord_t< dim, depth > & xx ) const;
  
}; // endclass hilbert_curve

template < const size_t dim, const size_t depth >
std::bitset< dim * depth > hilbert_curve< dim, depth >::get_key ( const hilbert_coord_t< dim, depth > & xx ) const {

  std::bitset< dim * depth > key { size_t( 0 ) };
  int levkey = _levhilbert - 1;

  while ( levkey >= 0 ) {

    for ( size_t ii = 0; ii < dim; ++ii )
      if ( xx[ ii ][ levkey ] )	key.set( dim - 1 - ii + dim * levkey );

    --levkey;

  }

  return key;
  
}

// ==============================================================================================

template < const size_t dim, const size_t depth >
hilbert_coord_t< dim, depth > hilbert_curve< dim, depth >::get_axes ( const hilbert_coord_t< dim,
								      depth > & xx ) const {

  hilbert_coord_t< dim, depth > yy = xx;
  hilbert_curve::bitsetfix N { 2 << ( depth - 1 ) }, P, Q, t, one { 1 };

  // Gray decode by H ^ ( H / 2 )
  t = yy[ dim - 1 ] >> 1;
  for ( size_t ii = dim - 1; ii > 0; --ii ) yy[ ii ] ^= yy[ ii - 1 ];
  yy[ 0 ] ^= t;

  // Undo excess work
  for ( Q = 2; Q != N; Q <<= 1 ) {
    P = minus1( Q );
    for ( size_t ii = dim - 1; ii >= 0; --ii )
      if ( ( yy[ ii ] & Q ).any() ) yy[ 0 ] ^= P; // invert
      else {
	t = ( yy[ 0 ] ^ yy[ ii ] ) & P;
	yy[ 0 ] ^= t;
	yy[ ii ] ^= t;
      } // exchange
  }

  return yy;
  
}

// ==============================================================================================

template < const size_t dim, const size_t depth >
hilbert_coord_t< dim, depth > hilbert_curve< dim, depth >::get_grid ( const hilbert_coord_t< dim,
								      depth > & xx ) const {

  hilbert_coord_t< dim, depth > yy = xx;
  
  hilbert_curve::bitsetfix M { 1 << ( depth - 1 ) }, P, Q, t;

  for ( Q = M; ( Q & _mask1 ).any(); Q >>= 1 ) {
    P = minus1( Q );
    for ( size_t ii = 0; ii < dim; ++ii )
      if ( ( yy[ ii ] & Q ).any() ) yy[ 0 ] ^= P; // invert
      else {
	t = ( yy[ 0 ] ^ yy[ ii ] ) & P;
	yy[ 0 ] ^= t;
	yy[ ii ] ^= t;
      } // exchange
  }

  // Gray encode
  for ( size_t ii = 1; ii < dim; ++ii ) yy[ ii ] ^= yy[ ii - 1 ];
  t = 0;
  for ( Q = M; ( Q & _mask1 ).any(); Q >>= 1 )
    if ( ( yy[ dim - 1 ] & Q ).any() ) t ^= minus1( Q );
  for ( size_t ii = 0; ii < dim; ++ii ) yy[ ii ] ^= t;
  
  return yy;
  
}

// ==============================================================================================

#endif //__HILBERT_CURVE__

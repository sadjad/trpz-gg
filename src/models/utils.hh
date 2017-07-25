/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#include <string>
#include <stdexcept>
#include <vector>

#include "path.hh"

namespace gg {
  namespace models {
    roost::path create_gg_dir()
    {
      const char * envar = getenv( "GG_DIR" );
      roost::path gg_path { envar ? std::string( envar ) : std::string( ".gg" ) };

      /* create the gg directory, if it doesn't exist */
      if ( not roost::is_directory( gg_path ) ) {
        roost::create_directories( gg_path );
      }

      return roost::absolute( gg_path );
    }

    std::vector<std::string> args_to_vector( int argc, char ** argv )
    {
      std::vector<std::string> result;

      /* ignores argv[ 0 ] */
      for ( int i = 1; i < argc; i++ ) {
        result.push_back( argv[ i ] );
      }

      return result;
    }
  }
}

/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

#include "s3.hh"
#include "path.hh"
#include "ggpaths.hh"

using namespace std;

void usage( const char * argv0 )
{
  cerr << argv0 << " S3-REGION S3-BUCKET [S3-ENDPOINT]" << endl;
}

int main( int argc, char * const argv[] )
{
  if ( argc <= 0 ) {
    abort();
  }

  if ( argc < 3 ) {
    usage( argv[ 0 ] );
    return EXIT_FAILURE;
  }

  string s3_region { argv[ 1 ] };
  string s3_bucket { argv[ 2 ] };
  string s3_endpoint;

  if ( argc == 4 ) {
    s3_endpoint = argv[ 3 ];
  }

  vector<S3::DownloadRequest> files;

  string object_key;
  while ( cin >> object_key ) {
    files.push_back( { object_key, gg::paths::blob_path( object_key ) } );
  }

  S3ClientConfig client_config;
  client_config.region = s3_region;

  S3Client s3_client { client_config };
  s3_client.download_files( s3_bucket, files );

  return EXIT_SUCCESS;
}

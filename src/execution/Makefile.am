AM_CPPFLAGS = -I../protobufs -I$(srcdir)/../util -I$(srcdir)/../tui \
              -I$(srcdir)/../trace -I$(srcdir)/../sandbox -I$(srcdir)/../net \
              -I$(srcdir)/../thunk $(CXX14_FLAGS) $(PROTOBUF_CFLAGS) \
              $(SSL_CFLAGS) $(SSL_CFLAGS) $(CRYPTO_CFLAGS)

AM_CXXFLAGS = $(PICKY_CXXFLAGS) $(EXTRA_CXXFLAGS)

noinst_LIBRARIES = libggexecution.a

libggexecution_a_SOURCES = remote_response.hh remote_response.cc \
                           connection_context.hh connection_context.cc \
                           loop.hh loop.cc \
                           engine.hh \
                           engine_local.hh engine_local.cc \
                           engine_lambda.hh engine_lambda.cc \
                           engine_gg.hh engine_gg.cc \
                           engine_wsk.hh engine_wsk.cc \
                           reductor.hh reductor.cc

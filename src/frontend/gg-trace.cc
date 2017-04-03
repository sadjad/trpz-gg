/* -*-mode:c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>

#include "exception.hh"

using namespace std;

void usage( const char * argv0 )
{
  cerr << argv0 << " COMMAND [option]..." << endl;
}

int wait_for_syscall( pid_t child_pid )
{
  int status;

  while ( true ) {
    SystemCall( "ptrace(SYSCALL)", ptrace( PTRACE_SYSCALL, child_pid, 0, 0 ) );
    waitpid( child_pid, &status, 0 );

    if ( WIFSTOPPED( status ) && WSTOPSIG( status ) & 0x80 ) {
      return 0;
    }

    if ( WIFEXITED( status ) ) {
      return 1;
    }
  }
}

int main( int argc, char * argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort();
    }

    if ( argc < 2 ) {
      usage( argv[ 0 ] );
      return EXIT_FAILURE;
    }

    pid_t child_pid = SystemCall( "fork", fork() );

    if ( child_pid == 0 ) {
      SystemCall( "ptrace(TRACEME)", ptrace( PTRACE_TRACEME ) );
      kill( getpid(), SIGSTOP );
      return SystemCall( "execvp", execvp( argv[ 1 ], &argv[ 1 ] ) );
    }
    else {
      int child_ret;

      SystemCall( "waitpid", waitpid( child_pid, &child_ret, 0 ) );
      SystemCall( "ptrace(SETOPTIONS)", ptrace( PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACESYSGOOD ) );

      while ( true ) {
        if ( wait_for_syscall( child_pid ) != 0 ) {
          break;
        }

        int syscall_no = ptrace( PTRACE_PEEKUSER, child_pid, 8 * ORIG_RAX );

        cout << "syscall( " << syscall_no << " ) = ";

        if ( wait_for_syscall( child_pid ) != 0 ) {
          break;
        }

        int retval = ptrace( PTRACE_PEEKUSER, child_pid, 8 * RAX );

        cout << retval << endl;
      }
    }
  }
  catch ( const exception &  e ) {
    print_exception( argv[ 0 ], e );
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
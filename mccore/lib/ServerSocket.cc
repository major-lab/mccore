#include "ServerSocket.h"

#include <iostream.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

ServerSocket::ServerSocket (int port)
{
  sockaddr_in sin;

  // Creating socket ---
  if ((socket_id = ::socket (AF_INET, SOCK_STREAM, 0)) < 0) {
    // put exceptions!!!
    cerr << "could not create socket" << endl;
    abort ();
  }

  // Binding a name to the socket ---
  bzero (&sin, sizeof (sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons (port);

  if (::bind (socket_id, (sockaddr*)&sin, sizeof (sin)) < 0) {
    cerr << "bind failed" << endl;
    abort ();
  }
}

ServerSocket::~ServerSocket ()
{
  close ();
}


sBinstream*
ServerSocket::accept ()
{
  sockaddr_in client;
  int clientlen;
  int cid;
  sBinstream* stream;

  if (listen (socket_id, MAX_QUEUE_LEN) < 0) {
    cerr <<  "listen failed" << endl;
    return NULL;
  }

  if ((cid = ::accept (socket_id, (sockaddr*)&client, 
		       (socklen_t*)&clientlen)) < 0) {
    cerr << "Accept failed" << endl;
    return NULL;
  }
       
  stream = new sBinstream (cid);

  return stream;
}

void
ServerSocket::close ()
{
  ::close (socket_id);
}

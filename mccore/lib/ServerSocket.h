// SocketTools.h        -*- mode: c++ -*-

#ifndef _ServerSocket_h_
#define _ServerSocket_h_

#include "sBinstream.h"

#define MAX_QUEUE_LEN 5

/**
 * @short Implementation of a server socket.
 *
 * This class implements a server socket on which we can listen and
 * wait for a connection from a client and returns a socket stream
 * (sBinstream).
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca> */
class ServerSocket
{
  int socket_id;

  ServerSocket () {}

public:

  /**
   * Creates a server socket on the specified port.
   */

  ServerSocket (int port);

  /**
   * Destructor.
   */
  ~ServerSocket ();


  /**
   * Listens for a connection to be made and accepts it.  This is a
   * blocking call on the listen(2) function.
   * @return a newly created stream (not destroyed here)
   */
  sBinstream* accept ();

  /**
   * Closes this socket.
   */
  void close ();

};

#endif

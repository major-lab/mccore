//                         -*- Mode: C++ -*-

#ifndef _sockbuf_h_
#define _sockbuf_h_

#include <iostream.h>

#include <streambuf.h>


/**
 * @short Implementation of a socket trivial buffer
 *
 * This buffer does not buffer anything, it reads and writes immediatly 
 *
 * @author Patrick Gendron <gendrop@iro.umontreal.ca>
 */
class sockbuf : public streambuf
{
public:
  int socket_id;

public:

  /**
   * Initializes the socket buffer.
   */
  sockbuf ();
  
  /**
   * Initializes the socket buffer with a socket.
   * @param s a socket created by accept(2) or socket(2).
   */
  sockbuf (int s) : streambuf (), socket_id (s) {}

  /**
   * Destructor.
   */
  virtual ~sockbuf () { }

  
/**
   * Open the stream with a connection to the given host.
   * @param host the server's host name
   * @param port the port on which to call the host
   * @return itself if the operation went successfull, 0 otherwise.
   */
  virtual sockbuf* open (const char* host, int port);

  /**
   * Closes the stream.
   */
  virtual void close ();
  
  /**
   * Socket read method.
   * @param buf the bytes to read
   * @param size the number of bytes to read
   * return the number of bytes read (-1 on error)
   */
  virtual streamsize sys_read (char* buf, streamsize size);

  /**
   * Socket write method.
   * @param buf the bytes to write
   * @param len the number of bytes to write
   * @param flags the flags passed to send(2)
   * return the number of bytes written (-1 on error)
   */ 
  virtual streamsize sys_write (const char *buf, streamsize size);

  /**
   * Closes the stream.
   * @return 0 on success.
   */
  virtual int sys_close ();

  /**
   * Socket readline method.  Reads up to "\r\n".
   * @param buf the bytes to read
   * @param maxlen the maximum number of bytes to read
   * @return the number of bytes read (-1 on error)
   */
//    virtual streamsize readline (char* buf, streamsize maxlen);

protected:

  /**
   * Stream input method.
   */
  virtual streamsize xsgetn (char* s, streamsize n);    

  /**
   * Stream output method.
   * 
   */
  virtual streamsize xsputn (const char* s, streamsize n);

};

#endif

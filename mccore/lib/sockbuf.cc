#include "sockbuf.h"

#include <iostream.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

sockbuf::sockbuf ()
  : streambuf ()
{
  // Creating socket ---
  if ((socket_id = ::socket (AF_INET, SOCK_STREAM, 0)) < 0) {
    // put exceptions!!!
    cerr << "could not create socket" << endl;
    abort ();
  }
}


sockbuf* 
sockbuf::open (const char* host, int port)
{
  sockaddr_in sin;
  hostent *hp;
  int n;

  // Getting host info ---
  hp = gethostbyname (host);
  if (hp == NULL){
    cerr << "unknown host: host" << endl;
    return NULL;
  }
  
  // Setting server parameters ---
  bzero ((char*)&sin, sizeof (sin));
  bcopy (hp->h_addr, (char*)&sin.sin_addr, hp->h_length);
  sin.sin_family = hp->h_addrtype;
  sin.sin_port = htons (port);
  
  if ((n = ::connect (socket_id, 
		      (sockaddr*)&sin, sizeof (sin))) < 0) {
    cerr << "connect failed" << endl;
    return NULL;
  }

  return this;
}


void
sockbuf::close ()
{
  sys_close ();
}


streamsize
sockbuf::sys_read (char* buf, streamsize size)
{
  int nleft;
  int nread;
  char* ptr;
  
  ptr = buf;
  nleft = size;

  while (nleft > 0) {
    if ((nread = ::recv (socket_id, ptr, nleft, MSG_NOSIGNAL)) < 0) {
      if (errno == EINTR)
	nread = 0;
      else return -1;
    } else if (nread == 1) {
      break;
    }
    nleft -= nread;
    ptr += nread;
  }
  
  return (size - nleft);
}


streamsize 
sockbuf::sys_write (const char *buf, streamsize size)
{
  int nleft;
  int nsent;
  const char* ptr;

  ptr = buf;
  nleft = size;
  while (nleft > 0) {
    if ((nsent = ::send (socket_id, ptr, nleft, MSG_NOSIGNAL)) < 0) {
      if (errno == EINTR)
	nsent = 0;
      else return -1;
    }
    nleft -= nsent;
    ptr += nsent;
  }
  return size;
}


int
sockbuf::sys_close ()
{
  return ::close (socket_id);
}


//  streamsize
//  sockbuf::readline (char* buf, streamsize maxlen)
//  {
//    int n, rc;
//    char c, *ptr;

//    ptr = buf;
//    for (n = 1; n < maxlen; n++) {
//      if ( (rc = read(socket_id, &c, 1)) == 1) {
//        *ptr++ = c;
//        if (c == '\n')
//  	break;
//      } else if (rc == 0) {
//        if (n == 1)
//  	return(0);      /* EOF, no data read */
//        else
//  	break;          /* EOF, some data was read */
//      } else
//        return(-1);       /* error, errno set by read() */
//    }
  
//    *ptr = 0;
//    return(n);
//  }


streamsize sockbuf::xsgetn (char* s, streamsize n)
{
  // More things to do if the read is incomplete
  
  return sys_read (s, n);
}

streamsize sockbuf::xsputn (const char* s, streamsize n)
{
  // More things to do if the write is incomplete

  return sys_write (s, n);
}



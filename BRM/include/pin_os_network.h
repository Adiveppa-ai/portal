/*
 *	Copyright (c) 1996, 2024, Oracle and/or its affiliates. 
 *      
 *      This material is the confidential property of Oracle Corporation or its
 *      licensors and may be used, reproduced, stored or transmitted only in
 *      accordance with a valid Oracle license or sublicense agreement.
 */

#ifndef _pin_os_network_h_
#define _pin_os_network_h_

#ifndef _PIN_TYPE_H_
  #include "pin_type.h"
#endif

typedef int pin_recv_size_t;



#if defined(__unix)

	#include <sys/types.h>
	#include <sys/time.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <sys/un.h>
	#include <netinet/tcp.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <errno.h>

    	#define pin_ntohl pin_htonl
          #ifndef PINSYS_LIB
            __inline int32 pin_htonl(int32 host_long)
	    {
              int32 return_value;
	      /* 
	       * Swap bytes.
	       */
	      ((char*)&return_value)[3] = ((char*)&host_long)[0];
	      ((char*)&return_value)[2] = ((char*)&host_long)[1];
	      ((char*)&return_value)[1] = ((char*)&host_long)[2];
	      ((char*)&return_value)[0] = ((char*)&host_long)[3];
	      return return_value;
	    }
          #endif
	#define pin_htons(v) htons(v)
 	#define pin_ntohs(v) ntohs(v)	

	#define PIN_SOCKET_FD               int
	#define pin_socket_init()           0
	#define pin_socket_perror(TEXT)     perror(TEXT)
	#define pin_socket_strerror(ERR)    strerror(ERR)
	#define pin_socket_close(FD)        close(FD)
	#define pin_socket_ioctl            ioctl
	#define pin_socket_cleanup()        0
	#define pin_socket_error            errno
	#define pin_socketpair              socketpair

#endif

#define PIN_MAXIPHOSTNAMELEN    256

struct iphostent
{
	struct in_addr addr;
	char name[PIN_MAXIPHOSTNAMELEN];
};


#if defined(__cplusplus)
extern "C" {
#endif

/** Get an IP host name from its address
  *
  * This API will do a reverse DNS lookup to get the name of an IP host from
  * its known address. If the host has multiple names, only one will be returned.
  *
  * This API is multi-thread safe.
  *
  * @param  addr    The address to look up
  * @param  ihe     The IP host entry to fill in. Both the name and address
  *                 parts are filled in.
  * @return 0 if ok, else non-zero error
  */
int pin_get_iphost_by_addr(struct in_addr addr, struct iphostent* const ihe);

/** Get an IP host address from its name
  *
  * This API will do a DNS lookup, to get the address of an IP host from its
  * known name. If the host has multiple addresses, only one will be
  * returned.
  *
  * This API is multi-thread safe.
  *
  * @param  name    The name of the host to look up
  * @param  ihe     The IP host entry to fill in. Both the name and address
  *                 parts are filled in.
  * @return 0 if ok, else non-zero error
  */
int pin_get_iphost_by_name(const char* const name, struct iphostent* const ihe);

#if defined(__cplusplus)
}
#endif


/*  PIN_DEPRECATED_STUFF
 *
 *  These things are now deprecated. They are here still in order to make the
 *  transition easier (i.e. so that the whole code base doesn't need to be
 *  swatted at once in order to update pin_os.
 *
 *  To check your code against the new stuff, define the PIN_NODEP_PIN_OS token
 *  for your build, which will force all deprecated PINOS stuff off.
 */
#ifndef PIN_NODEP_PIN_OS

		#define pin_init_socket     pin_socket_init
		#define closesocket(FD)     close(FD)
		#define ioctlsocket         ioctl

	#define getiphostbyaddr     pin_get_iphost_by_addr
	#define getiphostbyname     pin_get_iphost_by_name

	#define MAXIPHOSTNAMELEN  256

#endif

#endif


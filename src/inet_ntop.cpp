#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet6/in6.h>
#endif

#include <stdlib.h> // for NULL

#include "inet_ntop.h"

const char *inet_ntop(int af, const void *src, char *dest, size_t length)
{
	if (af != AF_INET && af != AF_INET6)
	{
		return NULL;
	}

	SOCKADDR_STORAGE address;
	DWORD address_length;

	if (af == AF_INET)
	{
		address_length = sizeof(sockaddr_in);
		sockaddr_in* ipv4_address = (sockaddr_in*)(&address);
		ipv4_address->sin_family = AF_INET;
		ipv4_address->sin_port = 0;
		memcpy(&ipv4_address->sin_addr, src, sizeof(in_addr));
	}
	else // AF_INET6
	{
		address_length = sizeof(sockaddr_in6);
		sockaddr_in6* ipv6_address = (sockaddr_in6*)(&address);
		ipv6_address->sin6_family = AF_INET6;
		ipv6_address->sin6_port = 0;
		ipv6_address->sin6_flowinfo = 0;
		// hmmm
		ipv6_address->sin6_scope_id = 0;
		memcpy(&ipv6_address->sin6_addr, src, sizeof(in6_addr));
	}

	DWORD string_length = (DWORD)(length);
	int result;
	result = WSAAddressToStringA((sockaddr*)(&address),
								 address_length, 0, dest,
								 &string_length);

	// one common reason for this to fail is that ipv6 is not installed

	return result == SOCKET_ERROR ? NULL : dest;
}
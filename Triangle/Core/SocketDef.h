#pragma once
#ifndef _TRI_SOCKET_DEF_H_
#define _TRI_SOCKET_DEF_H_

#include "SysInterfaces.h"
#include "TypeDef.h"

#if _WIN32
#include <winsock2.h> 
#include <WS2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct sockaddr_in  sockaddripv4;
    typedef struct sockaddr_in6 sockaddripv6;
#if _WIN32
    typedef SOCKET sock_n;
#else
    typedef int sock_n;
#endif

    // convert ip string to unsigned long
    EXTERN void network_ipv4_pton(const char* ipv4, struct in_addr* s);

    // convert unsigned long to ip string
    EXTERN void network_ipv4_ntop(struct in_addr const* s, char* ipv4);

    // convert host long to netwrok long, to convert bytes order
#define network_ipv4_htonl(x) htonl(x)

// convert host short to network short, to convert bytes order
#define network_ipv4_htons(x) htons(x)

// convert network long to host long, to convert bytes order
#define network_ipv4_ntohl(x) ntohl(x)

// convert network short to host short, to convert bytes order
#define netwrok_ipv4_ntohs(x) ntohs(x)

#if _WIN32
    // init the windows network resources
    EXTERN bool_n network_init();

    // dispose the windows network resources
    EXTERN void network_dispose();
#endif

#ifdef __cplusplus
}
#endif

/* for IPv4 dotted-decimal */
#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN			22
#endif // !INET_ADDRSTRLEN

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN		65
#endif // !INET_ADDRSTRLEN

#endif
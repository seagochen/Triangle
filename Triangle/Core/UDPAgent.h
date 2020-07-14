#pragma once
#ifndef _TRI_UDP_AGENT_H_
#define _TRI_UDP_AGENT_H_

#define IPV4_MULTICAST_TO_ALL       "224.0.0.1" // multicast to all machines
#define IPV4_MULTICAST_TO_ROUTERs   "224.0.0.2" // multicast to all routers
#define IPV4_MULTICAST_TO_DVMRPs    "224.0.0.4" // multicast to dvmrp routers
#define IPV4_MULTICAST_TO_OSPFs     "224.0.0.5" // multicast to ospf routers
#define IPV4_MULTICAST_TO_DRBDRs    "224.0.0.6" // multicast to DR/BDR
#define IPV4_MULTICAST_TO_STRs      "224.0.0.7" // multicast to st routers
#define IPV4_MULTICAST_TO_STHOSTs   "224.0.0.8" // multicast to st hosts
#define IPV4_MULTICAST_TO_RIP2s     "224.0.0.9" // to rip-2 routers
#define IPV4_MULTICAST_TO_EIGRPs    "224.0.0.10" // to Eigrp routers
#define IPV4_MULTICAST_TO_AGENTS    "224.0.0.11" // agents
#define IPV4_MULTICAST_TO_DHCPs     "224.0.0.12" // DHCP
#define IPV4_MULTICAST_TO_PIMs      "224.0.0.13" // PIM routers
#define IPV4_MULTICAST_TO_RSVP      "224.0.0.14" // rsvp
#define IPV4_MULTICAST_TO_CBTs      "224.0.0.15" // cbt routers
#define IPV4_MULTICAST_TO_SBM       "224.0.0.16" // bms routers
#define IPV4_MULTICAST_TO_SBMS      "224.0.0.17" // sbms routers
#define IPV4_MULTICAST_TO_VRRP      "224.0.0.18" // vrrp routers
#define IPV4_MULTICAST_TO_IGMPv3    "224.0.0.22" // IGMPv3


#define IPV4_MULTICAST_RESV1        "224.0.1.1" // reserved group 1
#define IPV4_MULTICAST_RESV2        "224.0.1.2" // reserved group 2
#define IPV4_MULTICAST_RESV3        "224.0.1.3" // reserved group 3
#define IPV4_MULTICAST_RESV4        "224.0.1.4" // reserved group 4
#define IPV4_MULTICAST_RESV5        "224.0.1.5" // reserved group 5
#define IPV4_MULTICAST_RESV6        "224.0.1.6" // reserved group 6
#define IPV4_MULTICAST_RESV7        "224.0.1.7" // reserved group 7
#define IPV4_MULTICAST_RESV8        "224.0.1.8" // reserved group 8
#define IPV4_MULTICAST_RESV9        "224.0.1.9" // reserved group 9
#define IPV4_MULTICAST_RESV10       "224.0.1.10" // reserved group 10

#include "SysInterfaces.h"
#include "SocketDef.h"
#include "TypeDef.h"

typedef struct ip_mreq castgroup;

#ifdef __cplusplus
extern "C" {
#endif    
    // create ipv4 udp socket
    EXTERN sock_n udp_ipv4_create_socket(void);

    //// socket options ////

    // set socket as broadcast
    EXTERN bool_n udp_ipv4_socket_as_broadcast(const sock_n socket);

    // set socket as nio
    EXTERN bool_n udp_ipv4_socket_as_nonblock(const sock_n socket);

    // set socket to be able to reuse
    EXTERN bool_n udp_ipv4_socket_as_reuse(const sock_n socket);

    // set socket receive buffer size
    EXTERN bool_n udp_ipv4_socket_recv_size(const sock_n socket, const size_n size);

    // set socket send buffer size
    EXTERN bool_n udp_ipv4_socket_send_size(const sock_n socket, const size_n size);


    //// address options ////

    // set address as any
    EXTERN bool_n udp_ipv4_addr_as_any(const int port, sockaddripv4* addr);

    // set address as broadcast
    EXTERN bool_n udp_ipv4_addr_as_broadcast(const int port, sockaddripv4* addr);

    // set address as loop
    EXTERN bool_n upd_ipv4_addr_as_loop(const int port, sockaddripv4* addr);

    // set address as given address and port
    EXTERN bool_n udp_ipv4_addr_as_peer(const int port, const void* ip, sockaddripv4* addr);


    //// for multicasting ///

    // join multicast group
    EXTERN castgroup* udp_ipv4_join_group(const sock_n sock, const void* ip);

    // leave multicast group
    EXTERN void udp_ipv4_leave_group(const sock_n sock, castgroup* group);

    // set socket can receive multicasting message from loop interface
    EXTERN bool_n udp_ipv4_socket_multi_loop(const sock_n socket, bool_n enable = TRUE);


    //// others ////

    // bind socket to address
    EXTERN bool_n udp_ipv4_setup_server(const sock_n socket, sockaddripv4* addr);

    // send data as datagram, returning is the length of data sent to remote
    EXTERN size_n udp_ipv4_send(const sock_n socket, sockaddripv4* addr, const void* buffer, size_n bufferlen);

    // recv data as datagram, returning is the length of data recv from remote
    EXTERN size_n udp_ipv4_recv(const sock_n socket, sockaddripv4* addr, void* buffer, size_n bufferlen);

    // dispose socket and release the resource
    EXTERN void udp_ipv4_dispose(const sock_n socket);

#ifdef __cplusplus
}
#endif

#endif
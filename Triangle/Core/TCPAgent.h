#pragma once
#ifndef _TRI_TCP_AGENT_H_
#define _TRI_TCP_AGENT_H_

#include "SocketDef.h"
#include "TypeDef.h"
#include "SysInterfaces.h"

#ifdef __cplusplus
extern "C" {
#endif
    // create ipv4 udp socket
    EXTERN sock_n tcp_ipv4_create_socket();

    // socket setup options
    EXTERN bool_n tcp_ipv4_socket_as_nonblock(sock_n socket);
    EXTERN bool_n tcp_ipv4_socket_as_reuse(sock_n socket);
    EXTERN bool_n tcp_ipv4_socket_recv_size(sock_n socket, size_n size);
    EXTERN bool_n tcp_ipv4_socket_send_size(sock_n socket, size_n size);

    // address setup options
    EXTERN bool_n tcp_ipv4_addr_as_any(const int port, sockaddripv4* addr); // set address as any
    EXTERN bool_n tcp_ipv4_addr_as_loop(const int port, sockaddripv4* addr); // set address as loop
    EXTERN bool_n tcp_ipv4_addr_as_peer(const int port, const void* ip, sockaddripv4* addr); // set address as given address and port

    // setup socket as server side and bind the address
    EXTERN bool_n tcp_ipv4_setup_server(sock_n socket, size_n maxclis, sockaddripv4* addr);

    // waiting for remote connection request
    EXTERN sock_n tcp_ipv4_waiting_connections(sock_n socket, sockaddripv4* peeraddr);

    // send connection request to remote server
    EXTERN bool_n tcp_ipv4_send_connection(sock_n socket, sockaddripv4* addr);

    // send data as datagram, returning is the length of data sent to remote
    EXTERN size_n tcp_ipv4_send(sock_n socket, const void* buffer, size_n bufferlen);

    // recv data as datagram, returning is the length of data recv from remote
    EXTERN size_n tcp_ipv4_recv(sock_n socket, void* buffer, size_n bufferlen);

    // dispose socket and release the resource
    EXTERN void tcp_ipv4_dispose(sock_n socket);

#ifdef __cplusplus
}
#endif

#endif
#include <string.h>
#include <iostream>

#if _WIN32
#include <winsock2.h> 
#include <WS2tcpip.h>
#else
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#endif

#include "TCPAgent.h"
#include "TypeDef.h"

// create ipv4 udp socket
sock_n tcp_ipv4_create_socket()
{
    sock_n socketfd = 0;
    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("create socket FALSE");
        return FALSE;
    }
    return socketfd;
};

// socket setup options
bool_n tcp_ipv4_socket_recv_size(sock_n socket, size_n size)
{
#if _WIN32
    const char opt = (char)size;
#else
    const int opt = size;
#endif

    int flag = -1;
    if ((flag = setsockopt(socket, SOL_SOCKET, SO_RCVBUF, &opt, sizeof(size))) == -1)
    {
        perror("set socket recv buf failed");
        return FALSE;
    }
    return TRUE;
};

bool_n tcp_ipv4_socket_send_size(sock_n socket, size_n size)
{
#if _WIN32
    const char opt = (char)size;
#else
    const int opt = size;
#endif

    int flag = -1;
    if ((flag = setsockopt(socket, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(size))) == -1)
    {
        perror("set socket recv buf failed");
        return FALSE;
    }
    return TRUE;
};

bool_n tcp_ipv4_socket_as_nonblock(sock_n socket)
{
#if _WIN32
    ULONG NonBlock = 1;

    if (ioctlsocket(socket, FIONBIO, &NonBlock) == SOCKET_ERROR) {
        perror("set socket as nonblock failed");
        return FALSE;
    }

    return TRUE;
#else

    int flag = fcntl(socket, F_GETFL, 0);
    if (flag < 0)
    {
        perror("get socket setting failed when calling fcntl");
        return FALSE;
    }
    flag = flag | O_NONBLOCK;
    if (fcntl(socket, F_SETFL, flag) < 0)
    {
        perror("set socket as nonblock failed when calling fcntl");
        return FALSE;
    }

    return TRUE;
#endif
};


// set address as any
bool_n tcp_ipv4_addr_as_any(int const port, sockaddripv4* addr)
{
    if (addr == NULL)
    {
        perror("sockaddripv4 couldn't be null");
        return FALSE;
    }

    // empty the struct
    memset(addr, 0, sizeof(sockaddripv4));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    addr->sin_port = htons(port);

    return TRUE;
};

// set address as loop
bool_n tcp_ipv4_addr_as_loop(int const port, sockaddripv4* addr)
{
    if (addr == NULL)
    {
        perror("sockaddripv4 couldn't be null");
        return FALSE;
    }

    // empty the struct
    memset(addr, 0, sizeof(sockaddripv4));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr->sin_port = htons(port);

    return TRUE;
};

// set address as given address and port
bool_n tcp_ipv4_addr_as_peer(int const port, const void* ip, sockaddripv4* addr)
{
    if (addr == NULL)
    {
        perror("sockaddripv4 couldn't be null");
        return FALSE;
    }

    // empty the struct
    memset(addr, 0, sizeof(sockaddripv4));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);

    // set socket address to given ip
    inet_pton(AF_INET, (const char*)ip, &(addr->sin_addr));

    return TRUE;
};

bool_n tcp_ipv4_socket_as_reuse(sock_n socket)
{
    // calling reuse option and trying to re-bind agian
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (const char*)& reuse, sizeof(reuse)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        return FALSE;
    }

    return TRUE;
};


// setup socket as server side and bind the address
bool_n tcp_ipv4_setup_server(sock_n socket, size_n maxclis, sockaddripv4* addr)
{
    if (addr == NULL)
    {
        perror("sockaddripv4 couldn't be null");
        return FALSE;
    }

    if (bind(socket, (struct sockaddr*)addr, sizeof(sockaddripv4)) == -1)
    {
        perror("bind socket to address failed");
        return FALSE;
    }

    if (listen(socket, maxclis) == -1) {
        perror("listen failed!");
        return FALSE;
    }

    return TRUE;
};

// waiting for remote connection request
sock_n tcp_ipv4_waiting_connections(sock_n socket, sockaddripv4* addr)
{
    if (addr == NULL)
    {
        sock_n sockfd = accept(socket, NULL, NULL);
        if (sockfd > 0) return sockfd;
    }
    else {
        socklen_t size = sizeof(struct sockaddr);
        sock_n sockfd = accept(socket, (struct sockaddr*)addr, &size);
        if (sockfd > 0) return sockfd;
    }

    return FALSE;
};

// send connection request to remote server
bool_n tcp_ipv4_send_connection(sock_n socket, sockaddripv4* addr)
{
    if (connect(socket, (struct sockaddr*)addr, (socklen_t)sizeof(struct sockaddr)) == -1)
    {
        perror("send connection request failed");
        return FALSE;
    }
    return TRUE;
};

// send data as datagram, returning is the length of data sent to remote
size_n tcp_ipv4_send(sock_n socket, const void* buffer, size_n bufferlen)
{
    return send(socket, (const char*)buffer, bufferlen, 0);
};

// recv data as datagram, returning is the length of data recv from remote
size_n tcp_ipv4_recv(sock_n socket, void* buffer, size_n bufferlen)
{
    return recv(socket, (char*)buffer, bufferlen, 0);
};

// dispose socket and release the resource
void tcp_ipv4_dispose(sock_n socket)
{
#if _WIN32
    closesocket(socket);
#else
    close(socket);
#endif
};

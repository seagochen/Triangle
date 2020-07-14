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

#include "UDPAgent.h"

sock_n udp_ipv4_create_socket()
{
    sock_n sock = -1;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("create ipv4 udp socket error");
        return FALSE;
    }
    return sock;
};

bool_n udp_ipv4_socket_as_broadcast(const sock_n socket)
{
#if _WIN32
    const char opt = 1;
#else
    const int opt = 1;
#endif
    int flag = -1;
    if ((flag = setsockopt(socket, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt))) == -1)
    {
        perror("permit socket to send broadcast failed");
        return FALSE;
    }
    return TRUE;
};


bool_n udp_ipv4_socket_recv_size(const sock_n socket, size_n size)
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

bool_n udp_ipv4_socket_send_size(const sock_n socket, size_n size)
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

bool_n udp_ipv4_socket_as_nonblock(const sock_n socket)
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

bool_n udp_ipv4_addr_as_any(const int port, sockaddripv4* addr)
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

bool_n udp_ipv4_addr_as_broadcast(const int port, sockaddripv4* addr)
{
    if (addr == NULL)
    {
        perror("sockaddripv4 couldn't be null");
        return FALSE;
    }

    // empty the struct
    memset(addr, 0, sizeof(sockaddripv4));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_BROADCAST);
    addr->sin_port = htons(port);

    return TRUE;
};

bool_n upd_ipv4_addr_as_loop(const int port, sockaddripv4* addr)
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

bool_n udp_ipv4_addr_as_peer(const int port, const void* ip, sockaddripv4* addr)
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

bool_n udp_ipv4_setup_server(const sock_n socket, sockaddripv4* addr)
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

    return TRUE;
};

bool_n udp_ipv4_socket_as_reuse(const sock_n socket) {

    // calling reuse option and trying to re-bind agian
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (const char*)& reuse, sizeof(reuse)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        return FALSE;
    }

#ifdef SO_REUSEPORT
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEPORT, (const char*)& reuse, sizeof(reuse)) < 0) {
        perror("setsockopt(SO_REUSEPORT) failed");
        return FALSE;
    }
#endif

    return TRUE;
}

size_n udp_ipv4_send(const sock_n socket, sockaddripv4* addr, const void* buffer, size_n bufferlen)
{
    if (addr == NULL)
    {
        perror("sockaddripv4 couldn't be null");
        return FALSE;
    }
    if (buffer == NULL)
    {
        perror("buffer couldn't be null");
        return FALSE;
    }

    return sendto(socket, (const char*)buffer, bufferlen, 0, (struct sockaddr*)addr, sizeof(struct sockaddr));
};

size_n udp_ipv4_recv(const sock_n socket, sockaddripv4* addr, void* buffer, size_n bufferlen)
{
    if (addr == NULL)
    {
        perror("sockaddripv4 couldn't be null");
        return FALSE;
    }
    if (buffer == NULL)
    {
        perror("buffer couldn't be null");
        return FALSE;
    }
    socklen_t size = sizeof(struct sockaddr);
    return recvfrom(socket, (char*)buffer, bufferlen, 0, (struct sockaddr*)addr, &size);
};

void udp_ipv4_dispose(const sock_n socket)
{
#if _WIN32
    closesocket(socket);
#else
    close(socket);
#endif
};

#include <stdlib.h>

castgroup* udp_ipv4_join_group(const sock_n sock, const void* ip)
{
    if (ip == nullptr) {
        perror("ip cannot be null");
        return nullptr;
    }

    // malloc a cast group
    castgroup* group = nullptr;
    group = (castgroup*)calloc(1, sizeof(castgroup));
    if (group == nullptr) return nullptr;

    // set group
    group->imr_interface.s_addr = network_ipv4_htonl(INADDR_ANY);
    network_ipv4_pton((const char*)ip, &group->imr_multiaddr);

    // join multicast group
#if _WIN32
    int ret = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)& group, sizeof(castgroup));
#else
    int ret = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, group, sizeof(castgroup));
#endif
    if (ret == -1)
    {
        perror("join multicast group failed");
        SAFE_FREE(group);
        return nullptr;
    }

    // return group
    return group;
};

void udp_ipv4_leave_group(const sock_n sock, castgroup* group)
{
    if (group == nullptr) {
        perror("group cannot be null");
        return;
    }

    // leave multicast group
#if _WIN32
    int ret = setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)group, sizeof(castgroup));
#else
    int ret = setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, group, sizeof(castgroup));
#endif
    if (ret == -1) {
        perror("leave multicast group failed");
        return;
    }

    // release the source of group
    SAFE_FREE(group);
};

bool_n udp_ipv4_socket_multi_loop(const sock_n socket, bool_n enable)
{
    const char opt = enable;
    if (setsockopt(socket, IPPROTO_IP, IP_MULTICAST_LOOP, &opt, sizeof(opt)) < 0) {
        perror("setsockopt(IP_MULTICAST_LOOP) failed");
        return FALSE;
    }

    return TRUE;
}

bool_n udp_ipv4_socket_multi_interface(const sock_n socket, sockaddripv4* ipv4)
{
    struct in_addr opt = ipv4->sin_addr;
#if _WIN32
    if (setsockopt(socket, IPPROTO_IP, IP_MULTICAST_IF, (char*)& opt, sizeof(struct in_addr)) < 0) {
#else
    if (setsockopt(socket, IPPROTO_IP, IP_MULTICAST_IF, &opt, sizeof(struct in_addr)) < 0) {
#endif
        perror("setsockopt(IP_MULTICAST_IF) failed");
        return FALSE;
    }
    return TRUE;    
}
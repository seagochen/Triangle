#include "SocketDef.h"

#if _WIN32
#pragma comment(lib,"ws2_32.lib") 
#endif

#if _WIN32
// init the socket and apis under windows platform
bool_n network_init()
{
    // initialize dll
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0 ? TRUE : FALSE;
}

// dispose relative resource under windows platform
void network_dispose()
{
    // release dll
    WSACleanup();
};
#endif

#include "Validators.h"
#include <iostream>

// convert ip string to unsigned long
void network_ipv4_pton(const char* ipv4, struct in_addr* s)
{
    // check
    if (reg_match_ipv4(ipv4) == FALSE) {
        std::cerr << "ipv4 is incorrect!" << std::endl;
        return;
    }

    if (s == nullptr) {
        std::cerr << "s in nullptr" << std::endl;
        return;
    }

    // converting
    inet_pton(AF_INET, ipv4, s);
};

// convert unsigned long to ip string
void network_ipv4_ntop(struct in_addr const* s, char* ipv4)
{
    if (s == nullptr || ipv4 == nullptr) {
        std::cerr << "s or ipv4 is nullptr" << std::endl;
        return;
    }

    // converting
    inet_ntop(AF_INET, s, ipv4, 16);
};
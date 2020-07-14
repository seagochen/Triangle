#ifndef _HOST_INFO_H_
#define _HOST_INFO_H_

#include "List.h"
#include "SocketDef.h"
#include "TypeDef.h"
#include "SysInterfaces.h"

typedef struct network_info {
    char str_interface[512];
	char str_address[INET_ADDRSTRLEN];
    char str_netmask[INET_ADDRSTRLEN];
    char str_gateway[INET_ADDRSTRLEN];
	char str_netcast[INET_ADDRSTRLEN];
} network_info;

#ifdef __cplusplus
extern "C" {
#endif

// get host name
EXTERN bool_n host_get_name(char * hostname_out, size_n size);

// get host available network ports and ipv4 address if possible
EXTERN bool_n host_get_ipv4_netinfo(list * out);

// cherry pick network info from list by given address or pattern
EXTERN network_info * host_filtering_by_addr(list* l, const char * regexp);

// cherry pick network info from list by given port name or pattern
EXTERN network_info * host_filtering_by_port(list* l, const char * regexp);

// cherry pick network info from list by given the ip address class type
EXTERN network_info * host_filtering_by_class(list* l, type_n type);

#ifdef __cplusplus
}
#endif

#endif

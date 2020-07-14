#if _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <memory.h>
#include <string.h>
#include <sys/types.h>

#include "HostInfo.h"
#include "Validators.h"
#include "TypeDef.h"
#include "StrUtils.h"

#if _WIN32
#include <WinSock2.h>
#include <Iphlpapi.h>
#else
#include <ifaddrs.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#if _WIN32
#pragma comment(lib,"Iphlpapi.lib")
#endif


// get host name
bool_n host_get_name(char * hostname, size_n size)
{
	// copy buffer to hostname
	int res = gethostname(hostname, size);
	if (res == -1)
	{
        std::cerr << "get host name failed" << std::endl;
		return FALSE;
	}
	return TRUE;
};


// calculate network gateway
void host_gateway(network_info & network)
{
	in_addr addr, mask, gateway;
	network_ipv4_pton(network.str_address, &addr);
	network_ipv4_pton(network.str_netmask, &mask);
	network_ipv4_pton("0.0.0.1", &gateway);

	// calculating
	addr.s_addr = (addr.s_addr & mask.s_addr) | gateway.s_addr;

	// write back
	network_ipv4_ntop(&addr, network.str_gateway);
}
   

void host_netcast(network_info& network) 
{
	in_addr addr, mask, broadcast;
	network_ipv4_pton(network.str_address, &addr);
	network_ipv4_pton(network.str_netmask, &mask);
	network_ipv4_pton("0.0.0.255", &broadcast);

	// calculating
	addr.s_addr = (addr.s_addr & mask.s_addr);
	
	if (addr.s_addr != 0x0L) {
		addr.s_addr = addr.s_addr | broadcast.s_addr;
	}

	// write back
	network_ipv4_ntop(&addr, network.str_netcast);
}

// get host available network ports and ipv4 address if possible
bool_n host_get_ipv4_netinfo(list * nodes)
{
	// create a list if ptr is empty
	if (nodes == nullptr)
	{
        std::cerr << "list canot be null" << std::endl;
		return FALSE;
	}

	// empty the list if necessary
	list_empty(nodes);

#if _WIN32

	DWORD AdapterInfoSize = 0;
	if (ERROR_BUFFER_OVERFLOW != GetAdaptersInfo(NULL, &AdapterInfoSize))
	{
        std::cerr << "get adapter info failed" << std::endl;
		return FALSE;
	}

	void* buffer = malloc(AdapterInfoSize);
	if (buffer == NULL)
	{
        std::cerr << "malloc buffer failed" << std::endl;
		return FALSE;
	}

	PIP_ADAPTER_INFO pAdapt = (PIP_ADAPTER_INFO)buffer;
	if (ERROR_SUCCESS != GetAdaptersInfo(pAdapt, &AdapterInfoSize))
	{
        std::cerr <<
            str_fmt("get adapter failed! ErrorCode: %d", GetLastError())
            << std::endl;
		free(buffer);
		return 0;
	}

	// adapters
	DWORD netCardNum = 0;
	GetNumberOfInterfaces(&netCardNum);
	std::cout << "Network adapters:" << netCardNum << std::endl;
	
	// reset the number to zero
	netCardNum = 0;

	// print out adapters info
	while (pAdapt)
	{
		//可能网卡有多IP,因此通过循环去判断
		IP_ADDR_STRING* pIpAddrString = &(pAdapt->IpAddressList);
		do
		{
			network_info* net = (network_info*)calloc(1, sizeof(network_info));
			
			if (net == nullptr) {
                std::cerr << "malloc network_info failed" << std::endl;
				break;
			}

			// append netmask
			memcpy(net->str_netmask,
				pIpAddrString->IpMask.String,
				strlen(pIpAddrString->IpMask.String));

			// append gateway
			memcpy(net->str_gateway,
				pAdapt->GatewayList.IpAddress.String,
				strlen(pAdapt->GatewayList.IpAddress.String));
	
			// append adapter interface name
			memcpy(net->str_interface,
				pAdapt->AdapterName, 
				strlen(pAdapt->AdapterName));
			
			// append ip address
			memcpy(net->str_address,
				pIpAddrString->IpAddress.String,
				strlen(pIpAddrString->IpAddress.String));

			// append broadcast address
			host_netcast(*net);

			// append info to list
			basic_node* pn = node_wrap_data(sizeof(struct network_info), 
                DATA_DEFAULT, net);

			// push node to list
			list_append(nodes, pn);

			pIpAddrString = pIpAddrString->Next;
		} while (pIpAddrString);
		pAdapt = pAdapt->Next;
	}
	

	// free resources
	if (pAdapt) { free(buffer); }

	// return results
	return list_elements(nodes) > 0;
#else   
    // create a ptr to network infos and ports
    struct ifaddrs *interfaces = nullptr;
        
    // retrieve the current interfaces - returns 0 on success
    int res = getifaddrs(&interfaces);
        
    if (res == 0)
    {
        // Loop through linked list of interfaces
        struct ifaddrs *temp_addr = interfaces;
        while(temp_addr != nullptr) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // create a node to store the data
                network_info * ptr = (network_info *) calloc(1, sizeof(struct network_info));
                    
                // append network address
                char * temp = inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr);
                memcpy(ptr->str_address, temp, strlen(temp)); 

				// append network netmask
                temp = inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_netmask)->sin_addr);
                memcpy(ptr->str_netmask, temp, strlen(temp));

				// append calculated the gateway
				host_gateway(*ptr);

				// append broadcast 
				host_netcast(*ptr);
                
                // copy interface name
                memcpy(ptr->str_interface, temp_addr->ifa_name, strlen(temp_addr->ifa_name));
                    
                // point node's ptr to network_info
                basic_node * pn = node_wrap_data(sizeof(struct network_info), 
                    DATA_DEFAULT, ptr);
                    
                // push node to list
                list_append(nodes, pn);
                    
                // increase mark
                res++;
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    
    // release resources
    free(interfaces);
    
    // return results
    return list_elements(nodes) > 0;
#endif
};
    
// check ip address
bool_n check_ipv4_addresses(list * nodes)
{
    if (nodes == nullptr)
    {
        std::cerr << "ptr(s) cannot be null or empty!" << std::endl;
        return FALSE;
    }
        
    for (basic_node * ptr = nodes; ptr != nullptr; ptr = ptr->next)
    {
        if (ptr->size > 0)
        {
            network_info * nptr = (network_info *) ptr->content;
                
            if (!reg_match_ipv4(nptr->str_address))
            {
                std::cerr << "Invalid IPv4 address format detected!" << std::endl;
                return FALSE;
            }
        }
    }
        
    return TRUE;
};

#include <iostream>
    
// cherry pick network info from list by given address or pattern
network_info * host_filtering_by_addr(list * nodes, const char * regexp)
{
    if (check_ipv4_addresses(nodes) == FALSE) 
    {
        std::cout << "invalid ipv4 address nodes" << std::endl;
        return nullptr;
    }
        
    for (basic_node * ptr = nodes; ptr != nullptr; ptr = ptr->next)
    {
        if (ptr->size > 0)
        {
            network_info * nptr = (network_info *) ptr->content;
            // std::cout << "checking the address: " << nptr->str_address << std::endl;
            if (reg_match_pattern(nptr->str_address, regexp)) return nptr;
        }
    }

    std::cout << "nothing found" << std::endl;
    return nullptr;
};
    
// cherry pick network info from list by given port name or pattern
network_info * host_filtering_by_port(list * nodes, const char * regexp)
{
    if (!check_ipv4_addresses(nodes)) {
        std::cout << "invalid ipv4 address nodes" << std::endl;
        return nullptr;
    }
        
    for (basic_node * ptr = nodes; ptr != nullptr; ptr = ptr->next)
    {
        if (ptr->size > 0)
        {
            network_info * nptr = (network_info *) ptr->content;
                
            if (reg_match_pattern(nptr->str_interface, regexp)) return nptr;
        }
    }

    std::cout << "nothing found" << std::endl;
    return nullptr;
};


network_info * host_filtering_by_class(list * nodes, type_n type)
{
    if (!check_ipv4_addresses(nodes)) 
    {
        std::cout << "invalid ipv4 address nodes" << std::endl;
        return nullptr;
    }

    for (basic_node * ptr = nodes; ptr != nullptr; ptr = ptr->next)
    {
        if (ptr->size > 0)
        {
            network_info * nptr = (network_info *) ptr->content;
            if (reg_match_ipv4_group(nptr->str_address, type)) return nptr;
        }
    }

    std::cout << "nothing found" << std::endl;
    return nullptr;
};
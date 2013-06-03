#ifndef PLC_NETINFO_H_
#define PLC_NETINFO_H_

#include <net/if.h>
#include <arpa/inet.h>

typedef struct plc_netinfo {
  char name[IFNAMSIZ];
  char address[INET6_ADDRSTRLEN];
  struct plc_netinfo *next;
} plc_netinfo_t;

int plc_netinfo(plc_netinfo_t **netinfo);

int plc_netinfo_cleanup(plc_netinfo_t **netinfo);

#endif /* PLC_NETINFO_H_ */

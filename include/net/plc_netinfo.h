#ifndef PLC_NETINFO_H_
#define PLC_NETINFO_H_

typedef struct plc_netinfo {
  char *name;
  char address[4];
  struct plc_netinfo *next;
} plc_netinfo_t;

plc_netinfo_t *plc_netinfo();

void plc_netinfo_cleanup(plc_netinfo_t *netinfo);

#endif /* PLC_NETINFO_H_ */

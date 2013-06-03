#include <stdio.h>

#include "net/plc_netinfo.h"

int main()
{
  plc_netinfo_t *netinfo = NULL;
  int ret = 0;

  printf("netinfo before %p\n", netinfo);
  ret = plc_netinfo(&netinfo);
  printf("netinfo after %p\n", netinfo);
  if (ret < 0) {
    perror("plc_netinfo: ");
  }
  printf("name is: %s\n", netinfo->next->name);
  printf("address is: %s\n", netinfo->next->address);

  return 0;
}

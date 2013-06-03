#include <stdio.h>

#include "net/plc_netinfo.h"

int main()
{
  plc_netinfo_t *netinfo = NULL;
  int ret = 0;

  ret = plc_netinfo(&netinfo);
  if (ret < 0) {
    perror("plc_netinfo: ");
  }

  plc_netinfo_t *iter = netinfo;
  while (iter != NULL) {
    printf("if: %s\n", iter->name);
    printf("addr: %s\n", iter->address);
    iter = iter->next;
  }

  return 0;
}

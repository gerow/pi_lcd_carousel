#include <stdio.h>

#include "net/plc_netinfo.h"

int main()
{
  #define ADDR_BUFFER_SIZE 32
  plc_netinfo_t addr_buffer[ADDR_BUFFER_SIZE * sizeof(plc_netinfo_t)];
  int ret = 0;

  ret = plc_netinfo(addr_buffer, sizeof addr_buffer);
  if (ret < 0) {
    perror("plc_netinfo: ");
  }

  int n = ret / sizeof *addr_buffer;

  for (int i = 0; i < n; i++) {
    printf("if: %s\n", addr_buffer[i].name);
    printf("addr: %s\n", addr_buffer[i].address);
  }

  return 0;
}

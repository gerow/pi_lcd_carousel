#include "net/plc_netinfo.h"

#include <stddef.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include <stdio.h>

char *get_ip_str(const struct sockaddr *sa, char *s, size_t maxlen)
{
  switch(sa->sa_family) {
    case AF_INET:
    inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr),
      s, maxlen);
    break;

    case AF_INET6:
    inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr),
      s, maxlen);
    break;

    default:
    strncpy(s, "Unknown AF", maxlen);
    return NULL;
  }

  return s;
}

int plc_netinfo(plc_netinfo_t **target)
{
  // Null out the target if it isn't already
  *target = NULL;

  int ret = 0;
  int netdev = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
  if (netdev < 0)
    return netdev;

  struct ifconf conf;
  // Create a buffer for up to 32 interfaces
  char buffer[32 * sizeof *conf.ifc_req];
  conf.ifc_buf = buffer;
  conf.ifc_len = sizeof buffer;

  // do the ioctl call that should fill up
  // our buffer
  ret = ioctl(netdev, SIOCGIFCONF, &conf);
  if (ret != 0) {
    goto cleanup_netdev;
  }

  plc_netinfo_t **current = target;

  for (int i = 0; i < conf.ifc_len / (sizeof *conf.ifc_req); i++) {
    // allocate a new plc_netinfo struct
    *current = malloc(sizeof(**current));
    // zero it out to be safe (also we need
    // to make sure that the next pointer is NULL)
    memset(*current, 0, sizeof **current);
    // copy the ifr_name we got from the ioctl into
    // the newly allocated name field
    struct ifreq entry;
    entry = conf.ifc_req[i];
    // copy the name over
    memcpy((*current)->name, entry.ifr_name, sizeof (*current)->name);
    // ntop the address and copy it over
    if (get_ip_str(&entry.ifr_addr,
               (*current)->address,
               sizeof (*current)->address) == NULL) {
      ret = -1;
      goto cleanup_netdev;
    }

    // make sure current now points to the next one
    current = &(*current)->next;
  }

  ret = 0;

cleanup_netdev:

  close(netdev);

  return ret;
}

int plc_netinfo_cleanup(plc_netinfo_t **netinfo)
{
  return 0;
}

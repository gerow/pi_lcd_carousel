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

  struct ifreq req;
  // Clear out req
  memset(&req, 0, sizeof req);

  plc_netinfo_t **current = target;

  // interface indices begin at 1. Why?
  // ... I'm not quite sure...
  req.ifr_ifindex = 1;
  while (ioctl(netdev, SIOCGIFNAME, &req) == 0) {
    // allocate a new plc_netinfo struct
    *current = malloc(sizeof(**current));
    // zero it out to be safe (also we need
    // to make sure that the next pointer is NULL)
    memset(*current, 0, sizeof **current);
    printf("copying info for %s\n", req.ifr_name);
    // copy the ifr_name we got from the ioctl into
    // the newly allocated name field
    memcpy((*current)->name, req.ifr_name, IFNAMSIZ);
    printf("got info for %s\n", req.ifr_name);

    ret = ioctl(netdev, SIOCGIFCONF, &req);
    if (ret < 0) {
      // oh god, just cleanup what we've allocated
      // so far and exit
      int cleanup_ret = plc_netinfo_cleanup(target);
      if (cleanup_ret < 0) {
        // :(
        return cleanup_ret;
      }
      return ret;
    }

    //if (get_ip_str(&req.ifr_addr, (*current)->address,
    //          sizeof *(*current)->address) == NULL) {
    //  return -1;
    //}

    printf("address is %s\n", (*current)->address);

    // make sure current now points to the next one
    current = &(*current)->next;
    // Conveniently, this last ioctl leaves us
    // with a valid if name in ifr_name, so let's
    // just use it!
    // allocate a new one!
    req.ifr_ifindex++;
  }

  close(netdev);

  return 0;
}

int plc_netinfo_cleanup(plc_netinfo_t **netinfo)
{
  return 0;
}

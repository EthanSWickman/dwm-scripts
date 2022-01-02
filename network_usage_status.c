#include <stdio.h>
#include <string.h>

#include "network_usage_status.h"

unsigned long long prevUpBytes = 0;
unsigned long long prevDownBytes = 0;

void SetNetworkUpInt(unsigned int* networkUpStatusInt) {
  FILE* openFile = fopen("/sys/class/net/wlan0/statistics/tx_bytes", "r");

  unsigned long long currBytes;
  
  fscanf(openFile, "%llu", &currBytes);

  *networkUpStatusInt = (currBytes - prevUpBytes)/1000000;

  prevUpBytes = currBytes;

  printf("kilobytes upload this second: %u\n", *networkUpStatusInt);

  fclose(openFile);
}

void SetNetworkDownInt(unsigned int* networkDownStatusInt) {
  FILE* openFile = fopen("/sys/class/net/wlan0/statistics/rx_bytes", "r");

  unsigned long long currBytes;
  
  fscanf(openFile, "%llu", &currBytes);

  *networkDownStatusInt = (currBytes - prevDownBytes)/1000000;

  prevDownBytes = currBytes;

  printf("kilobytes download this second: %u\n", *networkDownStatusInt);

  fclose(openFile);
}
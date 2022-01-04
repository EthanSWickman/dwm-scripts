#include <stdio.h>
#include <string.h>

#include "network_usage_status.h"

unsigned long long prevUpBytes = 0;
unsigned long long prevDownBytes = 0;

void SetNetworkUpString(char* networkUpStatusString) {
  FILE* openFile = fopen("/sys/class/net/wlan0/statistics/tx_bytes", "r");

  unsigned long long currBytes;
  
  fscanf(openFile, "%llu", &currBytes);

  fclose(openFile);

  unsigned long long newBits = (currBytes - prevUpBytes) * 8;

  printf("current upload bytes: %llu\n", currBytes-prevUpBytes);

  prevUpBytes = currBytes;

  int coefficient;
  char networkUpString[10];

  if (newBits < 1000) {
    sprintf(networkUpString, "%llu b/s", newBits);
  }
  else if (newBits < 1000000) {
    sprintf(networkUpString, "%llu kb/s", newBits / 1000);
  }
  else if (newBits < 1000000000) {
    sprintf(networkUpString, "%llu mb/s", newBits / 1000000);
  }
  else {
    sprintf(networkUpString, "%llu gb/s", newBits / 1000000000);
  }

  strcpy(networkUpStatusString, networkUpString);
}

void SetNetworkDownInt(unsigned int* networkDownStatusInt) {
  FILE* openFile = fopen("/sys/class/net/wlan0/statistics/rx_bytes", "r");

  unsigned long long currBytes;
  
  fscanf(openFile, "%llu", &currBytes);

  printf("current download bytes: %llu\n", currBytes-prevDownBytes);

  prevDownBytes = currBytes;

  fclose(openFile);
}
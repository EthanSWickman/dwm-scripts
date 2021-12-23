#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "updates_status.h"

void SetUpdatesString(char* updatesString) {
  FILE* openFile = fopen("/home/jif/monitors/update_count", "r");

  char numUpdates[3];

  fgets(numUpdates, 3, openFile);
 
  fclose(openFile);

  strcpy(updatesString, numUpdates);
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "updates_status.h"

void SetUpdatesString(char* updatesString) {
  FILE* openFile = fopen("/home/jif/monitors/update_count", "r");

  char numUpdates[6];

  fgets(numUpdates, 5, openFile);
 
  if (numUpdates[strlen(numUpdates) - 1] == '\n') {
    numUpdates[strlen(numUpdates) - 1] = '\0';
  }

  fclose(openFile);

  strcpy(updatesString, numUpdates);
}
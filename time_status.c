#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "time_status.h"

void SetTimeString(char** timeString) {
  time_t currTime; 
  time(&currTime);
  *timeString = ctime(&currTime);
}
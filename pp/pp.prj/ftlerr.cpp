// Display Fatal Error & exit
// rrvt


#include "stdafx.h"
#include "ftlerr.h"
#include <stdio.h>
#include <stdlib.h>


void fatalError(char* msg, long val) {
  if (val) printf(msg, val);
  else	   printf("%s", msg);
  exit(1);
  }

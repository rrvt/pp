// Catastrophic Failure Handler
// rrvt 3/3/98


// Required for Exception Handler -- Module is program specific.


#pragma once

#include "std.h"

 
void recordException(int excpVal);
 

void reportCatastrophicFailure(void);

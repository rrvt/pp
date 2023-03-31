// Catastrophic Failure Handler
// rrvt 3/3/98
// (C) Copyright Software Design & Engineering, Inc. -- 1998
// All rights reserved


// Required for Exception Handler -- Module is program specific.


#include "pch.h"
#include "catFailr.h"
#include "std.h"
#include <stdlib.h>


static int excpV;


void recordException(int excpVal) {excpV = excpVal;}


void reportCatastrophicFailure(void) {_tprintf(_T("Exception value: %i\n"), excpV); exit(0);}


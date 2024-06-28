// Exception Handler Module
// rrvt 1/27/98
// (C) Copyright Software Design & Engineering, Inc. -- 1998
// All rights reserved


#include "pch.h"
#include "excptn.h"
#include "catFailr.h"
#include "std.h"
#include <setjmp.h>
#include <string.h>


jmp_buf excp_jmpb;                          // Jump buffer for must be global

static jmp_buf stack[6];                    // Allow a few levels
static int     index = 0;
static int     exceptionValue;



static int excpValue = 0;                   // Exception value setting before open


// local functions




// User should never call the following functions

int  pushExcp(int excpV) {

  if (!excpV) {memcpy(stack[index], excp_jmpb, sizeof(excp_jmpb)); index++;}

  return excpV;
  }


void closeExceptionRegion(void) {
  if (index > 0) {index--; memcpy(excp_jmpb, stack[index], sizeof(excp_jmpb));}
  }


// raise an exception, set excption value

void raiseException(int excpVal) {
  exceptionValue = excpVal;

  recordException(excpVal);

  if (index > 0) {closeExceptionRegion(); longjmp(excp_jmpb, 1);}

  reportCatastrophicFailure();                          // Catastrophic failure
  }


int  getExceptionValue(void) {return exceptionValue;}

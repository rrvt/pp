// Exception Handler Module
// rrvt 1/27/98


#ifndef excptn_h
#define excptn_h



#include <setjmp.h>


extern jmp_buf excp_jmpb;


// Used to enter a block of code (in braces) in which a control C may be
// entered
//
// int excpV;                               needed for openExceptionRegion
//
//   ...
//
//   if (openExceptionRegion()) {
//     ...
//     closeExceptionRegion();
//     }
//   else {			                    
//     code to be executed only when an exception is received
//     }
//
//
//  Somewhere down in the execution sequence a function decides to raise an 
//  exception with the value 10 (probably should be defined in an enum 
//  somewhere):
//
//  f(..) {
//    ...
//    raiseException(10);
//    ...
//    }


#define openExceptionRegion() !(excpV = setjmp(excp_jmpb), pushExcp(excpV))


void closeExceptionRegion(void);	    // restore original exception state


void raiseException(int excpVal);     // raise an exception, set exception value

int  getExceptionValue(void);


// User should never call the following functions

int  pushExcp(int excpV);

#endif


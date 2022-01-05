// Display Interface


#include "stdafx.h"
#include "Display.h"


Display dsp;


void Display::name(TCchar* pname) {
int lng = _tcsclen(pname);

  if (pos + lng + 1 >= 80) {_tprintf(_T("\n\r")); pos = 0;}

  if (pos) {_tprintf(_T(" ")); pos++;}

  _tprintf(_T("%s"), pname); pos += lng;
  }


void Display::fin() {if (pos > 0) _tprintf(_T("\n"));}


// Display Interface


#pragma once


class Display {

int pos;

public:

  Display() : pos(0) {}

  void name(TCchar* pname);
  void fin();
  };


extern Display dsp;

// Date/Time Module
// rrvt 10/9/97


#pragma once
#include <atltime.h>


typedef struct tm Tm;


class After {
int year;
int month;
int day;
int hour;
int minute;
int second;

public:

  After();
 ~After() {}

  void  getTime(String& s);

  void  getDate(String& s);

  CTime toTimeT();
  };

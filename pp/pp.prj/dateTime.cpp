// Date/Time Module
// rrvt 10/9/97


#include "pch.h"
#include "dateTime.h"
#include "std.h"
#include <stdio.h>


static const long daysPerMonth[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
static const long leapYrsTo70    = 1970 / 4 - 1970 / 400;
static const long secsPerMin     = 60;
static const long secsPerHr      = 60 * 60;
static const long secsPerDay     = 24 * 60 * 60;


After::After() {
  CTime cur; cur = cur.GetCurrentTime();

  year = cur.GetYear(); month  = cur.GetMonth();  day    = cur.GetDay();
  hour = cur.GetHour(); minute = cur.GetMinute(); second = cur.GetSecond();
  }


// hh              -- current day mm = 0, ss = 0
// hh:mm           -- current day ss = 0
// hh:mm:ss        -- current day
void After::getTime(String& s) {
uint   i;
String x;

  if (s.find(_T('/'))) {getDate(s); return;}

  hour = s.stoi(i);                           x = s.substr(i+1);

  minute  = !x.isEmpty() ? x.stoi(i) : 0;     x = s.substr(i+1);

  second  = !x.isEmpty() ? x.stoi(i) : 0;
  }


//           /t dd hh           -- current month year mm = 0, ss = 0
//           /t mm/dd hh        -- current year mm = 0, ss = 0
//           /t mm/dd           -- current year hh = 0, mm = 0, ss = 0
//           /t mm/dd/yy hh     -- mm = 0, ss = 0

void After::getDate(String& s) {
uint   i;
String x;

  if (!s.find(_T('/'))) {day = s.stoi(i); return;}

                                           month  = s.stoi(i);
  if (s[i] == _T('/')) {x = s.substr(i+1); day    = x.stoi(i);}
  if (s[i] == _T('/')) {x = s.substr(i+1); year   = x.stoi(i);}

  if (year < 1970) {
    if (year > 70) year += 1900;
    else           year += 2000;
    }
  }



// Interprets year, mon, day, hour, min and sec fields of tm to form time_t

CTime After::toTimeT() {CTime t(year, month, day, hour, minute, second, 0); return t;}



#if 0
time_t t;
long   years = tm.tm_year + 1900;
long   noLeapYears;
bool   leapYear;
long   noDays;
long   timeZone;    _get_timezone(&timeZone);
int    dySvgHr;       _get_daylight(&dySvgHr);

  noLeapYears = years / 4 - years / 400 - leapYrsTo70;

  leapYear = (years % 4) == 0 && (years % 400) != 0;

  t = (years - 1970) * 365 * secsPerDay + noLeapYears * secsPerDay - (leapYear ? secsPerDay : 0);

  noDays = daysPerMonth[tm.tm_mon] + tm.tm_mday - 1;    noDays += leapYear && tm.tm_mon > 1 ? 1 : 0;

  t += noDays * secsPerDay + tm.tm_hour * secsPerHr;    t += timeZone - (dySvgHr ? secsPerHr : 0);

  t += tm.tm_min  * secsPerMin + tm.tm_sec;             return t;
#endif


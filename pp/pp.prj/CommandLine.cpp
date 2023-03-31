// Command Line class


#include "pch.h"
#include "CommandLine.h"
#include "dateTime.h"
#include "Extension.h"
#include "printer.h"


CommandLine::CommandLine(char* argv[], int n) : i(0), subdir(false), prtHdr(true) {
  for (nArgs = 0; nArgs < n; nArgs++) {ToUniCode toUni(argv[nArgs]);  args[nArgs] = toUni();}
  }




bool CommandLine::getOption() {
String& opt = args[i];

  switch (opt[1]) {
    case _T('0'): case _T('1'):
    case _T('2'): case _T('3'):
    case _T('4'): case _T('5'):
    case _T('6'): case _T('7'):
    case _T('8'): case _T('9'): file.setTab(opt[1] - _T('0')); break;

    case _T('d'): case _T('D'): printer.reqDoubleSided = true;  break;

    case _T('e'): case _T('E'): extension.setIgnoreExt(true);  break;

    case _T('s'): case _T('S'): subdir = true; break;

    case _T('n'): prtHdr = false; break;

    case _T('h'): prtHdr = true;  break;

    case _T('p'): if (i+1 < nArgs) {
                    uint ui;
                    String& nxt = args[i+1];
                    if (!nxt.isEmpty()) printer.pageno = nxt.stoi(ui);
                    if (ui >= (uint) nxt.length()) {i++; break;}
                    }
                  _tprintf(_T("Not page number %s\n"), args[i+1].str()); return false;

    case _T('t'): i += getAfterTime(args[i+1], args[i+2]); break;

    case _T('x'): examineX(); break;

    case _T('y'): examineY(); break;

    default     : _tprintf(_T("Unknown flag\n")); return false;
    }

  return true;
  }




// Interpret /t mm/dd/yy hh:mm:ss with the following defaults
//           /t hh              -- current day mm = 0, ss = 0
//           /t hh:mm           -- current day ss = 0
//           /t hh:mm:ss        -- current day
//           /t dd hh           -- current month year mm = 0, ss = 0
//           /t mm/dd hh        -- current year mm = 0, ss = 0
//           /t mm/dd           -- current year hh = 0, mm = 0, ss = 0
//           /t mm/dd/yy hh     -- mm = 0, ss = 0

int  CommandLine::getAfterTime(TCchar* arg0, TCchar* arg1) {
String   s;
String   s1;
Tchar    ch;
After    after;
int      noArgs = 0;

  if (!arg0 && !arg1) return 0;

  s  = arg0;   s1 = arg1;

  s.trim();   ch = s[0];   if (ch < _T('0') || ch > _T('9')) return 0;

  s1.trim();  ch = s1[0];

  if (ch < _T('0') || ch > _T('9')) {after.getTime(s);                    noArgs = 1;}
  else                              {after.getDate(s); after.getTime(s1); noArgs = 2;}

  CTime tm = after.toTimeT();   file.setAfterTime(tm);   return noArgs;
  }


void CommandLine::examineX() {

  if (!printer.open()) {_tprintf(_T("printer could not be opened")); return;}

  file.initialize(prtHdr);  printer.examineX();
  }


void CommandLine::examineY() {

  if (!printer.open()) {_tprintf(_T("printer could not be opened")); return;}

  file.initialize(prtHdr);  printer.examineY();
  }



void CommandLine::help() {
  _putts(_T("Version 1.17.8"));
  _putts(_T("USAGE: pp [/d] [/e] [/h] [/n] [/s] [/t [date] [time] <filename>..."));
  _putts(_T("or   : pp [/e] [/h] [/n] [/s] [/t [date] [time]] <\\*.ext> <\\*.\\*> ..."));
  _putts(_T("where: d - double side output (adjust margin odd/even pages)"));
  _putts(_T("       e - extension valid otherwise extension filtered by list in ini file"));
  _putts(_T("       h - header is output"));
  _putts(_T("       n - no header is output"));
  _putts(_T("       s - search subdirectories"));
  _putts(_T("       t - last modified date and time >= that given"));
  _putts(_T("       /t mm/dd/yy hh:mm:ss note defaults:"));
  _putts(_T("          hh          -- current day,          mm = 0, ss = 0"));
  _putts(_T("          hh:mm       -- current day,                  ss = 0"));
  _putts(_T("          hh:mm:ss    -- current day"));
  _putts(_T("          mm/dd hh    -- current year,         mm = 0, ss = 0"));
  _putts(_T("          mm/dd       -- current year, hh = 0, mm = 0, ss = 0"));
  _putts(_T("          mm/dd/yy hh -- mm = 0, ss = 0"));
  _putts(_T("       1-9 - tab translates into n spaces (default: 8)"));
  _putts(_T(""));
  _putts(_T("Wildcard characters '*' and '?' may appear in the filename and extension"));
  _putts(_T("The following extensions are acceptable as wildcards:"));
  _putts(_T("c, h, cpp, asm, txt, bat"));
  }

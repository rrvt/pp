/* Print Files
/* rrvt 11/4/90

/* Copyright (C) 1991 by Software Design & Engineering, All rights reserved.

/* Accepts file names on command line, filenames may contain wild card
/* characters.  Page breaks will occur at page eject characters and at optimal
/* double blank lines and single blank lines.  The basic idea is to fill pages
/* with text bounded by double blank lines or single blank lines.

/* Command:

/*  p [/n] [/h] [/t [date] [time]] {' ' <file_name>}

// Interpret /t mm/dd/yy hh:mm:ss with the following defaults
//           /t hh              -- current day mm = 0, ss = 0
//           /t hh:mm           -- current day ss = 0
//           /t hh:mm:ss        -- current day
//           /t dd hh           -- current month year mm = 0, ss = 0
//           /t mm/dd hh        -- current year mm = 0, ss = 0
//           /t mm/dd           -- current year hh = 0, mm = 0, ss = 0
//           /t mm/dd/yy hh     -- mm = 0, ss = 0
//           /t                 -- no change
// where file name after date and/or time must begin with a non-digit.

/* A header is placed on each page containing the file name, file creation date
/* and time, and page number.           */


#include "pch.h"
#include "CommandLine.h"
#include "Display.h"
#include "Extension.h"
#include "File.h"
#include "FilePaths.h"
#include "filename.h"
#include "filesrch.h"
#include "iniFile.h"
#include "printer.h"


// Global

IniFile iniFile;



static int no_files;


// Local Functions

static bool printFile(String& path, bool prtHdr);


int main(int argc, char* argv[], char* env[]) {
CommandLine commandLine(argv, argc);
String*     p;
int         i;
String      tok;

  if (argc < 2) {commandLine.help(); return 0;}

  if (iniFile.getAppDataPath(commandLine.startLoop()->str()).isEmpty())
                            {_tprintf(_T("Unable to open/create initialization file.")); return 0;}

  for (p = commandLine.startLoop(), i = 0; p; p = commandLine.nextArg(), i++) {
    String& fileName = *p;

    if (!i) {extension.initialize();  continue;}

    if (commandLine.isOption()) {if (!commandLine.getOption()) break; continue;}

    String  path     = fileName;
    int     pos      = path.find_last_of(pathSepChar);
    String  pFile;

    if (pos > 0) {path.resize(pos); fileName = fileName.substr(pos+1);}
    else         path = _T(".");

    if (fileName.find_last_of(_T('.')) == string::npos) fileName += _T(".*");

    if (commandLine.srchSubDirs()) {

      FilePaths filePaths;
      FPsIter   iter(filePaths);
      String*   pth;

      if (filePaths.findFiles(path, fileName)) {

        for (pth = iter(); pth; pth = iter++) {
          if (!printFile(*pth, commandLine.prtHdr)) return -1;
          }
        }
      }
    else {
      FileSrch fileSrch;

      if (fileSrch.findFiles(path, fileName)) {

        while (fileSrch.getName(pFile)) if (!printFile(pFile, commandLine.prtHdr)) return -1;
        }
      }
    }

  dsp.fin();   printer.close();   return 0;
  }


bool printFile(String& path, bool prtHdr) {
  if (!extension.isLegal(path)) return true;

    if (!printer.open()) {_tprintf(_T("printer could not be opened")); return false;}

    file.initialize(prtHdr);

    if (!file.print(path)) {_tprintf(file.errMsg); return false;}

    no_files++; printer.pageno = 1;

    return true;
  }




#if 0
/* display name of file on display  */

static int pos = 0;

void display_name(TCchar* pname) {
int lng = _tcsclen(pname);

  if (pos + lng + 1 >= 80) {_tprintf(_T("\n\r")); pos = 0;}

  if (pos) {_tprintf(_T(" ")); pos++;}

  _tprintf(_T("%s"), pname); pos += lng;
  }


void fin_display_name(void) {if (pos > 0) _tprintf(_T("\n"));}
#endif

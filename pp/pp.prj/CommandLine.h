// Command Line class


#pragma once
#include "Expandable.h"
#include "File.h"


class CommandLine {
int                    i;
int                    nArgs;
Expandable <String, 8> args;
bool                   subdir;

public:

bool prtHdr;

  CommandLine(char* argv[], int n);
 ~CommandLine() {}

  bool    isOption() {Tchar ch = args[i][0]; return ch == _T('-') || ch == _T('/');}
  bool    getOption();

  String& getFileName() {return args[i];}
  bool    srchSubDirs() {return subdir;}

  int     getAfterTime(TCchar* arg0, TCchar* arg1);

  void    help();

  String* startLoop() {i = -1; return nextArg();}
  String* nextArg()   {i++; return i < nArgs ? &args[i] : 0;}

private:

  void examineX();
  void examineY();
  };


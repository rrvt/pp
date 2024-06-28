// File class


#pragma once
#include "blkdpo.h"
#include "fileIO.h"


class File {
bool      initialized;
Blkdpo    blkdpo;
FileIO    fileIO;

bool      printHdr;
int       offset;                         // offset to character
int       pos;                            // End of tab when non-zero
int       tabPos;                         // Tab offset
bool      ffSeen;                         // form feed seen not on margin...
CTime     afterTime;

public:

String errMsg;

  File();
 ~File() {}

  void initialize(bool prtHdr);

  void setTab(int tabDelta) {tabPos = tabDelta <= 0 ? 8 : tabDelta;}
  void setAfterTime(CTime& tm)         {afterTime = tm;}

  bool  print(TCchar* name);

private:

  bool getChar(Tchar& ch);             // Process tab characters
  };


extern File file;


// File class


#include "pch.h"
#include "File.h"
#include "DevBase.h"
#include "filename.h"
#include "printer.h"


File      file;


File::File() : initialized(false), offset(0), pos(0), tabPos(8), ffSeen(false) {}


void File::initialize(bool prtHdr) {

  if (initialized) return;

  printHdr = prtHdr;

  blkdpo.init(printer.noLinesPerPage(), printer.noCharsPerLine());

  initialized = true; return;
  }


bool File::print(TCchar* name) {
String nm = name;
Tchar  ch;
Tchar  lastCh = 0;
String fn;
CTime  modTime;
String mod;

  errMsg.clear();

  if (!fileIO.open(nm, FileIO::Read))
                   {errMsg.format(_T("Open file failed: %s\n"), fileIO.getLastError()); return false;}
  fn = removePath(name);

  if (fileIO.getModifiedTime(modTime) && modTime >= afterTime) {

    mod = modTime.Format(_T("%H:%M:%S %a %b %d, %y"));

    if (!printHdr) blkdpo.disable_header();
    else           blkdpo.set_header(fn, mod);   // FIX-----*******

    while (getChar(ch)) {blkdpo.put(ch); lastCh = ch;}

    if (lastCh != _T('\n')) blkdpo.put(_T('\n'));

    blkdpo.close();
    }

  fileIO.close(); return true;
  }





typedef enum {nil, ascii, tab, eol, cr, ff, other} Character_Class;

static Character_Class character_class_table[] = {
  other, other, other, other, other, other, other, other,  /* 00 - 07 */
  other, tab,   eol,   other, ff,    cr,    other, other,  /* 08 - 15 */
  other, other, other, other, other, other, other, other,  /* 16 - 23 */
  other, other, other, other, other, other, other, other,  /* 24 - 31 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, ascii,  /* 32 - 39 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, ascii,  /* 40 - 47 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, ascii,  /* 48 - 55 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, ascii,  /* 56 - 63 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, ascii,  /* 64 - 71 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, ascii,  /* 72 - 79 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, ascii,  /* 80 - 87 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, ascii,  /* 88 - 95 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, ascii,  /* 96 -103 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, ascii,  /*104 -111 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, ascii,  /*112 -119 */
  ascii, ascii, ascii, ascii, ascii, ascii, ascii, other,  /*120 -127 */
  other, other, other, other, other, other, other, other,  /*128  */
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,  /*   Safety  */
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,
  other, other, other, other, other, other, other, other,  /*    -255 */
  };


// Process tab characters

bool File::getChar(Tchar& ch) {

  if (ffSeen) {ch = _T('\f'); ffSeen = false; return true;}

  if (pos) {if (++offset >= pos) pos = 0; ch = _T(' '); return true;}

  loop {

    if (!fileIO.read(ch)) return false;

    switch (character_class_table[ch]) {

      case tab  : pos = (offset + tabPos) / tabPos; pos = pos * tabPos;
                  offset++; if (offset >= pos) pos = 0; ch = _T(' '); return true;

      case eol  : offset = 0; return true;

      case cr   : continue;

      case ff   : if (offset > 0) {ffSeen = true; offset = 0; ch = _T('\n'); return true;}
                  return true;

      case ascii:
      default   : offset++; return true;
      }
    }
  }

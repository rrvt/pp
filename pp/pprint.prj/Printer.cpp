// Printer Interface


#include "pch.h"
#include "Printer.h"
#include "CalibrateXdlg.h"
#include "CalibrateYdlg.h"
#include "iniFile.h"


Printer printer;


void Printer::saveCurParams() {
  if (name.isEmpty()) return;

  iniFile.writeInt(name, CharsPerLine,  charsPerLine);
  iniFile.writeInt(name, XOffsetOddPg,  xOffsetOdd  );
  iniFile.writeInt(name, XOffsetEvenPg, xOffsetEven );
  iniFile.writeInt(name, XTweak,        xTweak      );

  iniFile.writeInt(name, LinesPerPage, linesPerPage);
  iniFile.writeInt(name, YOffset,      yTweak);
  iniFile.writeInt(name, YTweak,       yOffset);
  }


void Printer::saveHorizParams(CalibrateXdlg& dlg) {
String s;
uint   i;

  name = dlg.name;
  s = dlg.charPerLine;  charsPerLine = s.stoi(i);  iniFile.writeInt(name, CharsPerLine,  charsPerLine);
  s = dlg.oddPgOffset;  xOffsetOdd   = s.stoi(i);  iniFile.writeInt(name, XOffsetOddPg,  xOffsetOdd  );
  s = dlg.evenPgOffset; xOffsetEven  = s.stoi(i);  iniFile.writeInt(name, XOffsetEvenPg, xOffsetEven );
  s = dlg.tweak;        xTweak       = s.stoi(i);  iniFile.writeInt(name, XTweak,        xTweak      );
  }


void Printer::saveVertParams(CalibrateYdlg& dlg) {
String  s;
uint    i;

  name = dlg.name;
  s = dlg.nLines;   linesPerPage = s.stoi(i);    iniFile.writeInt(name, LinesPerPage, linesPerPage);
  s = dlg.yOffset;  yOffset      = s.stoi(i);    iniFile.writeInt(name, YTweak,       yOffset);
  s = dlg.yTweak;   yTweak       = s.stoi(i);    iniFile.writeInt(name, YOffset,      yTweak);
  }




#if 0
void Printer::writeVertParam(CString& nLinesPerPg, CString& offset, CString& tweak) {
TCchar* dev = name;
String  s;
uint    i;

  s = nLinesPerPg;   linesPerPage = s.stoi(i);    iniFile.writeInt(dev, LinesPerPage, linesPerPage);
  s = tweak;         yOffset      = s.stoi(i);    iniFile.writeInt(dev, YTweak,       yOffset);
  s = offset;        yTweak       = s.stoi(i);    iniFile.writeInt(dev, YOffset,      yTweak);
  }
#endif
#if 0
void Printer::writeVertParam(CString& nLinesPerPg, CString& offset, CString& tweak) {
TCchar* dev = name;
String  s;
uint    i;

  s = nLinesPerPg;   linesPerPage = s.stoi(i);    iniFile.writeInt(dev, LinesPerPage, linesPerPage);
  s = tweak;         yOffset      = s.stoi(i);    iniFile.writeInt(dev, YTweak,       yOffset);
  s = offset;        yTweak       = s.stoi(i);    iniFile.writeInt(dev, YOffset,      yTweak);
  }
#endif


#if 0
void Printer::readHorizParam(CString& charPerLine, CString& oddPgOffset,
                                                                 CString& evenPgOffset, CString& tweak) {
TCchar* dev = name;
int     n;
String  s;

  n = iniFile.readInt(dev, CharsPerLine, 80);  s = n;  charPerLine = s;
  n = iniFile.readInt(dev, XOffsetOddPg,  0);  s = n;  oddPgOffset  = s;
  n = iniFile.readInt(dev, XOffsetEvenPg, 0);  s = n;  evenPgOffset = s;
  n = iniFile.readInt(dev, XTweak,        0);  s = n;  tweak = s;
  }
#endif
#if 0
void Printer::readVertParam( CString& nLinesPerPg, CString& offset, CString& tweak) {
TCchar* dev = name;
int     n;
String  s;

  n =  iniFile.readInt(dev, LinesPerPage, 63);  s = n;  nLinesPerPg = s;
  n =  iniFile.readInt(dev, YOffset,       0);  s = n;  offset      = s;
  n =  iniFile.readInt(dev, YTweak,        0);  s = n;  tweak       = s;
  }
#endif


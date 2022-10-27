/* print files
 * rrvt 11/4/90

 * Copyright (C) 1991 by Software Design & Engineering, All rights reserved.

 */

// This version is written for Windows NT DOS box.


#include "stdafx.h"
#include "iniFile.h"
#include "blkdpo.h"
#include "printer.h"
#include <Winspool.h>


Printer printer;


Printer::Printer() : opened(false),
                     hdcPrn(0),
                     info({sizeof(DOCINFO), _T("Text Files")}),
                     oldFont(0),
                     logFont({0}),
                     noChLine(0),
                     xPage(0),
                     yPage(0),
                     charsPerLine(0),
                     xTweak(0),
                     doubleSided(false),
                     xOffsetOdd(0),
                     xOffsetEven(0),
                     xOffset(0),
                     pixelsPerInch(0),
                     linesPerPage(0),
                     yTweak(0),
                     yOffset(0),
                     height(0),
                     lineX(0),
                     reqDoubleSided(false),
                     pageno(1)
                     {}


bool Printer::open() {
BYTE            info9[2048];
DWORD           noInfo9 = noElements(info9);
DWORD           needed;
PRINTER_INFO_9* pInfo;
DEVMODE*        pDevMode;
long            width;
HGDIOBJ         hFont;
DWORD           err;
HANDLE          prtHndl;

  if (opened) return true;

  if (name.isEmpty() && !getDefaultPrinter()) return false;

  hdcPrn = 0;

  if (OpenPrinter((Tchar*) name.str(), &prtHndl, 0)) {

    if (!GetPrinter(prtHndl, 9, info9, noInfo9, &needed)) err = GetLastError();

    pInfo = (PRINTER_INFO_9*) info9;
    pDevMode = pInfo->pDevMode;

    if (pDevMode) {
      doubleSided   = (pDevMode->dmDuplex != DMDUP_SIMPLEX) & reqDoubleSided;    // Actually do it?
      pixelsPerInch = pDevMode->dmPrintQuality;
      }
    else doubleSided = reqDoubleSided;                                           // Default to request

    ClosePrinter(prtHndl);
    }

  hdcPrn = CreateDC(_T("winspool"), name, 0, 0); if (!hdcPrn) return false;

  xPage = GetDeviceCaps(hdcPrn, HORZRES);
  yPage = GetDeviceCaps(hdcPrn, VERTRES);

  getPrinterParms();

  noChLine = charsPerLine;

  height = (yPage - yTweak) / linesPerPage;     if (height * linesPerPage >= yPage) height--;

  width  = (xPage - xTweak) / charsPerLine;     if (width * charsPerLine  >= xPage) width--;

  logFont.lfHeight         = height;
  logFont.lfWidth          = width;
  logFont.lfEscapement     = 0;
  logFont.lfOrientation    = 0;
  logFont.lfWeight         = FW_NORMAL;
  logFont.lfItalic         = 0;
  logFont.lfUnderline      = 0;
  logFont.lfStrikeOut      = 0;
  logFont.lfCharSet        = ANSI_CHARSET;
  logFont.lfOutPrecision   = OUT_TT_ONLY_PRECIS;
  logFont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
  logFont.lfQuality        = DEFAULT_QUALITY;
  logFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;

  _tcscpy_s(logFont.lfFaceName, noElements(logFont.lfFaceName), font);

  hFont = CreateFontIndirect(&logFont);

  if (hFont) oldFont = SelectObject(hdcPrn, hFont);

  opened = StartDoc(hdcPrn, &info) > 0;  return opened;
  }


// Sets printer if returns true

bool Printer::getDefaultPrinter() {
Tchar  buf[1024];
DWORD n = sizeof(buf);

  if (!GetDefaultPrinter(buf, &n)) return false;
  name = buf; return true;
  }



bool Printer::startPrinter() {return StartDoc(hdcPrn, &info) > 0;}



void Printer::close(void) {

  if (!opened) return;

  EndDoc(hdcPrn); SelectObject(hdcPrn, oldFont); DeleteDC(hdcPrn); opened = false;
  }


// Look at various configurations

void Printer::examineX(void) {
int     width = logFont.lfWidth;
int     w;
int     i;
HFONT   hFont;
HGDIOBJ prevFont;

  xOffset = xOffsetOdd;

  createPort(); print10(width);

  for (i = 0; i < 9; i++) {

    w = width + i - 4;

    logFont.lfWidth = w;

    hFont = CreateFontIndirect(&logFont);

    if (hFont) prevFont = SelectObject(hdcPrn, hFont);

    print10(w);

    DeleteObject(SelectObject(hdcPrn, GetStockObject(SYSTEM_FONT)));
    }

  closePort();
  }


void Printer::print10(int w) {
String buf;
int    i;
int    lng = noChLine / 10;
int    tw;

  tw = xPage - w * charsPerLine;

  buf.format(_T("Width: %i, xTweak: %i, xPage: %i, xOffset %i, Pixels/Inch: %i"),
                                                              w, tw, xPage, xOffset, pixelsPerInch);
  printLine(buf);

  buf.clear();   for (i = 0; i < lng; i++) buf += _T("1234567890");

  for (i = 0; i < noChLine % 10; i++) buf += buf[i];

  printLine(buf);

  buf.clear();   for (i = 0; i < noChLine; i++) buf += _T('M');

  printLine(buf);
  }


void Printer::examineY(void) {
int     h;
int     yTLmt = yTweak;             if (yTLmt < 5  || 5 < yTLmt) yTLmt = 5;
int     i;
HGDIOBJ hFont;
HGDIOBJ prevFont;

  h = yPage / linesPerPage;     if (h * linesPerPage >= yPage) h--;

  for (i = 0; i < yTLmt; i++) {

    logFont.lfHeight = height = h - i;   if (!height) break;

    createPort();

    hFont = CreateFontIndirect(&logFont);

    if (hFont) prevFont = SelectObject(hdcPrn, hFont);

    printVert(height, i);

    DeleteObject(SelectObject(hdcPrn, GetStockObject(SYSTEM_FONT)));

    closePort();
    }
  }


void Printer::printVert(int height, int yTwk) {
int    i;
String buf;
int    noLPg  = yPage / height;
int    tw     = yPage - height * linesPerPage;

  buf.format(_T(" 1   yPage: %i, initial ln/pg: %i initial height: %i, "),
                                                                yPage, linesPerPage, yPage/linesPerPage);
  printLine(buf);
  buf.format(_T(" 2   yTweak: %i, h: %i, lines/page: %i, yOffset: %i"), tw, height, noLPg, yOffset);
  printLine(buf);

  for (i = 2; i < noLPg + 5; i++) {buf.format(_T("%2i"), i+1); printLine(buf);}
  }





static TCchar* CharsPerLine  = _T("CharsPerLine");
static TCchar* XOffsetOddPg  = _T("X-OffsetOddPg");      // adjust left margin of odd pages
static TCchar* XOffsetEvenPg = _T("X-OffsetEvenPg");
static TCchar* XTweak        = _T("X-Tweak");            // moves the text at right margin to the left
static TCchar* LinesPerPage  = _T("LinesPerPage");
static TCchar* YOffset       = _T("Y-Offset");           // adjusts the top margin
static TCchar* YTweak        = _T("Y-Tweak");            // moves the text at bottom up
static TCchar* Font          = _T("Font");


void Printer::getPrinterParms() {
TCchar* dev = name;
TCchar* q   = _tcsrchr(name.str(), _T('\\'));   if (q) dev = q + 1;

  if (!iniFile.readString(dev, Font, font)) {
    _tprintf(_T("\nIniFile, %s,\ndid not contain [%s], setting to defaults\n"),
                                                                              iniFile.path().str(), dev);
    iniFile.writeString(dev, Font, _T("Courier New"));
    iniFile.writeInt(dev,    CharsPerLine,  80);
    iniFile.writeInt(dev,    XOffsetOddPg,   0);
    iniFile.writeInt(dev,    XOffsetEvenPg,  0);
    iniFile.writeInt(dev,    XTweak,         0);

    iniFile.writeInt(dev,    LinesPerPage,  63);
    iniFile.writeInt(dev,    YOffset,        0);
    iniFile.writeInt(dev,    YTweak,         0);
    }

  charsPerLine =  iniFile.readInt(dev, CharsPerLine, 80);
  xOffsetOdd   =  iniFile.readInt(dev, XOffsetOddPg,  0);
  xOffsetEven  =  iniFile.readInt(dev, XOffsetEvenPg, 0);
  xTweak       =  iniFile.readInt(dev, XTweak,        0);

  linesPerPage =  iniFile.readInt(dev, LinesPerPage, 63);
  yOffset      =  iniFile.readInt(dev, YOffset,       0);
  yTweak       =  iniFile.readInt(dev, YTweak,        0);
  }


void Printer::readHorizParam(CString& nCharPerLine, CString& oddPgOffset,
                                                                 CString& evenPgOffset, CString& tweak) {
TCchar* dev = name;
int     n;
String  s;

  n = iniFile.readInt(dev, CharsPerLine, 80);  s = n;  nCharPerLine = s;
  n = iniFile.readInt(dev, XOffsetOddPg,  0);  s = n;  oddPgOffset  = s;
  n = iniFile.readInt(dev, XOffsetEvenPg, 0);  s = n;  evenPgOffset = s;
  n = iniFile.readInt(dev, XTweak,        0);  s = n;  tweak = s;

  }



void Printer::writeHorizParam(CString& nCharPerLine, CString& oddPgOffset,
                                                                 CString& evenPgOffset, CString& tweak) {
TCchar* dev = name;
String  s;
uint    i;

  s = nCharPerLine; iniFile.writeInt(dev, CharsPerLine,  s.stoi(i));
  s = oddPgOffset;  iniFile.writeInt(dev, XOffsetOddPg,  s.stoi(i));
  s = evenPgOffset; iniFile.writeInt(dev, XOffsetEvenPg, s.stoi(i));
  s = tweak;        iniFile.writeInt(dev, XTweak,        s.stoi(i));
  }


void Printer::readVertParam( CString& nLinesPerPg, CString& offset, CString& tweak) {
TCchar* dev = name;
int     n;
String  s;

  n =  iniFile.readInt(dev, LinesPerPage, 63);  s = n;  nLinesPerPg = s;
  n =  iniFile.readInt(dev, YOffset,       0);  s = n;  offset      = s;
  n =  iniFile.readInt(dev, YTweak,        0);  s = n;  tweak       = s;
  }


void Printer::writeVertParam(CString& nLinesPerPg, CString& offset, CString& tweak) {
TCchar* dev = name;
String  s;
uint    i;

  s = nLinesPerPg; iniFile.writeInt(dev, LinesPerPage, s.stoi(i));
  s = offset;      iniFile.writeInt(dev, YOffset,      s.stoi(i));
  s = tweak;       iniFile.writeInt(dev, YTweak,       s.stoi(i));
  }



bool Printer::printPage(Blkdpo* blkdpo) {
int rslt;

  if (!blkdpo->isPage()) return 0;

  xOffset = doubleSided && (pageno & 1) == 0 ? xOffsetEven : xOffsetOdd;

  createPort(); rslt = blkdpo->output_lines(pageno); pageno++; closePort(); return rslt != 0;
  }


void Printer::createPort(void) {
SIZE  orgSize;
SIZE  portSize;
POINT orgPt;

  StartPage(hdcPrn); SaveDC(hdcPrn);

  SetMapMode(hdcPrn, MM_TEXT);
  SetWindowExtEx(  hdcPrn, 2*xPage, 2*yPage, &orgSize);
  SetViewportExtEx(hdcPrn,   xPage,  -yPage, &portSize);
  SetViewportOrgEx(hdcPrn,       0,       0, &orgPt);

  lineX = 0;
  }


void Printer::printLine(TCchar* line)
                              {TextOut(hdcPrn, xOffset, lineX++ * height + yOffset, line, lstrlen(line));}


void Printer::closePort(void) {RestoreDC(hdcPrn, -1); EndPage(hdcPrn);}

/* print files
 * rrvt 11/4/90

 * Copyright (C) 1991 by Software Design & Engineering, All rights reserved.

 */

// This version is written for Windows NT DOS box.


#include "pch.h"
#include "iniFile.h"
#include "blkdpo.h"
#include "PrinterBase.h"
#include <Winspool.h>



TCchar* CharsPerLine    = _T("CharsPerLine");
TCchar* XOffsetOddPg    = _T("X-OffsetOddPg");      // adjust left margin of odd pages
TCchar* XOffsetEvenPg   = _T("X-OffsetEvenPg");
TCchar* XTweak          = _T("X-Tweak");            // moves the text at right margin to the left
TCchar* LinesPerPage    = _T("LinesPerPage");
TCchar* YOffset         = _T("Y-Offset");           // adjusts the top margin
TCchar* YTweak          = _T("Y-Tweak");            // moves the text at bottom up

static TCchar* CurPrntr = _T("Current");

static TCchar* Font     = _T("Courier New");


PrinterBase::PrinterBase() : opened(false),
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
                     linesPerPage(0),
                     yTweak(0),
                     yOffset(0),
                     height(0),
                     yPos(0),
                     reqDoubleSided(false),
                     pageno(1)
                     {}


void PrinterBase::initCurPrntr() {String prntr;   if (getCurPrntr(prntr)) initialize(prntr);}


bool PrinterBase::getCurPrntr(String& prntr)
                              {iniFile.read(_T("Globals"), CurPrntr, prntr);   return !prntr.isEmpty();}



void PrinterBase::initialize(TCchar* nam) {

  name = nam;   if (name.isEmpty()) return;

  charsPerLine = iniFile.readInt(name, CharsPerLine, 80);
  xOffsetOdd   = iniFile.readInt(name, XOffsetOddPg,  0);
  xOffsetEven  = iniFile.readInt(name, XOffsetEvenPg, 0);
  xTweak       = iniFile.readInt(name, XTweak,        0);

  linesPerPage = iniFile.readInt(name, LinesPerPage, 63);
  yOffset      = iniFile.readInt(name, YTweak,        0);
  yTweak       = iniFile.readInt(name, YOffset,       0);
  }


// Save Current printer

void PrinterBase::saveCurPrntr()
                              {if (!name.isEmpty()) iniFile.write(_T("Globals"), CurPrntr, name);}



bool PrinterBase::setupPrinter(bool dblSdd) {
CPrintDialogEx dlg;
String         prtName;

  reqDoubleSided = dblSdd;

  dlg.DoModal();

  prtName = dlg.GetDeviceName();     if (prtName.isEmpty()) return false;

  initialize(prtName);   return true;
  }


bool PrinterBase::selectPrinter() {
PRINTDLG printDlgInfo        = {sizeof(PRINTDLG)};
HDC      printerDC           = 0;
LPWSTR   localPrinterName    = 0;
PDEVMODE returnedDevmode     = 0;
PDEVMODE localDevmode        = 0;
int      localNumberOfCopies = 0;

  // Initialize the print dialog box's data structure.

//  printDlgInfo.lStructSize = sizeof(PRINTDLG);

  printDlgInfo.Flags = PD_RETURNDC |            // Return a printer device context.
                       PD_HIDEPRINTTOFILE |     // Don't allow separate print to file.
                       PD_DISABLEPRINTTOFILE |  // Remove these flags to support this feature.
                       PD_NOSELECTION;          // Don't allow selecting individual document pages.


  if (!PrintDlg(&printDlgInfo)) return false; // Display the printer dialog and retrieve the
                                              // printer DC.  The user clicked OK so the printer
                                              // dialog box data structure was returned with the
                                              // user's selections.  Copy the relevant data from
                                              // the data structure and save them to a local data
                                              // structure.

  printerDC = printDlgInfo.hDC;             // Get the HDC of the selected printer

                                            // In this example, the DEVMODE structure returned by
                                            // the printer dialog box is copied to a local memory
                                            // block and a pointer to the printer name that is
                                            // stored in the copied DEVMODE structure is saved.

  //  Lock the handle to get a pointer to the DEVMODE structure.
  returnedDevmode = (PDEVMODE) GlobalLock(printDlgInfo.hDevMode);

  localDevmode = (LPDEVMODE) HeapAlloc(GetProcessHeap(),
                            HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, returnedDevmode->dmSize);
  if (localDevmode) {

    memcpy((LPVOID) localDevmode, (LPVOID) returnedDevmode, returnedDevmode->dmSize);

    localPrinterName = localDevmode->dmDeviceName;  // Save the printer name from the DEVMODE
                                                    // structure.  This is done here just to
                                                    // illustrate how to access the name field.
                                                    // The printer name can also be accessed  by
                                                    // referring to the dmDeviceName in the local
                                                    // copy of the DEVMODE structure.

    localNumberOfCopies = printDlgInfo.nCopies;     // Save the number of copies as entered by the
    }                                               // user

  else {
    return false;                                   // Unable to allocate a new structure so leave
    }                                               // the pointer as NULL to indicate that it's
                                                    // empty.

  // Free the DEVMODE structure returned by the print dialog box.
  if (printDlgInfo.hDevMode) GlobalFree(printDlgInfo.hDevMode);

  return true;
  }


bool PrinterBase::open() {
BYTE            info9[2048];
DWORD           noInfo9 = noElements(info9);
DWORD           needed;
PRINTER_INFO_9* pInfo;
DEVMODE*        devMode;
HGDIOBJ         hFont;
DWORD           err;
HANDLE          prtHndl;

  if (opened) return true;

  if (name.isEmpty()) {
    String newPrntr;

    if (!getCurPrntr(newPrntr) && !getDefaultPrinter(newPrntr)) return false;

    initialize(newPrntr);
    }

  hdcPrn = 0;

  if (OpenPrinter((Tchar*) name.str(), &prtHndl, 0)) {

    if (!GetPrinter(prtHndl, 9, info9, noInfo9, &needed)) err = GetLastError();

    pInfo   = (PRINTER_INFO_9*) info9;
    devMode = pInfo->pDevMode;

    if (devMode) {
      doubleSided   = (devMode->dmDuplex != DMDUP_SIMPLEX) & reqDoubleSided; // Actually do it?
      }
    else doubleSided = reqDoubleSided;                                       // Default to request

    ClosePrinter(prtHndl);
    }

  hdcPrn = CreateDC(_T("winspool"), name, 0, 0); if (!hdcPrn) return false;

  xPage = GetDeviceCaps(hdcPrn, HORZRES);
  yPage = GetDeviceCaps(hdcPrn, VERTRES);

  noChLine = charsPerLine;

  height = getNomHeight();

  logFont.lfHeight         = getNomHeight() - yTweak;
  logFont.lfWidth          = getNomWidth()  - xTweak;
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

  _tcscpy_s(logFont.lfFaceName, noElements(logFont.lfFaceName), Font);

  hFont = CreateFontIndirect(&logFont);

  if (hFont) oldFont = SelectObject(hdcPrn, hFont);

  opened = StartDoc(hdcPrn, &info) > 0;  return opened;
  }


// Sets printer if returns true

bool PrinterBase::getDefaultPrinter(String& newPrntr) {
Tchar buf[1024];
DWORD n = noElements(buf);

  if (!GetDefaultPrinter(buf, &n)) return false;

  newPrntr = buf; return true;
  }



void PrinterBase::close(void) {

  if (!opened) return;

  EndDoc(hdcPrn); SelectObject(hdcPrn, oldFont); DeleteDC(hdcPrn); opened = false;
  }


// Look at various configurations

void PrinterBase::examineX(void) {
int width = getNomWidth();
int stk   = doubleSided;   doubleSided = true;

  createPort();

    xOffset = getXoffset(1);       printGrp(width);
    xOffset = getXoffset(1) * 2;   printGrp(width);

  closePort();

  createPort();

    xOffset = getXoffset(2);       printGrp(width);
    xOffset = getXoffset(2) * 2;   printGrp(width);

  closePort();

  doubleSided = stk;
  }


void PrinterBase::printGrp(int width)
                     {int i;   print10(xTweak);   for (i = 0; i < 9; i++) print10(xTweak + i - 4);}


void PrinterBase::print10(int tweak) {
int     width    = getNomWidth();
int     height   = getNomHeight();
HGDIOBJ prevFont = insertFont(width - tweak, height);
int     w        = logFont.lfWidth;
String  buf;
int     i;
int     lng = noChLine / 10;

  buf.format(_T("Width: %i, xTweak: %i, xPage: %i, xOffset %i"), w, tweak, xPage, xOffset);
  printLine(buf);

  buf.clear();

  for (i = 0; i < lng; i++)           buf += _T("1234567890");
  for (i = 0; i < noChLine % 10; i++) buf += buf[i];

  printLine(buf);

  buf.clear();   for (i = 0; i < noChLine; i++) buf += _T('M');   printLine(buf);

  DeleteObject(SelectObject(hdcPrn, prevFont));
  }


void PrinterBase::examineY(void) {
int     w = getNomWidth() - xTweak;
int     i;
INT     twk;
HGDIOBJ prevFont;

  for (i = 0; i < 2; i++) {

    xOffset = getXoffset(i);    twk = i * yTweak;

    createPort();

      prevFont = insertFont(w, height - twk);

        printVert(twk);

      DeleteObject(SelectObject(hdcPrn, prevFont));                 //GetStockObject(SYSTEM_FONT)

    closePort();
    }
  }


void PrinterBase::printVert(int twk) {
String s;
int    w = logFont.lfWidth;
int    i;
int    n = linesPerPage;

  s.format(_T(" 1 yPage: %i, offset: %i, height: %i tweak: %i, "), yPage, yOffset, height, twk);
  printLine(s);
  s.format(_T(" 2 Width: %i, xTweak: %i, xPage: %i, xOffset %i"), w, xTweak, xPage, xOffset);
  printLine(s);

  for (i = 0; i < n; i++) {
    s.format(_T("%2i - "), i+3);
    s += _T("abcdefghijklmnopqrstuvwxyz - ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    printLine(s);
    }
  }


HGDIOBJ PrinterBase::insertFont(int w, int h) {
HGDIOBJ hFont;
HGDIOBJ prevFont;

  logFont.lfWidth  = w;
  logFont.lfHeight = h;

  hFont = CreateFontIndirect(&logFont);

  if (hFont) prevFont = SelectObject(hdcPrn, hFont);          // (HFONT)

  return prevFont;
  }


bool PrinterBase::printPage(Blkdpo* blkdpo) {
int rslt;

  if (!blkdpo->isPage()) return 0;

  xOffset = getXoffset(pageno);           //doubleSided && (pageno & 1) == 0 ? xOffsetEven : xOffsetOdd;

  createPort(); rslt = blkdpo->output_lines(pageno); pageno++; closePort(); return rslt != 0;
  }


void PrinterBase::createPort(void) {
SIZE  orgSize;
SIZE  portSize;
POINT orgPt;

  StartPage(hdcPrn); SaveDC(hdcPrn);

  SetMapMode(hdcPrn, MM_TEXT);
  SetWindowExtEx(  hdcPrn, 2*xPage, 2*yPage, &orgSize);
  SetViewportExtEx(hdcPrn,   xPage,  -yPage, &portSize);
  SetViewportOrgEx(hdcPrn,       0,       0, &orgPt);

  yPos = yOffset;                                           // Set up for first line to be output
  }


void PrinterBase::printLine(TCchar* line)
                           {TextOut(hdcPrn, xOffset, yPos, line, lstrlen(line));   yPos += height;}


void PrinterBase::closePort(void) {RestoreDC(hdcPrn, -1);   EndPage(hdcPrn);   yPos = 0;}





// Printer List


#include "pch.h"
#include "Printers.h"
#include <Winspool.h>


TCchar* PrinterTxt = _T("Pick the Printer");

Printers printers;


static const ulong EnumFlags = PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS;
static const ulong DscType   = 4;


Printers::Printers() {
ulong  nBuf     = 0;
ulong  nPrinters = 0;
Byte*  buf;
String name;

  if (!EnumPrinters(EnumFlags, NULL, DscType, NULL, 0, &nBuf, &nPrinters) &&
                                                      GetLastError() != ERROR_INSUFFICIENT_BUFFER) return;
    buf = new Byte[nBuf];   if (buf == NULL) return;

  // Fill the buf
  // Again, this depends on the O/S

  if (!EnumPrinters(EnumFlags, NULL, DscType, buf, nBuf, &nBuf, &nPrinters)) {delete [] buf; return;}

  if (nPrinters == 0) {delete [] buf; return;}

  PRINTER_INFO_4* pInfo = (PRINTER_INFO_4*) buf;

  for (DWORD i = 0; i < nPrinters; i++, pInfo++) {
#if 1
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_FAX) continue;

    data = name = pInfo->pPrinterName;
#else
    if (i) notePad << nCrlf;
    notePad << _T("Name: ") << pInfo->pPrinterName << nCrlf;
    if (pInfo->pPortName) notePad << _T("Port: ") << pInfo->pPortName    << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_DIRECT)          notePad << _T("DIRECT") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_DO_COMPLETE_FIRST)
                                                              notePad << _T("DO_COMPLETE_FIRST") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_ENABLE_DEVQ)     notePad << _T("ENABLE_DEVQ") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_HIDDEN)          notePad << _T("HIDDEN") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_KEEPPRINTEDJOBS) notePad << _T("KEEPPRINTEDJOBS") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_LOCAL)           notePad << _T("LOCAL") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_NETWORK)         notePad << _T("NETWORK") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_PUBLISHED)       notePad << _T("PUBLISHED") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_QUEUED)          notePad << _T("QUEUED") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_RAW_ONLY)        notePad << _T("RAW_ONLY") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_SHARED)          notePad << _T("SHARED") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_FAX)             notePad << _T("FAX") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_FRIENDLY_NAME)   notePad << _T("FRIENDLY_NAME") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_MACHINE)         notePad << _T("MACHINE") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_PUSHED_USER)     notePad << _T("PUSHED_USER") << nCrlf;
    if (pInfo->Attributes & PRINTER_ATTRIBUTE_PUSHED_MACHINE)  notePad << _T("PUSHED_MACHINE") << nCrlf;
#endif
    }

  delete [] buf;
  }



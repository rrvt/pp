// Printer Interface


#pragma once
#include "PrinterBase.h"

class CalibrateXdlg;
class CalibrateYdlg;


class Printer : public PrinterBase {

public:

  Printer() : PrinterBase() { }
 ~Printer() { }


  TCchar* getName()    {return name;}
  int     getChars()   {return charsPerLine;}
  int     getXodd()    {return xOffsetOdd;}
  int     getXeven()   {return xOffsetEven;}
  int     getXtweak()  {return xTweak;}

  int     getLines()   {return linesPerPage;}
  int     getYoffset() {return yOffset;}
  int     getYtweak()  {return yTweak;}

  void    saveCurParams();

  void    saveHorizParams(CalibrateXdlg& dlg);

  void    saveVertParams(CalibrateYdlg& dlg);
  };


extern Printer printer;




//void    writeHorizParam(TCchar* charPerLine, TCchar* oddPgOffset, TCchar* evenPgOffset, TCchar* tweak);
//void    writeVertParam(CString& nLinesPerPg, CString& offset, CString& tweak);
  //  void    readHorizParam(CString& charPerLine, CString& oddPgOffset, CString& evenPgOffset, CString& tweak);
//  void    readVertParam( CString& nLinesPerPg, CString& offset, CString& tweak);


// print files
// rrvt 9/28/97


#pragma once
class Blkdpo;


extern TCchar* CharsPerLine;
extern TCchar* XOffsetOddPg;
extern TCchar* XOffsetEvenPg;
extern TCchar* XTweak;
extern TCchar* LinesPerPage;
extern TCchar* YOffset;
extern TCchar* YTweak;


class PrinterBase {
protected:

String  name;                         // PrinterBase Full Name
int     charsPerLine;                 // X Parameters
int     xOffsetOdd;
int     xOffsetEven;
int     xTweak;

int     linesPerPage;                 // Y Parameters
int     yOffset;
int     yTweak;

bool    opened;                       // printer opened when true
HDC     hdcPrn;                       // PrinterBase Handle
DOCINFO info;

HGDIOBJ oldFont;
LOGFONT logFont;
int     noChLine;
int     xPage;
int     yPage;

bool    doubleSided;
int     xOffset;

int     height;
int     yPos;

public:

bool reqDoubleSided;
int  pageno;

  PrinterBase();
 ~PrinterBase() {}

  void initCurPrntr();                      // get current printer and load parameters
  void initialize(TCchar* nam);             // Load parameters for named printer from iniFile
  void saveCurPrntr();                      // Save Current printer

  bool selectPrinter();
  bool setupPrinter(bool dblSdd);

  bool open();
                                            // Make printer ready for output
//  bool startPrinter();
  bool isDoubleSided() {return doubleSided;}
  void close(void);                         // Close printer -- release resources

  int  noLinesPerPage() {return linesPerPage;}
  int  noCharsPerLine() {return charsPerLine;}

  bool printPage(Blkdpo* blkdpo);           // print one page -- calls function to get lines.
  void printLine(TCchar* line);             // Output one line to printer
  void printLine(String& line) {printLine(line.str());}

  void examineX(void);                      // Look at various X configurations
  void examineY(void);

protected:

  bool    getCurPrntr(String& prntr);
  int     getNomWidth()  {return xPage / charsPerLine;}
  int     getXoffset(int i) {return doubleSided && (i & 1) == 0 ? xOffsetEven : xOffsetOdd;}
  int     getNomHeight() {return (yPage - yOffset)/ linesPerPage;}


  void    loadParam();
  bool    getDefaultPrinter(String& newPrntr);               // Sets printer if returns true
  void    createPort(void);
  void    closePort(void);
  int     PageGDICalls(short cxPage, short cyPage);
  void    printGrp(int width);
  void    print10(int tweak);
  HGDIOBJ insertFont(int w, int h);
  void    printVert(int twk);
  };

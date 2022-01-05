// print files
// rrvt 9/28/97


#pragma once
class Blkdpo;


class Printer {

String  name;

bool    opened;

HDC     hdcPrn;                       // Printer Handle
DOCINFO info;

HGDIOBJ oldFont;
LOGFONT logFont;
int     noChLine;
int     xPage;
int     yPage;
String  font;

int     charsPerLine;
int     xTweak;
bool    doubleSided;
int     xOffsetOdd;
int     xOffsetEven;
int     xOffset;
int     pixelsPerInch;
int     linesPerPage;
int     yTweak;
int     yOffset;

int     height;
int     lineX;

public:

bool reqDoubleSided;
int  pageno;

  Printer();
 ~Printer() {}

  void setPrinterName(String& nm) {name = nm;}

  bool open();
                                            // Make printer ready for output
  bool startPrinter();
  bool isDoubleSided() {return doubleSided;}
  void close(void);                         // Close printer -- release resources

  int  noLinesPerPage() {return linesPerPage;}
  int  noCharsPerLine() {return charsPerLine;}

  bool printPage(Blkdpo* blkdpo);           // print one page -- calls function to get lines.
  void printLine(TCchar* line);             // Output one line to printer
  void printLine(String& line) {printLine(line.str());}

  void examineX(void);                      // Look at various X configurations
  void examineY(void);

  void readHorizParam(CString& nCharPerLine, CString& oddPgOffset,
                                                                  CString& evenPgOffset, CString& tweak);
  void writeHorizParam(CString& nCharPerLine, CString& oddPgOffset,
                                                                  CString& evenPgOffset, CString& tweak);

  void readVertParam( CString& nLinesPerPg, CString& offset, CString& tweak);
  void writeVertParam(CString& nLinesPerPg, CString& offset, CString& tweak);
protected:

  bool getDefaultPrinter();                 // Sets printer if returns true
  void createPort(void);
  void closePort(void);
  int  PageGDICalls(short cxPage, short cyPage);
  void print10(int w);
  void printVert(int height, int h);
  void getPrinterParms();
  };


extern Printer printer;

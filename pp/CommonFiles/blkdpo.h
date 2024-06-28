/* Blocked Printer Output
// rrvt 11/4/90

// Copyright (C) 1991 by Software Design & Engineering, All rights reserved.

// Prints a group of lines, a header on each page, pages being defined by the
// position of double and single blank lines in the file (and page ejects).
// A page is filled as much as possible with text bounded by blank lines.  */


#pragma once

static const int MaxLines = 3 * 100;


struct Ln {
String s;
bool   blank;

  Ln() : blank(false) {}
  Ln(Ln& src) {s = src.s; blank = src.blank;}

  Ln& reset() {s.clear(); blank = true; return *this;}

  Ln& operator= (Ln& src) {s = src.s; blank = src.blank; return *this;}
  };


class Lines {
int     i;
int     curX;
int     pos;
Ln*     ln;
Ln      lines[MaxLines];

public:

  Lines() : i(0), curX(0), pos(0) {}
  void    init() {i = 0; curX = 0; pos = 0; resetCur();}

  void    put(Tchar ch) {ln->s += ch; pos++;}
  Ln*     cur()         {ln = &lines[curX]; return ln;}
  Ln*     nextCur()     {if (curX >= MaxLines) return 0; curX++;  ln = resetCur(); return ln;}
  String* curLine()     {return &cur()->s;}
  Ln*     resetCur()    {Ln& p = cur()->reset(); pos = 0; return &p;}

  int     curPos()      {return pos;}
  bool    isFirstLine() {return curX == 0;}
  bool    isPage()      {return curX > 0;}
  bool    gotApage(int nLinesPerPage) {return curX >= 2*nLinesPerPage;}

  Ln*     startLoop()       {i = -1; return nextNode();}
  Ln*     nextNode()        {return ++i < curX ? &lines[i] : 0;}
  Ln*     resetLines();

  friend class Break;
  };



class Break {
Lines&  lns;
int     curX;

public:

  Break(Lines& lines) : lns(lines), curX(lines.curX) {}

  int find(int noTxtLines, int noLinesInPage);
  };



class Blkdpo {

enum {LeftMargin    = 0};

int        noCharsInLine;             // Global count of number of characters in line
int        noLinesInPage;
int        noTxtLines;
Lines      lines;
Ln*        ln;                        // Pointer to current line data
String*    pline;                     // Current line while copying characters into lines
                                      //
String     header;
bool       outputHdr;
bool       blank;
int        noBlanks;

public:

  Blkdpo();
 ~Blkdpo() {}

  void    init(int linesPerPage, int charsPerLine);

  void    set_header(TCchar* pname, TCchar* ptime);         //, int width
  void    disable_header(void);

  void    put(Tchar ch);

  bool    isPage() {return lines.isPage();}

  bool    output_lines(int pageno);
  Ln*     resetLines() {return lines.resetLines();}

  void    close(void);

private:

  void    terminateLine(void);
  void    reset_blkdpo(bool hdr);
//void    isMagicLine();
  };


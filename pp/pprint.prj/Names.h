// Names


#pragma once


class Names {
TokenString tStg;
String      tok;
public:

  Names(CString& ln) {String s = ln; tStg = s;}

  String* startLoop() {return nextName();}
  String* nextName()  {if (tStg.next(tok, _T(" "))) return &tok; return 0;}

private:
  Names() {}
  };


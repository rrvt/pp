// Extensions ordinarily printed


#pragma once
#include "Expandable.h"
#include "IterT.h"


class Extension;
typedef IterT<Extension, String> ExtIter;


class Extension {
bool                   ignoreExt;
Expandable<String, 8> data;

public:

  Extension();

  void initialize();
  bool isLegal(TCchar* name);
  void setIgnoreExt(bool ignore) {ignoreExt = ignore;}

  void readExtensions( Cstring& cs);
  void writeExtensions(Cstring& cs);

private:

  // returns either a pointer to datum at index i in array or zero

  String* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}

  int     nData()      {return data.end();}                       // returns number of data items in array

  void    removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename ExtIter;
  };


extern Extension extension;


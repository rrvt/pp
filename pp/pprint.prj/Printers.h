// Printer List


#pragma once
#include "Expandable.h"
#include "IterT.h"


extern TCchar* PrinterTxt;

class Printers;
typedef IterT<Printers, String> PrtrsIter;


class Printers {

Expandable<String, 8> data;

public:

  Printers();
 ~Printers() { }

private:

  // returns either a pointer to datum at index i in array or zero

  String* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename PrtrsIter;
  };

extern Printers printers;

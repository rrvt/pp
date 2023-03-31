// Printer Interface


#pragma once
#include "PrinterBase.h"


class Printer : public PrinterBase {

public:

  Printer() : PrinterBase() { }
 ~Printer() { }
  };


extern Printer printer;



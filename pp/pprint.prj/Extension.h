// Extensions ordinarily printed


#pragma once
#include "Expandable.h"



class Extension {
int                    nExt;
Expandable<String, 32> ext;
bool                   ignoreExt;

public:

  Extension();

  void initialize();
  bool isLegal(TCchar* name);
  void setIgnoreExt(bool ignore) {ignoreExt = ignore;}

  void readExtensions( CString& cs);
  void writeExtensions(CString& cs);
  };


extern Extension extension;


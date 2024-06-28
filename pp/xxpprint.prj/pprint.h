
// pprint.h : main header file for the PROJECT_NAME application
//

#pragma once
#include "CApp.h"


// pprint:

class pprint : public CApp {

String programName;

public:
               pprint() : CApp(this) { }

  virtual BOOL InitInstance();

  DECLARE_MESSAGE_MAP()
  };


extern pprint theApp;

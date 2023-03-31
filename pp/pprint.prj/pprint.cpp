// pprint.cpp : Defines the class behaviors for the application.


#include "pch.h"
#include "pprint.h"
#include "Extension.h"
#include "filename.h"
#include "IniFile.h"
#include "pprintDlg.h"
#include "printer.h"
#include "Resource.h"
#include "Resources.h"


pprint  theApp;                             // The one and only pprint object
IniFile iniFile;

// pprint

BEGIN_MESSAGE_MAP(pprint, CWinAppEx)
END_MESSAGE_MAP()


// pprint initialization

BOOL pprint::InitInstance() {
PPrintDlg dlg(m_pszHelpFilePath);

  CWinApp::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  extension.initialize();

  printer.initCurPrntr();

    dlg.DoModal();

  printer.saveCurPrntr();    m_pMainWnd = 0;    return 0;
  }


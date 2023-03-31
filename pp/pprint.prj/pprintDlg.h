
// pprintDlg.h : header file
//

#pragma once
#include "ToolBar.h"
#include "WinPos.h"


// PPrintDlg dialog
class PPrintDlg : public CDialogEx {

String        helpPath;

HICON         m_hIcon;
ToolBar       toolBar;

bool          isInitialized;
WinPos        winPos;                                // Position of dialog box

CStatic       pathCtrl;
CButton       afterDtCtrl;
CButton       afterTmCtrl;
CDateTimeCtrl afterDateCtrl;
CDateTimeCtrl afterTimeCtrl;

String        path;                           // Current Path
BOOL          doubleSided;
BOOL          acceptExtension;
BOOL          printHeader;
BOOL          searchSubDirs;
CString       tabStopSpacing;
BOOL          afterDt;
BOOL          afterTm;
COleDateTime  afterDate;
COleDateTime  afterTime;
CString       nameLine;

public:

#ifdef AFX_DESIGN_TIME
  enum {IDD = IDD_pprint};                     // Dialog Data
#endif

  PPrintDlg(TCchar* helpPth, CWnd* pParent = nullptr);                 // standard constructor

protected:

  DECLARE_MESSAGE_MAP()

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  // Generated message map functions
  virtual BOOL    OnInitDialog();

//          bool    setupPrinter(bool dblSdd);

          void    readDlgData();
          void    readOneDatum(TCchar* key, int& datum, int dflt);
          void    writeDlgData();
          void    writeOneDatum(TCchar* key, int& datum);

          bool    getDateTime(CTime& tm);

private:

  void setupToolBar();
  bool printFile(String& path, bool printHeader);
  bool addAboutToSysMenu(uint idm, uint ids);

public:

  afx_msg void    OnSelectFolder();
  afx_msg void    OnFilePrint();
  afx_msg void    OnBnClickedAfterDt();
  afx_msg void    onDispatch();
  afx_msg void    OnXTweak();
  afx_msg void    OnYTweak();
  afx_msg void    OnEditextensions();
  afx_msg BOOL    OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg UINT    OnNotifyFormat(CWnd *pWnd, UINT nCommand);
  afx_msg LRESULT OnResetToolBar(WPARAM wParam, LPARAM lParam);

  afx_msg void    OnMove(int x, int y);
  afx_msg void    OnSize(UINT nType, int cx, int cy);
  afx_msg void    OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void    OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();

  afx_msg void    onHelp();
  afx_msg void    OnAbout();
  afx_msg void    OnExit();
  };



// bool    selectPrinter();



// pprintDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pprintDlg.h"
#include "AboutDlg.h"
#include "CalibrateXdlg.h"
#include "CalibrateYdlg.h"
#include "EditExtensions.h"
#include "Extension.h"
#include "File.h"
#include "FilePaths.h"
#include "filesrch.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "Names.h"
#include "pprint.h"
#include "printer.h"


static TCchar* Globals        = _T("Globals");
static TCchar* FolderPath     = _T("FolderPath");
static TCchar* DoubleSided    = _T("DoubleSided");
static TCchar* AccptExt       = _T("AcceptExtension");
static TCchar* PrintHeader    = _T("PrintHeader");
static TCchar* SearchSubDirs  = _T("SearchSubDirs");
static TCchar* TabStopSpacing = _T("TabStopSpacing");
//static TCchar* MenuCaption    = _T("Options");

static const TCchar* ItemsCaption =   _T("Options");
static const CbxItem PopupItems[] = {{_T("Calibrate X"),     ID_X_Tweak},
                                     {_T("Calibrate Y"),     ID_Y_Tweak},
                                     {_T("Edit Extensions"), ID_EditExtensions}
                                     };


BEGIN_MESSAGE_MAP(PPrintDlg, CDialogEx)
  ON_COMMAND(      ID_SelectFolder,   &OnSelectFolder)
  ON_COMMAND(      ID_Print,          &OnFilePrint)
  ON_COMMAND(      ID_ABOUT,          &OnAbout)
  ON_BN_CLICKED(   IDC_AfterDt,       &OnBnClickedAfterDt)
  ON_BN_CLICKED(   IDC_AfterTm,       &OnBnClickedAfterDt)

  ON_CBN_SELCHANGE(ID_PopupMenu,      &onDispatch)            // Send Command Message with ID_...
  ON_COMMAND(      ID_X_Tweak,        &OnXTweak)
  ON_COMMAND(      ID_Y_Tweak,        &OnYTweak)
  ON_COMMAND(      ID_EditExtensions, &OnEditextensions)

  ON_COMMAND(      ID_Help,           &onHelp)
  ON_COMMAND(      ID_Exit,           &OnExit)
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0,   &OnTtnNeedText)

  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()

  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &OnResetToolBar)
END_MESSAGE_MAP()


// PPrintDlg dialog

PPrintDlg::PPrintDlg(TCchar* helpPth, CWnd* pParent) : helpPath(helpPth), CDialogEx(IDD_pprint, pParent),
  m_hIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME)), doubleSided(FALSE), acceptExtension(FALSE),
  printHeader(FALSE), searchSubDirs(FALSE), tabStopSpacing(_T("")),
  afterDt(FALSE), afterTm(FALSE),
  afterDate(COleDateTime::GetCurrentTime()), afterTime(COleDateTime::GetCurrentTime()),
  nameLine(_T("")) { }


BOOL PPrintDlg::OnInitDialog() {
                                                        // Initialize data in variables before dialog init
  readDlgData();

  COleDateTime dt = COleDateTime::GetCurrentTime();
  int yr = dt.GetYear();
  int mn = dt.GetMonth();
  int dy = dt.GetDay() - 7;
  if (dy <= 0) {dy += 30; mn--;  if (mn < 1) {mn = 12; yr--;}}

  dt.SetDateTime(yr, mn, dy, 0, 0, 0);
  afterDate = dt;
  afterTime = dt;

  CDialogEx::OnInitDialog();                      // Initialize data before OnInit, controls after Init
                                                  // system menu (upper left hand corner & toolbar
  addAboutToSysMenu(IDM_ABOUTBOX, IDS_ABOUTBOX);  // Add "About..." menu item to system menu.

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog

  SetIcon(m_hIcon, TRUE);                               // Set big icon
  SetIcon(m_hIcon, FALSE);                              // Set small icon

  if (!toolBar.create(this, IDR_ToolBar)) EndDialog(IDCANCEL);

  // Initialize controls directly

  iniFile.readString(Globals, FolderPath, path);   pathCtrl.SetWindowText(path);

  afterDateCtrl.SetFormat(_T("MM/dd/yy"));
  afterTimeCtrl.SetFormat(_T("HHmm"));

//  UpdateData(true);

//  toolBar.setPopupCaption(ID_PopupMenu, MenuCaption);

  return TRUE;                                      // return TRUE unless you set the focus to a control
  }


// MainFrame message handlers

LRESULT PPrintDlg::OnResetToolBar(WPARAM wParam, LPARAM lParam) {setupToolBar();  return 0;}


void PPrintDlg::setupToolBar() {
CRect winRect;   GetWindowRect(&winRect);   toolBar.initialize(winRect);

  if (toolBar.installPopupMenu(ID_PopupMenu)) {
    toolBar.addPopupItems(ID_PopupMenu, PopupItems, noElements(PopupItems));
    toolBar.setPopupCaption(ID_PopupMenu, ItemsCaption);
    }
  }



void PPrintDlg::readDlgData() {
int spcing;

  readOneDatum(DoubleSided,    doubleSided,     false);
  readOneDatum(AccptExt,       acceptExtension, false);
  readOneDatum(PrintHeader,    printHeader,     true);
  readOneDatum(SearchSubDirs,  searchSubDirs,   true);
  readOneDatum(TabStopSpacing, spcing,  0);
  String s = spcing;  tabStopSpacing = s;
  }


bool PPrintDlg::addAboutToSysMenu(uint idm, uint ids) {
CMenu*  sysMenu;
Cstring cs;

  if ((idm & 0xFFF0) != idm) return false;
  if (idm >= 0xF000)         return false;

  sysMenu = GetSystemMenu(FALSE);

  if (!sysMenu || !cs.loadRes(ids) || cs.isEmpty()) return false;

  sysMenu->AppendMenu(MF_SEPARATOR);
  sysMenu->AppendMenu(MF_STRING, idm, cs);   return true;
  }


void PPrintDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(     pDX, IDC_CurPath,         pathCtrl);

  DDX_Check(       pDX, IDC_DoubleSided,     doubleSided);
  DDX_Check(       pDX, IDC_AcceptExtension, acceptExtension);
  DDX_Check(       pDX, IDC_PrintHeader,     printHeader);
  DDX_Check(       pDX, IDC_SearchSubDirs,   searchSubDirs);
  DDX_Text(        pDX, IDC_TabStopSpacing,  tabStopSpacing);

  DDX_Control(     pDX, IDC_AfterDt,         afterDtCtrl);
  DDX_Check(       pDX, IDC_AfterDt,         afterDt);
  DDX_Control(     pDX, IDC_DATETIMEPICKER2, afterDateCtrl);
  DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, afterDate);

  DDX_Control(     pDX, IDC_AfterTm,         afterTmCtrl);
  DDX_Check(       pDX, IDC_AfterTm,         afterTm);
  DDX_Control(     pDX, IDC_DATETIMEPICKER3, afterTimeCtrl);
  DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, afterTime);

  DDX_Text(        pDX, IDC_NameLine,        nameLine);
  }


void PPrintDlg::readOneDatum(TCchar* key, int& datum, int dflt) {

  datum = iniFile.readInt(Globals, key, -1);

  if (datum == -1) {datum = dflt;   iniFile.writeInt(Globals, key, datum);}
  }


void PPrintDlg::writeDlgData() {
String s;
uint   pos;
int    spcng;

  writeOneDatum(DoubleSided,    doubleSided);
  writeOneDatum(AccptExt,       acceptExtension);
  writeOneDatum(PrintHeader,    printHeader);
  writeOneDatum(SearchSubDirs,  searchSubDirs);

  s = tabStopSpacing;   spcng = s.stoi(pos);   writeOneDatum(TabStopSpacing, spcng);
  }


void PPrintDlg::writeOneDatum(TCchar* key, int& datum) {iniFile.writeInt(Globals, key, datum);}


BOOL PPrintDlg::OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
                                                                  {return toolBar.OnTtnNeedText(pNMHDR);}



// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void PPrintDlg::OnPaint() {
  if (IsIconic()) {

    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
    }
  else {CDialogEx::OnPaint();}
  }


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.

HCURSOR PPrintDlg::OnQueryDragIcon() {return static_cast<HCURSOR>(m_hIcon);}


void PPrintDlg::OnSysCommand(UINT nID, LPARAM lParam) {
  if ((nID & 0xFFF0) == IDM_ABOUTBOX) OnAbout();
  else                                CDialogEx::OnSysCommand(nID, lParam);
  }


void PPrintDlg::onHelp() {
String topic = helpPath + _T(">Introduction");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void PPrintDlg::OnAbout() {AboutDlg dlgAbout;   dlgAbout.DoModal();}


void PPrintDlg::OnFilePrint() {
String*  p;
String   fullPath;
int      i;
CTime    tm;
int      tabSpc;
uint     ui;

  UpdateData(true);

  if (setupPrinter(doubleSided)) {

    Names line(nameLine);

    extension.setIgnoreExt(acceptExtension);

    String ts = tabStopSpacing; tabSpc = ts.stoi(ui);

    for (p = line.startLoop(), i = 0; p; p = line.nextName(), i++) {
      String& fileName = *p;
      String  path     = fileName;
      int     pos      = path.find_last_of(pathSepChar);
      String  pFile;

      if (pos > 0) {path.resize(pos); fileName = fileName.substr(pos+1);}
      else if (!this->path.isEmpty()) path = this->path;
      else                            path = _T(".");

      if (fileName.find_last_of(_T('.')) == string::npos) fileName += _T(".*");

      if (tabSpc) file.setTab(tabSpc);

      if (getDateTime(tm)) file.setAfterTime(tm);

      if (searchSubDirs) {
        FilePaths filePaths;
        FPsIter   iter(filePaths);
        String*   pth;

        if (filePaths.findFiles(path, fileName)) {

          for (pth = iter(); pth; pth = iter++) {
            if (!printFile(*pth, printHeader)) return;
            }
          }
        }
      else {
        FileSrch fileSrch;

        if (fileSrch.findFiles(path, fileName)) {

          while (fileSrch.getName(pFile))
            if (!printFile(pFile, printHeader)) return;
          }
        }
      }

    writeDlgData();
    }

  printer.close();
  }


bool PPrintDlg::printFile(String& path, bool printHeader) {

  if (!extension.isLegal(path)) return true;

  if (!printer.open()) {MessageBox(_T("printer could not be opened")); return false;}

  file.initialize(printHeader);

  if (!file.print(path)) {MessageBox(file.errMsg); return false;}

  printer.pageno = 1;  return true;
  }


bool PPrintDlg::setupPrinter(bool dblSdd) {
CPrintDialogEx printerDlg;
String         prtName;

  printer.reqDoubleSided = dblSdd;

  printerDlg.DoModal();

  prtName = printerDlg.GetDeviceName();     if (prtName.isEmpty()) return false;

  printer.setPrinterName(prtName); return true;
  }



void PPrintDlg::OnSelectFolder() {
  if (getDirPathDlg(_T("Select Path"), path)) {
    iniFile.writeString(Globals, FolderPath, path);   pathCtrl.SetWindowText(path);  //setCurPath(path);
    }
  }


void PPrintDlg::OnBnClickedAfterDt() {
bool         dtSt = afterDtCtrl.GetCheck();
bool         tmSt = afterTmCtrl.GetCheck();
COleDateTime dt   = COleDateTime::GetCurrentTime();
int          yr   = dt.GetYear();
int          mn   = dt.GetMonth();
int          dy   = dt.GetDay();
int          hr   = dt.GetHour();
int          min  = dt.GetMinute();

  if (dtSt && tmSt) {
    dy -= 7; if (dy <= 0) {dy += 30; mn--;  if (mn < 1) {mn = 12; yr--;}}
    dt.SetDateTime(yr, mn, dy, hr, min, 0);
    afterDateCtrl.SetTime(dt);
    afterTimeCtrl.SetTime(dt);
    }
  else if (dtSt) {
    dy -= 7; if (dy <= 0) {dy += 30; mn--;  if (mn < 1) {mn = 12; yr--;}}
    dt.SetDateTime(yr, mn, dy, 0, 0, 0);
    afterDateCtrl.SetTime(dt);
    afterTimeCtrl.SetTime(dt);
    }
  else if (tmSt) {
    hr -= 4;  if (hr < 0) {hr = 0;}
    dt.SetDateTime(yr, mn, dy, hr, 0, 0);
    afterDateCtrl.SetTime(dt);
    afterTimeCtrl.SetTime(dt);
    }
  else {
    dy -= 7; if (dy <= 0) {dy += 30; mn--;  if (mn < 1) {mn = 12; yr--;}}
    dt.SetDateTime(yr, mn, dy, 0, 0, 0);
    afterDateCtrl.SetTime(dt);
    afterTimeCtrl.SetTime(dt);
    }
  }


bool PPrintDlg::getDateTime(CTime& tm) {

  if (!afterDt && !afterTm) return false;

  int yr   = afterDate.GetYear();
  int mn   = afterDate.GetMonth();
  int dy   = afterDate.GetDay();
  int hr   = afterTime.GetHour();
  int min  = afterTime.GetMinute();
  CTime t(afterDate.GetYear(), afterDate.GetMonth(),  afterDate.GetDay(),
          afterTime.GetHour(), afterTime.GetMinute(), 0
          );

  tm = t; return true;
  }


void PPrintDlg::OnExit() {EndDialog(0);}


void PPrintDlg::onDispatch() {toolBar.dispatch(ID_PopupMenu, ItemsCaption);}


void PPrintDlg::OnXTweak() {
CalibrateXdlg dlg;

  if (setupPrinter(doubleSided)) {

    printer.readHorizParam(dlg.nCharPerLine, dlg.oddPgOffset, dlg.evenPgOffset, dlg.tweak);

    if (dlg.DoModal() != IDOK) return;

    printer.writeHorizParam(dlg.nCharPerLine, dlg.oddPgOffset, dlg.evenPgOffset, dlg.tweak);

    if (!printer.open()) {MessageBox(_T("printer could not be opened")); return;}

    file.initialize(printHeader);

    printer.examineX();

    printer.close();
    }
  }


void PPrintDlg::OnYTweak() {
CalibrateYdlg dlg;

  if (setupPrinter(doubleSided)) {

    printer.readVertParam(dlg.nLinesPerPg, dlg.offset, dlg.tweak);

    if (dlg.DoModal() != IDOK) return;

    printer.writeVertParam(dlg.nLinesPerPg, dlg.offset, dlg.tweak);

    if (!printer.open()) {MessageBox(_T("printer could not be opened")); return;}

    file.initialize(printHeader);

    printer.examineY();

    printer.close();
    }
  }


void PPrintDlg::OnEditextensions() {
EditExtensions dlg;

  extension.readExtensions(dlg.extensions); if (dlg.DoModal()) extension.writeExtensions(dlg.extensions);
  }




#if 0
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
  CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_ABOUTBOX };
#endif

  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) { }

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {CDialogEx::DoDataExchange(pDX);}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()
#endif





#if 0
    INT_PTR nHit = toolBar.HitTest(point);

    if (nHit >= 0) {
      CMFCToolBarButton* pButton = toolBar.GetButton((int)nHit);

      if (pButton != btn) {
        pButton = btn;
        }
      if (pButton) {
        id = pButton->m_nID;

        s.LoadString(id);

        _stprintf_s(pTTT->szText, sizeof(pTTT->szText) / sizeof(TCHAR), _T("%s"), s.GetBuffer());

        pTTT->uFlags = TTF_ABSOLUTE | TTF_TRACK;
        pTTT->lParam = MAKELONG(screenPt.x, screenPt.y);

        ::SendMessage(hwnd, TTM_TRACKPOSITION, 0, (LPARAM)(DWORD) MAKELONG(screenPt.x, screenPt.y));
        ::SendMessage(hwnd, TTM_TRACKACTIVATE, true, (LPARAM)(LPTOOLINFO) pTTT);

        *pResult = 0;   return true;
        }
      }
#endif



#if 0
    // idFrom is actually the HWND of the tool

    nID = ::GetDlgCtrlID((HWND) nID);

    if (nID) {

      s.LoadString(nID);

      _stprintf_s(pTTT->szText, sizeof(pTTT->szText) / sizeof(TCHAR), _T("%s"), s.GetBuffer());

      pTTT->hinst = AfxGetResourceHandle();

      bRet = TRUE;
      }
#endif
#if 0
BOOL CMyDialog::OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
   UNREFERENCED_PARAMETER(id);

   NMTTDISPINFO* pTTT = (NMTTDISPINFO*)pNMHDR;
   UINT_PTR nID = pNMHDR->idFrom;
   BOOL bRet = FALSE;

   if (pTTT->uFlags & TTF_IDISHWND)
   {
      // idFrom is actually the HWND of the tool
      nID = ::GetDlgCtrlID((HWND)nID);
      if (nID)
      {
         _stprintf_s(pTTT->szText, sizeof(pTTT->szText) / sizeof(TCHAR),
            _T("Control ID = %d"), nID);
         pTTT->hinst = AfxGetResourceHandle();
         bRet = TRUE;
      }
   }

   *pResult = 0;

   return bRet;
}
#endif

#if 0
BOOL CMFCToolBarEx::OnNeedTipText(UINT /*id*/, NMHDR* pNMH, LRESULT* /*pResult*/)
{
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMH;
   // UINT nID = static_cast<int>(pNMH->idFrom);
    CString strTip = _T("");

    CPoint point;
    ::GetCursorPos(&point);
    ScreenToClient(&point);
    INT_PTR nHit = ((CMFCToolBar*)this)->HitTest(point);

    if(nHit == -1)
        return FALSE;

    CMFCToolBarButton* pButton = GetButton((int)nHit);
    strTip = pButton->m_strText;
    _tcscpy(pTTT->lpszText , strTip.GetBuffer(0));

    return TRUE;
}
#endif
//void PPrintDlg::setCurPath(TCchar* path) {pathCtrl.SetWindowText(path);}
#if 1
#else
NMTTDISPINFO* pTTT = (NMTTDISPINFO*) pNMHDR;
UINT_PTR      nID  = pNMHDR->idFrom;
Cstring       s;

  if (pTTT->uFlags & TTF_IDISHWND) {

  *pResult = 0;   if (!nID) return false;

  s.LoadString(nID);

  _stprintf_s(pTTT->szText, sizeof(pTTT->szText) / sizeof(TCHAR), _T("%s"), s.GetBuffer());

  pTTT->hinst = AfxGetResourceHandle();   return true;
#endif
//  pTTT->uFlags = 0; //TTF_ABSOLUTE;// | TTF_TRACK;
//  pTTT->lParam = MAKELONG(screenPt.x, screenPt.y);   //   point.x, point.y                          //
//  pTTT->hinst = 0;

//  ::SendMessage(hWnd, TTM_TRACKACTIVATE, true, (LPARAM)(LPTOOLINFO) pTTT);



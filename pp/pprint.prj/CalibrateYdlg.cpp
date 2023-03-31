// CalibrateYdlg.cpp : implementation file
//

#include "pch.h"
#include "CalibrateYdlg.h"
#include "printer.h"
#include "Printers.h"
#include "Resource.h"


// CalibrateYdlg dialog

IMPLEMENT_DYNAMIC(CalibrateYdlg, CDialogEx)

CalibrateYdlg::CalibrateYdlg(CWnd* pParent) : CDialogEx(IDD_CalibrateYdlg, pParent), name(_T("")),
                                                 nLines(_T("")), yOffset(_T("")), yTweak(_T("")) { }

CalibrateYdlg::~CalibrateYdlg() { }


BOOL CalibrateYdlg::OnInitDialog() {
PrtrsIter iter(printers);
String*   s;

  name    = printer.getName();
  nLines  = printer.getLines();
  yOffset = printer.getYoffset();
  yTweak  = printer.getYtweak();

  CDialogEx::OnInitDialog();

  for (s = iter(); s; s = iter++) nameCtl.AddString(*s);

  if (!name.isEmpty()) nameCtl.SetWindowText(name);
  else                 nameCtl.SetWindowText(PrinterTxt);

  return TRUE;
  }


void CalibrateYdlg::OnCbnSelchangePrinterlist() {
Cstring newPrntr;
Cstring cs;

  nameCtl.GetLBText(nameCtl.GetCurSel(), newPrntr);

  if (!name.isEmpty() && name != newPrntr) printer.saveCurParams();

  printer.initialize(newPrntr);
  cs = printer.getLines();     nLinesCtl.SetWindowText(cs);
  cs = printer.getYoffset();   yOffsetCtl.SetWindowText(cs);
  cs = printer.getYtweak();    yTweakCtl.SetWindowText(cs);
  }


void CalibrateYdlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_CBString(pDX, IDC_PrinterList,  name);
  DDX_Text(    pDX, IDC_LinesPerPage, nLines);
  DDX_Text(    pDX, IDC_Yoffset,      yOffset);
  DDX_Text(    pDX, IDC_Ytweak,       yTweak);
  DDX_Control( pDX, IDC_PrinterList,  nameCtl);
  DDX_Control( pDX, IDC_LinesPerPage, nLinesCtl);
  DDX_Control( pDX, IDC_Yoffset,      yOffsetCtl);
  DDX_Control( pDX, IDC_Ytweak,       yTweakCtl);
}


BEGIN_MESSAGE_MAP(CalibrateYdlg, CDialogEx)
    ON_CBN_SELCHANGE(IDC_PrinterList, &CalibrateYdlg::OnCbnSelchangePrinterlist)
END_MESSAGE_MAP()

// CalibrateXdlg.cpp : implementation file
//

#include "pch.h"
#include "CalibrateXdlg.h"
#include "printer.h"
#include "Printers.h"
#include "resource.h"   // main symbols


// CalibrateXdlg dialog

IMPLEMENT_DYNAMIC(CalibrateXdlg, CDialogEx)


BEGIN_MESSAGE_MAP(CalibrateXdlg, CDialogEx)
  ON_CBN_SELCHANGE(IDC_PrinterList, &onSelectPrinter)
END_MESSAGE_MAP()


CalibrateXdlg::CalibrateXdlg(CWnd* pParent) : CDialogEx(IDD_CalibrateXdlg, pParent), name(_T("")),
                       charPerLine(_T("")), oddPgOffset(_T("")), evenPgOffset(_T("")), tweak(_T("")) { }


CalibrateXdlg::~CalibrateXdlg() { }


BOOL CalibrateXdlg::OnInitDialog() {
PrtrsIter iter(printers);
String*   s;

  name         = printer.getName();
  charPerLine  = printer.getChars();
  oddPgOffset  = printer.getXodd();
  evenPgOffset = printer.getXeven();
  tweak        = printer.getXtweak();

  CDialogEx::OnInitDialog();

  for (s = iter(); s; s = iter++) nameCtl.AddString(*s);

  if (!name.isEmpty()) nameCtl.SetWindowText(name);
  else                 nameCtl.SetWindowText(PrinterTxt);

  return TRUE;
  }


void CalibrateXdlg::onSelectPrinter() {
Cstring newPrntr;
Cstring cs;

  nameCtl.GetLBText(nameCtl.GetCurSel(), newPrntr);

  if (!name.isEmpty() && name != newPrntr) printer.saveCurParams();

  printer.initialize(newPrntr);
  cs = printer.getChars();     charsCtl.SetWindowText(cs);
  cs = printer.getXodd();      oddCtl.SetWindowText(cs);
  cs = printer.getXeven();     evenCtl.SetWindowText(cs);
  cs = printer.getXtweak();    tweakCtl.SetWindowText(cs);
  }


void CalibrateXdlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_CBString(pDX, IDC_PrinterList,  name);
  DDX_Text(    pDX, IDC_CharsPerLine, charPerLine);
  DDX_Text(    pDX, IDC_OffsetOdd,    oddPgOffset);
  DDX_Text(    pDX, IDC_OffsetEven,   evenPgOffset);
  DDX_Text(    pDX, IDC_Xtweak,       tweak);
  DDX_Control( pDX, IDC_PrinterList,  nameCtl);
  DDX_Control( pDX, IDC_CharsPerLine, charsCtl);
  DDX_Control( pDX, IDC_OffsetOdd,    oddCtl);
  DDX_Control( pDX, IDC_OffsetEven,   evenCtl);
  DDX_Control( pDX, IDC_Xtweak,       tweakCtl);
  }


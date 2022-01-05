// CalibrateYdlg.cpp : implementation file
//

#include "stdafx.h"
#include "CalibrateYdlg.h"
#include "resource.h"


// CalibrateYdlg dialog

IMPLEMENT_DYNAMIC(CalibrateYdlg, CDialogEx)

CalibrateYdlg::CalibrateYdlg(CWnd* pParent) : CDialogEx(IDD_CalibrateYdlg, pParent),
                                                  nLinesPerPg(_T("")), offset(_T("")), tweak(_T("")) { }

CalibrateYdlg::~CalibrateYdlg() { }


void CalibrateYdlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, nLinesPerPg);
  DDX_Text(pDX, IDC_EDIT2, offset);
  DDX_Text(pDX, IDC_EDIT3, tweak);
  }


BEGIN_MESSAGE_MAP(CalibrateYdlg, CDialogEx)
END_MESSAGE_MAP()


// CalibrateYdlg message handlers

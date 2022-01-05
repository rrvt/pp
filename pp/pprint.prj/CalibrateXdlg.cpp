// CalibrateXdlg.cpp : implementation file
//

#include "stdafx.h"
#include "CalibrateXdlg.h"
#include "resource.h"   // main symbols


// CalibrateXdlg dialog

IMPLEMENT_DYNAMIC(CalibrateXdlg, CDialogEx)


CalibrateXdlg::CalibrateXdlg(CWnd* pParent) : CDialogEx(IDD_CalibrateXdlg, pParent),
                       nCharPerLine(_T("")), oddPgOffset(_T("")), evenPgOffset(_T("")), tweak(_T("")) { }


CalibrateXdlg::~CalibrateXdlg() { }


void CalibrateXdlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, nCharPerLine);
  DDX_Text(pDX, IDC_EDIT2, oddPgOffset);
  DDX_Text(pDX, IDC_EDIT3, evenPgOffset);
  DDX_Text(pDX, IDC_EDIT4, tweak);
  }


BEGIN_MESSAGE_MAP(CalibrateXdlg, CDialogEx)
END_MESSAGE_MAP()



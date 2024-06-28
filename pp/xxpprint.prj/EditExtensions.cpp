// EditExtensions.cpp : implementation file
//

#include "pch.h"
#include "EditExtensions.h"
#include "resource.h"


// EditExtensions dialog

IMPLEMENT_DYNAMIC(EditExtensions, CDialogEx)

EditExtensions::EditExtensions(CWnd* pParent) : CDialogEx(IDD_EditExtensions, pParent),
                                                                                   extensions(_T("")) { }


EditExtensions::~EditExtensions() { }


void EditExtensions::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_Extensions, extensions);
  }


BEGIN_MESSAGE_MAP(EditExtensions, CDialogEx)
END_MESSAGE_MAP()


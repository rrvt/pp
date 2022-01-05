// Get horizontal parameters

#pragma once


// CalibrateXdlg dialog

class CalibrateXdlg : public CDialogEx {

  DECLARE_DYNAMIC(CalibrateXdlg)

public:

CString nCharPerLine;
CString oddPgOffset;
CString evenPgOffset;
CString tweak;

  CalibrateXdlg(CWnd* pParent = nullptr);   // standard constructor

  virtual ~CalibrateXdlg();

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_CalibrateXdlg };                     // Dialog Data
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };

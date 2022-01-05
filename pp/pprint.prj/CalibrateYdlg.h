#pragma once


// CalibrateYdlg dialog

class CalibrateYdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CalibrateYdlg)

public:
	CalibrateYdlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CalibrateYdlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CalibrateYdlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString nLinesPerPg;
	CString offset;
	CString tweak;
};

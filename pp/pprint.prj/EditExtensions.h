#pragma once


// EditExtensions dialog

class EditExtensions : public CDialogEx {

  DECLARE_DYNAMIC(EditExtensions)

public:

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_EditExtensions };                           // Dialog Data
#endif

CString extensions;

           EditExtensions(CWnd* pParent = nullptr);   // standard constructor
  virtual ~EditExtensions();


protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };

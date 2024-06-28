// My ToolBar


#pragma once

#define MyButtonDefs
//#define DocViewTB


#include "TBCbxMenu.h"
#include "ToolBarBase.h"


struct CbxItem;


class MyToolBar : public ToolBarBase {

TBCbxMenu cbxMenu;

public:

  MyToolBar();
 ~MyToolBar() { }

  bool    addButton( uint id, TCchar* caption);
  bool    addEditBox(uint id, int     noChars);
  CString getText(uint id);

#ifdef DocViewTB

  bool    addMenu(   uint id, int     idr, TCchar* caption);
  bool    addMenu(   uint id, int     idr, int     index);
  bool    addMenu(   uint id, CbxItem cbxItem[], int n, TCchar* caption);

#else

  bool    addMenu(   uint id, int     idr, TCchar* caption);
  bool    addMenu(   uint id, const CbxItem cbxItem[], int n, TCchar* caption);
  void    dispatch(uint id);

#endif

  bool    addCBx(    uint id);
  bool    addCBx(    uint id, int     idr, TCchar* caption);
  bool    addCbxItem(uint id, TCchar* txt, int data = 0);
  bool    addCBx(    uint id, CbxItem cbxItem[], int n, TCchar* caption);
  bool    addCbxItemSorted(uint id, TCchar* txt, int data = 0);
  void    setCaption(uint id, TCchar* caption);
  void    setWidth(  uint id);
  void    setHeight( uint id);
  bool    getCurSel( uint id, String& s, int& data);
  };


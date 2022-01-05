// ToolBar Combo Box


#pragma once
#include "CbxItem.h"

struct TBBtnCtx;


class TBComboBox : public CMFCToolBarComboBoxButton {
public:

  TBComboBox(uint id);
 ~TBComboBox() { }

         void        install(TBBtnCtx& ctx);

  static bool        addItems(  uint id, CbxItem* items, int noItems, TBBtnCtx& ctx, bool sorted);
  static bool        addRes(    uint id, uint     idr,                TBBtnCtx& ctx, bool sorted);
  static bool        add(       uint id, CbxItem& item,               TBBtnCtx& ctx, bool sorted);
  static bool        setCaption(uint id, TCchar*  txt,                TBBtnCtx& ctx);

  static bool        getCurSel(uint id, String& s, int& data);   // Returns current selection when true

         int         find(TCchar* tc) {String s = tc; return find(s);}
         int         find(String& s);

  static TBComboBox* get(uint id);
  static CComboBox*  getCBx(uint id);

private:
         void        addItems(CbxItem* items, int noItems, TBBtnCtx& ctx, bool sorted);
         bool        addRes(  uint     idr,                TBBtnCtx& ctx, bool sorted);
         void        add(CbxItem& item, TBBtnCtx& ctx, bool sorted);
         void        setCaption(TCchar* txt, TBBtnCtx& ctx);
         bool        getCurSel(String& s, int& data);   // Returns current selection of if none faile

         void        setDim(TBBtnCtx& ctx);
  };


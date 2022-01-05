// ToolBar Simulated Drop Down Menu -- Useful in dialog boxes


#include "stdafx.h"
#include "TBPopupMenu.h"
#include "TBBtnCtx.h"


TBPopupMenu::TBPopupMenu(uint id) : CMFCToolBarComboBoxButton(id, -1) { }


void TBPopupMenu::install(TBBtnCtx& ctx) {

  SetFlatMode(false);   SetCenterVert(true);   m_dwStyle = CBS_DROPDOWN | WS_VSCROLL;

  setDim(ctx);
  }


void TBPopupMenu::setCaption(uint id, TCchar* txt, TBBtnCtx& ctx) {
TBPopupMenu* popup = TBPopupMenu::get(id);

  ctx.setMaxChars(txt);

  if (popup) popup->setCaption(txt);

  popup->setDim(ctx);
  }


uint TBPopupMenu::getCmdId(uint id, TCchar* caption) {
TBPopupMenu* popup = TBPopupMenu::get(id);   if (!popup) return 0;
uint         cmdID = popup->getCmdId();      if (!cmdID) return 0;

  popup->setCaption(caption);   return cmdID;
  }


void TBPopupMenu::setCaption(TCchar* txt) {
CComboBox* cbx = GetComboBox();

  if (cbx) {cbx->Clear();  cbx->SetWindowText(txt);}
  }


uint TBPopupMenu::getCmdId() {
int i = GetCurSel();

  return i >= 0 ? GetItemData(i) : 0;
  }



TBPopupMenu* TBPopupMenu::get(uint id)
                                    {try {return (TBPopupMenu*) GetByCmd(id);}   catch (...) {return 0;}}


bool TBPopupMenu::addItems(  uint id, const CbxItem* items, int noItems, TBBtnCtx& ctx, bool sorted) {
TBPopupMenu* popup = TBPopupMenu::get(id);   if (!popup || !items) return false;

  return popup->addItems(items, noItems, ctx, sorted);
  }


bool TBPopupMenu::addItems(const CbxItem* items, int noItems, TBBtnCtx& ctx, bool sorted) {
int i;

  ctx.incNoLines();

  for (i = 0; i < noItems; i++) {
    const CbxItem& item = items[i];
    const String&  name = item.txt;
    int            id   = item.data;

    ctx.setMaxChars(name);   ctx.incNoLines();

    if (sorted) AddSortedItem(name, id);   else AddItem(name, id);
    }

  setDim(ctx);   return noItems > 0;
  }


bool TBPopupMenu::addItem(uint id, CbxItem& item, TBBtnCtx& ctx, bool sorted) {
TBPopupMenu* popup = TBPopupMenu::get(id);   if (!popup) return false;
String&      name = item.txt;
int          data = item.data;

  ctx.setMaxChars(name);   ctx.incNoLines();

  if (sorted) popup->AddSortedItem(name, data);   else popup->AddItem(name, data);

  popup->setDim(ctx);   return true;
  }



bool TBPopupMenu::addMenu(uint id, uint idr, TBBtnCtx& ctx, bool sorted) {
TBPopupMenu* popup = TBPopupMenu::get(id);   if (!popup) return false;

  return popup->addMenu(idr, ctx, sorted);
  }


bool TBPopupMenu::addMenu(uint idr, TBBtnCtx& ctx, bool sorted) {
CMenu   menu;   if (!menu.LoadMenu(idr)) return false;
uint    n = menu.GetMenuItemCount();
uint    i;
uint    id;
CString name;

  ctx.incNoLines();

  for (i = 0; i < n; i++) {
    id = menu.GetMenuItemID(i);   menu.GetMenuString(i, name, MF_BYPOSITION);

    ctx.setMaxChars(name);   ctx.incNoLines();

    if (sorted) AddSortedItem(name, id);   else AddItem(name, id);
    }

//  setCaption(caption);
  setDim(ctx);

  menu.DestroyMenu();  return true;
  }


void TBPopupMenu::clearSel() {
CComboBox* cbx = GetComboBox();

  if (cbx) cbx->SetCurSel(-1);
  }



void TBPopupMenu::setDim(TBBtnCtx& ctx) {
  m_iWidth = ctx.getHoriz() + 20;   m_nDropDownHeight = ctx.getVert();
  }


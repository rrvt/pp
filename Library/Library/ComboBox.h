// Combo Box that integrates with a Tool Bar (see ToolBar.h)
// To process the selection from combo box use the following declaration in xxxDoc.h:
//
//    protected:
//      DECLARE_MESSAGE_MAP()
//      afx_msg void OnCloseCombo();
//
// The function is located in xxxDoc.cpp and is defined by:
//
//    void xxxDoc::OnCloseCombo() {}
//
// The Message is caught by the following in xxxDoc.cpp file:
//
//    BEGIN_MESSAGE_MAP(xxxDoc, CDocument)
//      ON_CBN_CLOSEUP(ID_Cbx, &xxxDoc::OnCloseCombo)
//    END_MESSAGE_MAP()
//
// Note, the message processing may be done whereever message maps are found.

// Styles suggested for the combo box:

//   CBS_SIMPLE       The list box is displayed at all times. The current selection in the list box
//                    is displayed in the edit control.

//   CBS_DROPDOWN     Similar to CBS_SIMPLE, except that the list box is not displayed unless the
//                    user selects an icon next to the edit control.

//   CBS_DROPDOWNLIST Similar to CBS_DROPDOWN, except that the edit control is replaced by a
//                    static-text item that displays the current selection in the list box.

//   CBS_SORT         Automatically sorts strings entered into the list box.

#pragma once
#include "IterT.h"


class ComboBox;
typedef ObjIterT<ComboBox, String> CBIter;


class ComboBox : public CComboBox {
int i;
int n;

public:

  ComboBox() : i(0), n(0) {}

  void clear();
  bool getWindowText(String& s);
  bool getCurSel(String& s);
  bool setCurSel(TCchar* s);
  void setFocus() {SetFocus();}
  void del(String& s);
  void add(String& s);
  int  find(TCchar* s);

private:

  bool getText(int i, String& s);

  String* getDatum(int i, String& s);               // returns either a pointer to data (or datum)
                                                    // at index i in array or zero
  int   nData() {return GetCount();}                // returns number of data items in array

  friend typename CBIter;
  };


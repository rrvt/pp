// Extensions ordinarily printed


#include "pch.h"
#include "Extension.h"
#include "filename.h"
#include "IniFile.h"


// Locals

static TCchar* Globals    = _T("Globals");
static TCchar* Extensions = _T("Extensions");
static String  defaultExt = _T("c h cpp asm txt bat");

// Global

Extension extension;


Extension::Extension() : ignoreExt(false) { }


void Extension::initialize() {
TokenString tokStg;
String      tok;

  if (!iniFile.readString(Globals, Extensions, tokStg))
                       {tokStg = defaultExt;   iniFile.writeString(Globals, Extensions, tokStg);}

  while (tokStg.next(tok, _T(" \t"))) data += tok;
  }



bool Extension::isLegal(TCchar* name) {
String  extension = getExtension(name);   if (extension.isEmpty()) return true;
ExtIter iter(*this);
String* s;

  if (ignoreExt) return true;

  for (s = iter(); s; s = iter++) if (extension == *s) return true;

  return false;
  }



void Extension::readExtensions(Cstring& cs) {

  if (!iniFile.readString(Globals, Extensions, cs)) cs = defaultExt;
  }


void Extension::writeExtensions(Cstring& cs) {
  iniFile.writeString(Globals, Extensions, cs);
  }


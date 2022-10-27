// Extensions ordinarily printed


#include "stdafx.h"
#include "Extension.h"
#include "filename.h"
#include "IniFile.h"


// Locals

static TCchar* Globals    = _T("Globals");
static TCchar* Extensions = _T("Extensions");
static String  defaultExt = _T("c h cpp asm txt bat");

// Global

Extension extension;


Extension::Extension() : nExt(0), ignoreExt(false) { }


void Extension::initialize() {
TokenString tokStg;
String tok;

  if (!iniFile.readString(Globals, Extensions, tokStg))
                       {tokStg = defaultExt;   iniFile.writeString(Globals, Extensions, tokStg);}

  for (nExt = 0; tokStg.next(tok, _T(" \t")); nExt++) ext[nExt] = tok;
  }



bool Extension::isLegal(TCchar* name) {
int    i;
String extension = getExtension(name);

  if (ignoreExt) return true;

  if (extension.isEmpty()) return true;

  for (i = 0; i < nExt; i++) if (extension == ext[i]) return true;

  return false;
  }



void Extension::readExtensions(Cstring& cs) {

  if (!iniFile.readString(Globals, Extensions, cs)) cs = defaultExt;
  }


void Extension::writeExtensions(Cstring& cs) {
  iniFile.writeString(Globals, Extensions, cs);
  }


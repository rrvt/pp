

pprint.chm : *.htm pprint.hhp pprint.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" pprint


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F pprint.chm


Release/pprint.chm : pprint.chm
  copy $(MAKEDIR)\pprint.chm  $(MAKEDIR)\..\Release\pprint.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del pprint.chm
  cd $(MAKEDIR)


Debug/pprint.chm : pprint.chm
  copy $(MAKEDIR)\pprint.chm  $(MAKEDIR)\..\Debug\pprint.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del pprint.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/pprint.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/pprint.chm



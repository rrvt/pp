# pp -- Print Program(s)

Two versions of the same application, on callable from CommandLine (i.e. the Dos Box) and one a windows
version.  The goal is to produce a printed output where chunks of code separated by two lines from other
chunks of code appear on one page in so far as it is practical for that to happen.  If a chunk is too big
to fit on a page, then pick a single blank line to break the page, and so on...

## Getting Started

This version was created with Visual Studion 2017.  It was compiled with the following properties:

  o Windows SDK Version: 10.0.18362.0
  o Platform Toolset: visual Studio 2017 (v141)
  o MFC: Use MFC in a Shared DLL
  o Character Set:  Use Unicode Character Set
  o Precompiled Header:  Not Using Precompiled Headers
  o Linker/Additional Dependencies:  Htmlhelp.lib.

The HTML Help Workshop (HHW), Version 4.74.8702.0 was used to prepare the help file (WixApp.chm).  It is
copied into the Release directory.  I used Dreamweaver (DW) to do most of the content production of the
help files that the HTML Help Workshop produces (i.e. HHW is used to produce the pages/files needed
and DW is used to fill in the content).

Additionally the WIX Installer, The very old Help Workshop and SlickEdit were used to process the code.
The Product (Wix installation file) was produced by my WixApp but it can be manipulated by
hand for changes.

### Prerequisites

The following tools must be available to build these applications:

  o Visual Studio 2017 (VS17) or later.
  o The WiX Toolset must be installed in Visual Studio.
  o The "HTML Help Workshop" (google it) must be installed.

Optional Tools:

  o WixApp -- Application to produce a Wix Product.wxs file (see GitHub)

### Build Procedure

Build in SlickEdit or VS17:

  o Find the Solution file: .../Sources/pp/pp/pp.sln.
  o Open the Solution File in VS17 or SlickEdit
  o Optional -- Execute command Build/Clean Solution
  o Execute command Build/Build Solution

If all the prequisites are available then it should compile and link all products into the current
configuration directory (e.g. .../Sources/pp/Debug/, or .../Sources/pp/Release/).  All the build products
are contained in the configuration directory or subdirectories of the the configuration directory.

### Installing

The /Release/Install_pprint.msi will install the the pprint windows application.
The /Release/Install_pp.msi will install the pp command line application.

## Testing

Since this produces a printed output it would be best in the early stages to set the default printer to
a printer that creates an Adobe pdf file.  Then mistakes will result in a file that can be easily deleted.

The command line version, pp, takes a list of files with wild cards and some command modifiers.  Read the
help file for details.  It only knows about files in the current directory unless a path is included in
the name.  Failure to find the file to be printed will just result in nothing happening.  Here is a
typical sequence:

  o cd .../Source/pp.prj
  o pp *.h *.cpp

The output of a slew of files will be output to the default printer (be warned).

The windows version emulates the command line version by using a dialog box with buttons, check boxes and
edit boxes (for the list of files).  The windows version produces a printer dialog box so the printer may
be selected just prior to the output of the files.

However, every printer is different and the presentation on the page is configurable.  In the Options
menu are commands to configure the printed output on the page in the X-axis and the Y-axis.  Essentially
one chooses the number of characters/line, the number of lines/page and the size of all the margins.
Unfortunately every printer (including the pdf printer) is different so the applications provide
mechanisms to try out various values and observe their effects.  Some assistance is given by the
application for the right and bottom margin values.  Since the pixel density is unique to each
printer the values chosen do not represent inches or even pixels.  The help file in pprint should help
pick values...

## Authors

Robert R. Van Tuyl

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

# pp -- Print Program

This is the Command Line (i.e. the Dos Box) version of the print program.  The goal is to produce
a printed output where chunks of code separated by two lines from other chunks of code appear on
one page in so far as it is practical for that to happen.  If a chunk is too big
to fit on a page, then pick a single blank line to break the page, and so on...

## Getting Started

This version was created with Visual Studion 2017.  It was compiled with the following properties:

  - Windows SDK Version: 10.0.18362.0
  - Platform Toolset: visual Studio 2017 (v141)
  - MFC: Use MFC in a Shared DLL
  - Character Set:  Use Unicode Character Set
  - Precompiled Header:  Not Using Precompiled Headers
  - Linker/Additional Dependencies:  Htmlhelp.lib.

The HTML Help Workshop (HHW), Version 4.74.8702.0 was used to prepare the help file (WixApp.chm).
It is copied into the Release directory.  I used Dreamweaver (DW) to do most of the content
production of the help files that the HTML Help Workshop produces (i.e. HHW is used to produce the
pages/files needed and DW is used to fill in the content).

Additionally the WIX Installer, The very old Help Workshop and SlickEdit were used to process the
code.  The Product (Wix installation file) was produced by my WixApp but it can be manipulated by
hand for changes.

### Prerequisites

The following tools must be available to build these applications:

  - Visual Studio 2017 (VS17) or later.
  - The WiX Toolset must be installed in Visual Studio.
  - The "HTML Help Workshop" (google it) must be installed.

Optional Tools:

  - WixApp -- Application to produce a Wix Product.wxs file (see GitHub)

### Build Procedure

Build in SlickEdit or VS17:

  - Find the Solution file: .../Sources/pp/pp/pp.sln.
  - Open the Solution File in VS17 or SlickEdit
  - Optional -- Execute command Build/Clean Solution
  - Execute command Build/Build Solution

If all the prequisites are available then it should compile and link all products into the current
configuration directory (e.g. .../Sources/pp/Debug/, or .../Sources/pp/Release/).  All the build
products are contained in the configuration directory or subdirectories of the the configuration
directory.

### Installing

The /Release/Install_pprint.msi will install the the pprint windows application.
The /Release/Install_pp.msi will install the pp command line application.

## Testing

Since this produces a printed output it would be best in the early stages to set the default
printer to a printer that creates an Adobe pdf file.  Then mistakes will result in a file that can
be easily deleted.

The command line version, pp, takes a list of files with wild cards and some command modifiers.
Read the help file for details.  It only knows about files in the current directory unless a path
is included in the name.  Failure to find the file to be printed will just result in nothing
happening.  Here is a typical sequence:

  - cd .../Source/pp.prj
  - pp *.h *.cpp

The output of a slew of files will be output to the default printer (be warned).

However, every printer is different and the presentation on the page is configurable.  In the
Options menu are commands to configure the printed output on the page in the X-axis and the Y-axis.
Essentially one chooses the number of characters/line, the number of lines/page and the size of
all the margins.  Unfortunately every printer (including the pdf printer) is different so the
applications provide mechanisms to try out various values and observe their effects.  Some
assistance is given by the application for the right and bottom margin values.  Since the pixel
density is unique to each printer the values chosen do not represent inches or even pixels.  The
help file in pprint should help pick values...

##Updates

### Update 6/28/24

Moved the windows version to a separate directory.  Added MIT License to installation.

### Update 2/17/24

Reorganized the Library so that it compiles once into Debug and Release directories under the
Library directory.

### Update 1/7/24

Library and other changes.

### Update 12/26/23

Library Update

### Update 7/3/23

Library update and fix About Command.

### Update 3/30/23

Update Library.

### Update 10/26/22

Added position and size logic.  Updated the dialog box and toolbar backgrounds.

### Update 8/3/22

Minor Library Update.

### Update 4/15/22

Big adventure in February when I started moving to a new Win11 and Visual Studio 2022.  I now
feel that this version is working in the new environment.  There were several changes made to the app
in order to compile properly on VS22.

### Update 01/31/22

Updates to the library, mostly about the toolbar, but also NewAllocator, and a minor addition to
Expandable.

Also scrubbed the project files to remove all references to precompiled header files which I turned off
in VS17.  Unfortnately VS does not remove all references and pch files kept cropping up.  Not only does
that slow down the compiler but the files are large...

## Authors

Robert R. Van Tuyl

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


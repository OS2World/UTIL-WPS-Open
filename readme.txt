Open 2.01                     (C) 1997 Samuel Audet <guardia@cam.org>

THIS IS A FREEWARE UTILITY!!  Please send an e-mail if are using this
program, thank you!  If you can spare some money for a pre-university
student, it would be very much appreciated.

Introduction
============

This OS/2 command line utility lets you open objects the command line as if
you opened them from the WPS.

I also recommend the contrary to this utility (ie.: opening command lines
from folders), Command Folder.  You can get a copy on my web page
http://www.cam.org/~guardia

Installation
============

To be able to filter the contents of a folder using open.exe, you will need
to register a new folder class found in WPSExtS.dll.  This DLL also
includes a fix to the background open.  If you want to install both or
either of them, you will need OS/2 Warp 3 or higher and will need to run
"reg.exe i". It is preferable that the DLL be placed in a system DLL
directory (for example x:\os2\dll), unless you specify a directory, ex.:
"reg.exe i x:\open" This is the same DLL than in Hot Corners 2.0 package,
but register with reg.exe just to be sure everything is OK for Open.
Current version of WPS Extention DLL is 1.0, I will try to make all new
versions backward compatible.

Note that the Include page in folder's setting pages is the solution for a
permanent filtering since open.exe filtering is dismissed on folder close.

Usage
=====

open [/?] [/F filter] [/Oview] [objects] [/F filter] [/Oview] [objects] ...

where

  [/?]        shows this help screen.
  [/F filter] specifies a title wildcard filter for folder objects.
  [/Oview]    specifies the view to open.  Possible views are:
                   blank : default view (same as double-click),
                       P : properties view,
                       I : icon view,
                       T : tree view, and
                       D : details view.
  [objects] are the names of the objects to open (file system name or
            object IDs).  Wildcards and multiple entries are accepted!

The specified objects will be opened as if they were opened from the WPS.
If no parameters are specified, the current directory is opened as a
folder, with default view and no filter.

Of course, some of the view options only apply to folders.

To have a full list of Object IDs available on your system, run
objectid.cmd provided, you will be able to guess most of them.  Various
utilities including UniMaintenance and Object Desktop can determine the
Object ID of an object.  Object IDs are useful because not all objects are
found as files or directories. Object IDs specified on open.exe command
will need to be in quotes because < and > characters are normally used for
output and input redirection on the command line.  Remember that Object IDs
are CaSe SeNsItIvE.

A '-' can be used instead of a '/' for options, and the options are case
insensitive.  The options are also "linear".  This means they will take
effect on all objects following the declaration of this option and not on
the ones preceding it.

The return code indicates how many error occured (ie.: how many objects
were not successfully opened).

ex.:  [C:\open]open "<WP_OS2SYS>" f:\config.0?? e:\gif\naughty\*.gif i: g:\ /F *.zip c:\incoming /od . ..

      In order, it will open the "OS/2 System" folder, all files matching
      f:\config.0?? and e:\gif\naughty\*.gif, drive i:, drive g:, folder
      c:\incoming with *.zip filter (only showing ZIP files), and the current
      directory and the parent directory in details view with *.zip filter.

For Programmers
===============

If you want to include folder filtering or the background open fix in your
own program, read wpsext.doc.

Known bugs or limitations
=========================

- Icons position are not retained when using folder filtering.
- Sometimes, the filtering routine goes mad and filters everything out...
  if you manage to get a reproducable situation, let me know.

Legal stuff
===========

This freeware product is used at your own risk, although it is highly
improbable it can cause any damage.

If you plan on copying me, please give me the credits, thanks.

Contacting the author
=====================

Samuel Audet

E-mail:    guardia@cam.org
Homepage:  http://www.cam.org/~guardia
IRC nick:  Guardian_ (be sure it is I before starting asking questions though)

Snail Mail:

   377, rue D'Argenteuil
   Laval, Quebec
   H7N 1P7   CANADA


Thanks for using this wonderful product!


Original README
---------------

Open - a useful OS/2 WPS utility.

I first wrote this little utility basically because I discovered
how to use the WinSetObjectData API to open a Workplace Shell
object, and I thought it was cool.	It has since turned out to be
an extremely handy little tool, which is not bad for something
whose source code is a whopping 33 lines long, including the
help.

What does it do?  Basically, it opens WPS objects, using their
default open setting.  So, for example, you can type

open c:\os2

and it will open the drives folder for c:\os2.	Even handier, typing

open .

will open the drives folder for whatever the current directory you
are in is.	I tend to use this when I have been doing some stuff from
the command line, and suddenly want to delete a bunch of subdirectories,
which is a lot easier to do from the WPS than from the command line.
This saves navigating all the way through the drives object to get
to the folder you want.

Another handy use is if you want to be able to open a folder
from an object's menu.  There is no way to add a folder object to a menu
normally, but if you create a little dummy program object that uses
open.exe to open the folder, you can put _that_ on the menu, and
get the same result.

The other really cool thing you can do is something like

open os2.bmp

This will automatically run whatever the program associated with os2.bmp
is (usually either Windows Paint or the icon editor, but on my system
I have changed it so that bmps are associated with PMView) and load
os2.bmp into it automatically.	Basically, it is the same as
double-clicking on the file object for os2.bmp.

So, anyway, I hereby release this little utility as freeware.  I couldn't
see charging any money for something this simple.  The source code is
included if you want to monkey with it.  However, you may not charge
anyone for this software, other than a reasonable fee for duplication,
and all such other legal mumbo-jumbo that is normally associated
with freeware.

Please feel free to send me e-mail if you like this little program, or
if you have any questions.

-- Rob McDermid
rmcderm@ibm.net



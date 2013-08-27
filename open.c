/* Open 2.01  (C) 1997 Samuel Audet <guardia@cam.org> */

#define INCL_DOS
#define INCL_WINSWITCHLIST
#define INCL_WINWORKPLACE
#include <os2.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

/* just to get OPEN constants */
#include <wpdisk.h>
#include <wpfolder.h>
#include <wpobject.h>

int getAndOpen(char *path, char *filename, char *filter, ULONG view);
void DisplayHelp(void);
BOOL _System SwitchToObject(HOBJECT hobj, ULONG view, ULONG timeout, BOOL wait);

int main(int argc, char *argv[])
{

   int i,  /* loop index */
       rc; /* return code variable counter in the for loop */
   char *filter = NULL;       /* pointer to a user specified filter */
   ULONG view = OPEN_DEFAULT; /* default openview */

   /* used for wildcards support */
   HDIR         searchHandle = HDIR_SYSTEM;
   ULONG        onefile = 1;
   FILEFINDBUF3 searchBuf;
   ULONG        allfiles = FILE_ARCHIVED | FILE_DIRECTORY | FILE_SYSTEM |
                           FILE_HIDDEN   | FILE_READONLY;
   char *path;

/* check for no parameter -> open current dir */
	if (argc < 2)
      return getAndOpen(NULL,".",NULL,view);
/* check for help parameter -> display help */
   else if (argv[1][1] == '?')
   {
      DisplayHelp();
      return 0;
   }

   printf("\n");

/* check every parameters */

   for(i = 1, rc = 0; i < argc; i++)
   {
      /* strip the non-standard trailing backslash */
      if(*(strchr(argv[i],'\0') - 1) == '\\' && strlen(argv[i]) > 1) *(strchr(argv[i],'\0') - 1) = '\0';

      /* process options starting with - or / */
      if ((argv[i][0] == '/') || (argv[i][0] == '-'))
         switch(toupper(argv[i][1]))
         {
             case 'F':  filter = argv[++i]; break;
             case 'O':  switch(toupper(argv[i][2]))
                        {
                           case 'P' : view = OPEN_SETTINGS; break;
                           case 'I' : view = OPEN_CONTENTS; break;
                           case 'T' : view = OPEN_TREE; break;
                           case 'D' : view = OPEN_DETAILS; break;
                           default  : view = OPEN_DEFAULT; break;
                        }
                        break;
         }

   /* special processing for special filename . and ..                   */
   /* The wild card routines mucks them up, so I send them directly into */
   /* processing.                                                        */

      else if (!strcmp(argv[i],".") || !strcmp(argv[i],".."))
         rc += getAndOpen(NULL,argv[i],filter,view);

   /* another special treatement for drive roots, gotta love Microsoft
      for that one checks for either "x:", "x:\" and "\" type parameter */

      else if (
        ((argv[i][1] == ':') && (argv[i][2] == '\0')) ||
        (((argv[i][1] == ':') && (argv[i][2] == '\\')) && (argv[i][3] == '\0')) ||
        ((argv[i][0] == '\\') && (argv[i][1] == '\0'))
               )
         rc += getAndOpen(NULL,argv[i],filter,view);

   /* special treatement for Object IDs ex.: <WP_DESKTOP> */

      else if ((argv[i][0] == '<') && (*(strchr(argv[i],'\0')-1) == '>'))
         rc += getAndOpen(NULL,argv[i],filter,view);

   /* else start wildcard search */

      else
      {
         onefile = 1;
         if (!DosFindFirst(argv[i], &searchHandle, allfiles, &searchBuf,
                           sizeof(searchBuf), &onefile, FIL_STANDARD))
         {

         /* find the original path to give to the opener */

            if ((path = strrchr(argv[i],'\\')) || (path = strrchr(argv[i],':')))
            {
               *++path = '\0';
               path = argv[i];
            }
            do
               rc += getAndOpen(path,searchBuf.achName,filter,view);
            while (!DosFindNext(searchHandle, &searchBuf, sizeof(searchBuf), &onefile));
         }
         else
         {
            printf("%s: No file or directory found.\n",argv[i]);
            rc++;
         }
      }
   }

   return rc;

}


/* get object handle for the filename and open it in the WPS */

int getAndOpen(char *path, char *filename, char *filterraw, ULONG view)
{
   
   char fullfilename[CCHMAXPATH],
        filter[CCHMAXPATH],
        *temp;
   HOBJECT hobj;

/* patch together the path and filename, if it is present */
   if (path)
   {
      strcpy(fullfilename, path);
      strcat(fullfilename, filename);
   }
   else strcpy(fullfilename, filename);

/* make "FILTER=filter" */
   if (filterraw)
   {
      strcpy(filter,"FILTER=");
      strcat(filter,filterraw);
   }
   else *filter = '\0';

/* Get the fully qualified path name and handle of the file found */

   DosQueryPathInfo(fullfilename, FIL_QUERYFULLNAME, fullfilename, 2048);
   printf("Opening: %s\n",fullfilename);
   if ((hobj = WinQueryObject(fullfilename)) == NULLHANDLE)
   {
      printf("%s: Object not found.\n",fullfilename);
      return 1;
   }

/* Set filter and Open the object */

   if (*filter)
      WinSetObjectData(hobj,filter);

            /* if (!WinOpenObject(hobj,view,TRUE)) */

   /* buggy WinOpenObject makes the PMSHELL jam trying to drag an object to
      NS/2 window from a folder opened with it :( */

   switch(view)
   {
      case OPEN_DEFAULT:  temp = "OPEN=DEFAULT";  break;
      case OPEN_SETTINGS: temp = "OPEN=SETTINGS"; break;
      case OPEN_TREE:     temp = "OPEN=TREE";     break;
      case OPEN_CONTENTS: temp = "OPEN=ICON";     break;
      case OPEN_DETAILS:  temp = "OPEN=DETAILS";  break;
   }

   if (!WinSetObjectData(hobj,temp))
   {
      printf("%s%s: Object not successfully opened.\n",path,filename);
      return 1;
   }
   else SwitchToObject(hobj, view, 10, TRUE);

   return 0;
}


void DisplayHelp(void)
{
   printf(

"Open 2.01    (C) 1997 Samuel Audet <guardia@cam.org>\n"
"Freeware, please send an e-mail if you are using this program.               \n\n"
"Usage:                                                                         \n"
"  open [/?] [/F filter] [/Oview] [objects] [/F filter] [/Oview] [objects] ...\n\n"
"where                                                                        \n\n"
"  [/?]        shows this help screen.                                          \n"
"  [/F filter] specifies a title wildcard filter for folder objects.            \n"
"  [/Oview]    specifies the view to open.  Possible views are:                 \n"
"                   blank : default view (same as double-click),                \n"
"                       P : properties view,                                    \n"
"                       I : icon view,                                          \n"
"                       T : tree view, and                                      \n"
"                       D : details view.                                       \n"
"  [objects] are the names of the objects to open (file system name or          \n"
"            object IDs).  Wildcards and multiple entries are accepted!       \n\n"
"The specified objects will be opened as if they were opened from the WPS.      \n"
"If no parameters are specified, the current directory is opened as a folder,   \n"
"with default view and no filter.                                               \n"

   );
}

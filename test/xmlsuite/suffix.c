/*****************************************************************************/
/*  LibreDWG - free implementation of the DWG file format                    */
/*                                                                           */
/*  Copyright (C) 2010 Thien-Thi Nguyen                                      */
/*  Copyright (C) 2014, 2018 Free Software Foundation, Inc.                  */
/*                                                                           */
/*  This library is free software, licensed under the terms of the GNU       */
/*  General Public License as published by the Free Software Foundation,     */
/*  either version 3 of the License, or (at your option) any later version.  */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    */
/*****************************************************************************/

/*
 * suffix.c: avoid hardcoded input/output filenames
 * written by Thien-Thi Nguyen
 * modified by Achyuta Piyush
 * modified by Reini Urban
 */

#include "config.h"
#include <stdio.h>
#include <libgen.h>
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1 /* for strdup */
#endif
#include <string.h>
#include <stdlib.h>

char * suffix (const char *filename, const char *ext);

/* Return a newly `malloc'ed string made from "re-suffixing" FILENAME with
   ".EXT" (note dot).  That is, when FILENAME has the form "STEM.dwg" the
   value is "STEM.EXT", otherwise the value is "FILENAME.EXT".

   Caller should `free' the returned string when done using it.  */
char *
suffix (const char *filename, const char *ext)
{
  char *copy = strdup (filename);
#ifdef HAVE_BASENAME
  char *base = basename (copy);
#else
  char *base = copy;
#endif
  int len = strlen (base) + 1 + strlen (ext) + 1;
  char *rv = malloc (len);
  char *dot;

  if ((dot = strrchr (base, '.'))
      && dot + 4 < base + len && !strncmp (1 + dot, "dwg", 3))
    *dot = '\0';
  snprintf (rv, len, "%s.%s", base, ext);
  free (copy);
  return rv;
}

#define REQUIRE_INPUT_FILE_ARG(argc)            \
  do                                            \
    {                                           \
      if (2 == argc)                            \
        {                                       \
          puts ("No input file specified");     \
          return 1;                             \
        }                                       \
    }                                           \
  while (0)

/* suffix.c ends here */

/* basepdefs.h

   This file contains many of the defines needed for Base practice
   and not for anything else.

*/
#ifndef _h_basepdefs
#define _h_basepdefs


#include "defs.h"

/* System dependend setups */

#ifdef CHECK_ENV
#define ROBODIR(RFILE) ( strdup(strcat(strcpy(robofile, Robodir), RFILE)))
#else
#define ROBODIR(RFILE) (LIBDIR "/" N_ROBODIR RFILE)
#endif

#define RCMD            "/usr/bin/X11/xon"
#define OROBOT          ROBODIR("/robot")
#define NICE            "nice -1"
#define REMOTEHOST      "localhost"
#define LOGFILE		ROBODIR("")
#define COMFILE 	ROBODIR("/og")
#define DOGFILE 	ROBODIR("/dog")
#define BASEFILE        ROBODIR("/base")
#define DEFFILE		ROBODIR("/df")

/* Basepractice specific additions */

#define PORT 2592

#define HOWOFTEN 1                       /*Robot moves every HOWOFTEN cycles*/
#define PERSEC (1000000/UPDATE/HOWOFTEN) /* # of robo calls per second*/

#define ROBOCHECK (300*PERSEC)		/* Check if only robots are in game */
#define SENDINFO  (120*PERSEC)		/* send info to all */

#endif /* _h_basepdefs */


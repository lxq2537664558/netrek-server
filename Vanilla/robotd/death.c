/*
 * death.c
 */
#include "copyright.h"

#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/types.h>
#ifdef hpux
#include <time.h>
#else hpux
#include <sys/time.h>
#endif hpux
#include "defs.h"
#include "struct.h"
#include "data.h"
#include "robot.h"

extern jmp_buf env;

static struct itimerval udt;
static char *teamstring[9] = {"", "and the Federation",
			 "and the Romulan Empire", "",
			 "and the Klingon Empire", "", "", "",
			 "and the Orions"};

death()
{
    char buf[80];
    int ghost = 0;

#ifdef nodef
    /* Reset the signal */
    signal(SIGALRM, SIG_IGN);
    udt.it_interval.tv_sec = 0;
    udt.it_interval.tv_usec = 0;
    udt.it_value.tv_sec = 0;
    udt.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &udt, 0);
    signal(SIGALRM, SIG_DFL);
#endif nodef

    switch (me->p_whydead) {
    case KQUIT:
	mprintf("You have self-destructed.");
	break;
    case KTORP:
	mprintf("You were killed by a photon torpedo from %s (%c%c).",
	    players[me->p_whodead].p_name,
	    teamlet[players[me->p_whodead].p_team],
	    shipnos[me->p_whodead]);
	break;
    case KPLASMA:
	mprintf("You were killed by a plasma torpedo from %s (%c%c)",
	    players[me->p_whodead].p_name,
	    teamlet[players[me->p_whodead].p_team],
	    shipnos[me->p_whodead]);
	break;
    case KPHASER:
	mprintf("You were killed by a phaser shot from %s (%c%c)",
	    players[me->p_whodead].p_name,
	    teamlet[players[me->p_whodead].p_team],
	    shipnos[me->p_whodead]);
	break;
    case KPLANET:
	mprintf("You were killed by planetary fire from %s (%c)",
	    planets[me->p_whodead].pl_name,
	    teamlet[planets[me->p_whodead].pl_owner]);
	break;
    case KSHIP:
	mprintf("You were killed by an exploding ship formerly owned by %s (%c%c)",
	    players[me->p_whodead].p_name,
	    teamlet[players[me->p_whodead].p_team],
	    shipnos[me->p_whodead]);
	break;
    case KDAEMON:
	mprintf("You were killed by a dying daemon.");
	break;
    case KWINNER:
	mprintf("Galaxy has been conquered by %s (%c%c) %s",
	    players[me->p_whodead].p_name,
	    teamlet[players[me->p_whodead].p_team],
	    shipnos[players[me->p_whodead].p_no],
	    teamstring[players[me->p_whodead].p_team]);
	break;
    case KGHOST:
	mprintf("You were killed by a confused daemon.");
	ghost++;
	break;
    case KGENOCIDE:
	mprintf("Your team was genocided by %s (%c%c) %s.",
	    players[me->p_whodead].p_name,
	    teamlet[players[me->p_whodead].p_team],
	    shipnos[me->p_whodead],
	    teamstring[players[me->p_whodead].p_team]);
	break;
    case KPROVIDENCE:
	mprintf("You were removed from existence by divine mercy.");
	break;
    default:
	mprintf("You were killed by something unknown to this game?");
	break;
    }
    /*
    warning(buf, 1);
    */
    /* First we check for promotions: */
    if (promoted) {
	mprintf("Congratulations!  You have been promoted to %s", 
	    ranks[mystats->st_rank].name);
	promoted=0;
    }
    if(ghost && (_state.player_type == PT_OGGER || _state.player_type ==
      PT_DOGFIGHTER))
      exitRobot(0);

    longjmp(env, 0);
}

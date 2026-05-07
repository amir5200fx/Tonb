#pragma once
#ifndef _improve_header
#define _improve_header
#include "Starbase.h"
#include "top.h"
/*****************************************************************************/
/*                                                                           */
/*  driver functions to direct mesh improvement                              */
/*                                                                           */
/*****************************************************************************/

/* see if new means contains any better means. if so,
   update best means and return true */
bool meanimprove(starreal bestmeans[],
    starreal newmeans[],
    int passtype);

/* run a pass (smoothing, topo, insertion). return true
   if we have reached the desired quality */
bool pass(int passtype,
          tetcomplex* mesh,
          arraypoolstack* tetstack,
    starreal threshold,
    bool* minsuccess,
    bool* meansuccess,
    int passnum,
    starreal bestmeans[],
          behavior* behave,
          inputs* in,
          proxipool* vertexpool,
    int argc,
    char** argv);

/* pre-improvement initialization code */
void improveinit(tetcomplex* mesh,
                 proxipool* vertexpool,
                 arraypoolstack* tetstack,
                 behavior* behave,
                 inputs* in,
                 int argc,
                 char** argv,
                 starreal bestmeans[NUMMEANTHRESHOLDS]);

/* clean up after mesh improvement */
void improvedeinit(tetcomplex* mesh,
                   proxipool* vertexpool,
                   arraypoolstack* tetstack,
                   behavior* behave,
                   inputs* in,
                   int argc,
                   char** argv);

/* top-level function to perform static mesh improvement */
void staticimprove(behavior* behave,
                   inputs* in,
                   proxipool* vertexpool,
                   tetcomplex* mesh,
                   int argc,
                   char** argv);


#endif
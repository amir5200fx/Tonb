#pragma once
#ifndef _interact_header
#define _interact_header
#include "top.h"
/*****************************************************************************/
/*      Routines to interact with the user                                   */
/*****************************************************************************/

/* print out all the improvement settings */
void printimproveoptionsstream(FILE* o, improvebehavior* b);
void printimproveoptions(improvebehavior* b);

void parseimproveconfig(char* filename, improvebehavior* b);
void parseimprovecommandline(int argc, char** argv, improvebehavior* b);

#endif
#pragma once
#ifndef _arraypoolstack_header
#define _arraypoolstack_header
#include "Starbase.h"
/*****************************************************************************/
/*                                                                           */
/*  arraypoolstack                                                           */
/*                                                                           */
/*  This is a simple stack implementation based on arraypools.               */
/*                                                                           */
/*****************************************************************************/

/* initialize stack data structure */
void stackinit(struct arraypoolstack* stack, arraypoolulong objectbytes);

/* reset stack data structure */
void stackrestart(arraypoolstack* stack);

/* free the stack data structure */
void stackdeinit(arraypoolstack* stack);

/* push a new element on the stack, return pointer where new element
   should go */
void* stackpush(arraypoolstack* stack);

/* fetch the address of the top stack item */
void* stackpop(arraypoolstack* stack);

/* convenience struct to use standard library quick sort funtion */
struct sorttet
{
    starreal qual;
    tag id;
};

/* compare two starreal numbers as qualities of tets to be sorted */
int comparesorttets(const void* a, const void* b);

/* function to sort an array of reals */
void qsorttets(sorttet* array,
               int arraylength);

/* sort stack from worst quality to best */
/* TODO do in-place sort of arraypool? */
void sortstack(arraypoolstack* stack);

/* exactly copy one stack to another */
void copystack(arraypoolstack* fromstack,
               arraypoolstack* tostack);

/* permute the order of a tet's vertices so that edge[0], edge[1]
   are the first two vertices */
void permuteedge(tetcomplex* mesh,
                 tag tet[4],
                 int edge[2]);

/* peer into a stack of tets to see if a tet starting with edge (vtx1, vtx2)
   is in there somewhere */
bool tetinstackedge(arraypoolstack* tetstack,
                    tag vtx1, tag vtx2);

/* given a mesh and a minimum and maximum edge length,
   fill two stacks with tets edges shorter than the minimum
   or longer than the maximum. Each unique edge is represented
   in just one tet. Order the vertices in the tets
   such that the too short (too long) edge comes first */
void filledgestacks(tetcomplex* mesh,
                    arraypoolstack* longstack,
                    arraypoolstack* shortstack,
                    starreal minlength,
                    starreal maxlength,
                    starreal* minedge,
                    starreal* maxedge,
                    starreal* meanedge);

/* given a mesh and a quality threshold,
   return a stack of tets with quality
   at or below that threshold. this function
   assumes that the stack has already been
   initialized. */
//void fillstackqual(tetcomplex* mesh,
//                   arraypoolstack* stack,
//                   int qualmeasure,
//                   starreal threshold,
//                   starreal meanquals[],
//                   starreal* minqual);

/* given a mesh and a percentage p,
   return the worst numtets * p tets in the mesh */
void fillstackpercent(tetcomplex* mesh,
                      arraypoolstack* stack,
                      int qualmeasure,
                      starreal percent,
                      starreal meanquals[],
                      starreal* minqual);

/* run through a stack of tets, initializing each vertex with
   a flag indicating that it has not yet been smoothed */
void initsmoothedvertlist(arraypoolstack* tetstack,
                          arraypool* vertlist);

/* peer into a stack of tets to see if a tet starting with vtx
   is in there somewhere */
bool tetinstackfirstvert(arraypoolstack* tetstack,
                         tag vtx);

/* peer into a stack of vertices to see if a particular tag is present */
bool vertinstack(arraypoolstack* vertstack,
                 tag vtx);

/* peer into a stack of tets to see if a tet
   is in there somewhere */
bool tetinstack(arraypoolstack* tetstack,
                tag v1,
                tag v2,
                tag v3,
                tag v4);

/* append the contents of one stack to the top of another */
/* only adds tets if they do not already exist in tostack */
void appendstack(arraypoolstack* fromstack,
                 arraypoolstack* tostack);

/* compute the mean and minimum element
   qualities in the meash (multiple thresholded means) */
void meshquality(tetcomplex* mesh,
                 int qualmeasure,
                 starreal* meanqual,
                 starreal* minqual);

/* return the worst quality of all elements in the mesh */
double worstquality(tetcomplex* mesh);

/* find the meand and minimum qualities
   of all the tets in the stack (that still exist) */
void stackquality(tetcomplex* mesh,
                  arraypoolstack* tetstack,
                  int qualmeasure,
                  starreal meanqual[],
                  starreal* minqual);

/* find the longest and shortest edge length in a stack of tets */
void longshortstack(tetcomplex* mesh,
                    arraypoolstack* tetstack,
                    starreal* longest,
                    starreal* shortest);

/* find the worst quality of all the tets in the stack (that still exist) */
starreal worststackquality(tetcomplex* mesh,
                           arraypoolstack* tetstack,
                           int qualmeasure);

/* print out all the tets in a stack */
void printstack(tetcomplex* mesh,
                arraypoolstack* tetstack);
#endif
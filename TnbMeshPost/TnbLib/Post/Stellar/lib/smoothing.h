#pragma once
#ifndef _smoothing_header
#define _smoothing_header
#include "Starbase.h"
/*****************************************************************************/
/*                                                                           */
/*  smoothing functions                                                      */
/*                                                                           */
/*****************************************************************************/

/* given two values a and b and their gradients, compute the
   gradient of their product grad(a*b) */
void gradproduct(starreal a,
    starreal b,
    starreal grada[3],
    starreal gradb[3],
    starreal prod[3]);

/* given two values top and bottom and their gradients, compute the
   gradient of their quotient grad(top / bottom) */
void gradquotient(starreal top,
    starreal bot,
    starreal gradtop[3],
    starreal gradbot[3],
    starreal quot[3]);

/* get the information about this tet needed for non-smooth
   optimization of the current quality measure */
void getoptinfo(tetcomplex* mesh,
                struct opttet* opttet,
                int vtxkind,
                starreal vtxvec[3]);

/* test gradient computation */
bool testgrad(tetcomplex* mesh,
              tag vtx,
              tag vtx2,
              tag vtx3,
              tag vtx4);

/* returns the basis B of S union M. S is a set of points known
   to be in the basis */
void findbasis(starreal S[][3],
    starreal M[][3],
    starreal B[][3],
    int sizeS,
    int sizeM,
    int* sizeB);

/* finds the point on the convex hull of P nearest
   the origin */
void minconvexhullpoint(starreal P[][3],
    int sizeP,
    starreal nearest[]);

/* find the best step to take to improve all of the quality
   functions affected by a vertex vtx in the search direction
   d with an expected rate of improvement r */
void nonsmoothlinesearch(tetcomplex* mesh,
                         tag vtx,
                         starreal d[],
                         starreal inworstqual,
                         starreal* alpha,
                         starreal r,
                         opttet incidenttets[],
                         int numincident,
                         int vtxkind,
                         starreal vtxvec[3]);

/* given a set of tets incident to a vertex, and the quality
   of the worst quality function that varies with that vertex,
   compute the active set A of quality functions very near
   the worst */
void getactiveset(tetcomplex* mesh,
                  opttet incidenttets[],
                  int numincident,
                  starreal activegrads[][3],
                  int* numactive,
                  starreal worstqual);

/* for our initial step size, we use the distance
   to the next intersection with another quality funtion.
   this is the point at which the other quality function
   becomes the worst. we use a single-term taylor expansion
   to approximate all of the quality functions as lines,
   so we'll have to do a line search to find our ultimate
   step size. */
starreal getinitialalpha(tetcomplex* mesh,
                         opttet incidenttets[],
                         int numincident,
                         starreal d[3],
                         starreal r,
                         starreal worstqual);

/* perform non-smooth optimization of a vertex's position.
   vtx - the vertex to be smoothed, is in tet (vtx, vtx2, vtx3, vtx4).
   This tet gives us a starting point to build the list of incident
   elements.

   If we end up moving the vertex, return true.
   If for some reason we can't, return false.
*/
bool nonsmooth(tetcomplex* mesh,
               tag vtx,
               opttet incidenttets[],
               int numincident,
               starreal* outworstqual,
               int smoothkinds);

/* optimization-based smoothing for a single vertex
   v1, part of the existing tet (1,2,3,4) */
bool nonsmoothsinglevertex(tetcomplex* mesh,
                           tag v1,
                           tag v2,
                           tag v3,
                           tag v4,
                           starreal* worstout,
                           int kinds);

/* combination lap/opt smoothing for a single vertex
   v1, part of the existing tet (1,2,3,4) */
bool smoothsinglevertex(tetcomplex* mesh,
                        tag v1,
                        tag v2,
                        tag v3,
                        tag v4,
                        starreal threshold,
                        starreal* worstout,
                        int kinds,
                        int* optattempts,
                        int* optsuccesses,
                        struct arraypoolstack* outstack);

#define SKIPCHECKSIZE 0

/* perform a pass of combination Laplacian / optimization-based smoothing. */
bool smoothpass(tetcomplex* mesh,
                arraypoolstack* tetstack,
                arraypoolstack* outstack,
                arraypoolstack* influencestack,
                int qualmeasure,
                starreal threshold,
                starreal bestmeans[],
                starreal meanqualafter[],
                starreal* minqualafter,
                int smoothkinds,
                bool quiet);


#endif
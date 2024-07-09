#pragma once
#ifndef _classify_header
#define _classify_header
#include "Starbase.h"
/*****************************************************************************/
/*                                                                           */
/*  Routines to classify vertices                                            */
/*                                                                           */
/*****************************************************************************/

/* given a boundary vertex and a list of all of it's
   incident tets, determine if it lies in an input facet */
bool facetvertex(tetcomplex* mesh,
                 tag vtx,
                 tag incidenttets[][4],
                 int numincident,
                 starreal normal[3]);

/* given a boundary vertex and a list of all of it's
   incident tets, determine if it lies in an input segment */
bool segmentvertex(tetcomplex* mesh,
                   tag vtx,
                   tag incidenttets[][4],
                   int numincident,
                   starreal edge[3]);

/* given a tet, classifies each of its vertices according to how many
   degrees of freedom it has. TODO: The starter code was copied from boundverts(),
   could these two be combined? */
void tetvertexclassify(tetcomplex* mesh,
                       tag v1,
                       tag v2,
                       tag v3,
                       tag v4);

/* classify the number of degrees of freedom for all tets in the mesh */
void classifyvertices(tetcomplex* mesh);
#endif
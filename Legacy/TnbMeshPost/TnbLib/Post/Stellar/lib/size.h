#pragma once
#ifndef _size_header
#define _size_header
#include "Starbase.h"
/* compute statistics about tetrahedra volumes */
void volumestats(tetcomplex* mesh,
                 starreal* minvol,
                 starreal* maxvol,
                 starreal* meanvol);

/* compute statistics about edge lengths in the mesh */
void edgelengthstats(tetcomplex* mesh,
                     starreal* minedge,
                     starreal* maxedge,
                     starreal* meanedge,
                     starreal* medianedge,
                     bool anisotropic);

#define MINSIZEQUAL 1.0e-5

/* attempt to collapse edges that are too short */
void sizecontract(tetcomplex* mesh,
                  struct arraypoolstack* tetstack);

#define SIZESPLITPARANOID 0

/* attempt to split edges that are too long */
void sizesplit(tetcomplex* mesh,
               arraypoolstack* tetstack);

/* split and collapse edges until all tetrahedra are roughly the same size */
int sizecontrol(tetcomplex* mesh,
                behavior* behave,
                inputs* in,
                proxipool* vertexpool,
                int argc,
                char** argv);

void sizereportstream(FILE* o, tetcomplex* mesh);

/* print a report on edge lengths in the mesh */
void sizereport(tetcomplex* mesh);

#endif

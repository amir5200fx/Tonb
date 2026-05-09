#pragma once
#ifndef _print_header
#define _print_header
#include "Starbase.h"
#include "top.h"
/*****************************************************************************/
/*                                                                           */
/*  printing utility functions                                               */
/*                                                                           */
/*****************************************************************************/

/* print the coordinates of the for vertices of a tet for viz purposes
   (prints them in the format of a MATLAB matrix, my ghetto viz tool) */
void printtetverts(tetcomplex* mesh, tag* tet);

/* print the geometric locations of face vertices */
void printfaceverts(tetcomplex* mesh, tag* face);

/* another function that prints a tet with separate vertex args */
void printtetvertssep(tetcomplex* mesh,
                      tag vtx1,
                      tag vtx2,
                      tag vtx3,
                      tag vtx4);

/* print out an array of tets */
void printtets(tetcomplex* mesh,
               tag tets[][4],
               int numtets);

/* print out an array of tets */
void printopttets(tetcomplex* mesh,
                  opttet tets[],
                  int numtets);

/* print out an array of faces */
void printfaces(tetcomplex* mesh,
                tag faces[][3],
                int numfaces);

/* print out an array of tets as tags*/
void printtetstags(tag tets[][4],
    int numtets);

/* print Q and K tables from Klincsek's algorithm for debugging
   purposes */
void printtables(starreal Q[][MAXRINGTETS],
    int K[][MAXRINGTETS],
    int ringcount);

/* print edge and ring around it for ghetto visualization in matlab */
void printring(tetcomplex* mesh, tag a, tag b, tag* ring, int ringcount);

/* print edge and ring around it for ghetto visualization in matlab */
void printhalfring(tetcomplex* mesh, tag a, tag b, tag* ring, int ringcount);

/* print out the info in a opttet */
void printopttet(opttet* tet);

/* print out B, S, M arrays from findbasis */
void printbasisarrays(starreal S[][3],
    starreal M[][3],
    starreal B[][3],
    int sizeS,
    int sizeM,
    int* sizeB,
    starreal p[]);

/* print out global improvement stats */
void printstatsstream(FILE* o, tetcomplex* mesh);

void printstats(tetcomplex* mesh);

void printmeans(starreal means[]);

#endif
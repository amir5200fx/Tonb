#pragma once
#ifndef _quadric_header
#define _quadric_header
#include "Starbase.h"

/* compute the quadric error for a query position of a vertex */
starreal quadricerrorquery(tetcomplex* mesh,
                           tag vtag,
                           starreal v[3]);

/* compute the quadric error for a particular vertex's current position */
starreal quadricerror(tetcomplex* mesh,
                      tag vtag);

/* compute the quadric error at a vertex, normalized to
   be comparable to tetrahedron quality measures */
starreal quadricerrortet(tetcomplex* mesh,
                         tag vtag);

bool hasquadric(tag vtag);

/* compute the gradient of the quadric error for query point */
void quadricgradquery(tetcomplex* mesh,
                      tag vtag,
                      starreal v[3],
                      starreal grad[3]);

/* compute the gradient of the quadric error for a vertex */
void quadricgrad(tetcomplex* mesh,
                 tag vtag,
                 starreal grad[3]);

/* compute the gradient of the quadric error, scaled for tet comparison */
void quadricgradtet(tetcomplex* mesh,
                    tag vtag,
                    starreal grad[3]);

/* add a quadric for a newly inserted vertex */
bool addquadric(tetcomplex* mesh,
                tag vtag,
                tag faces[][3],
                int numfaces);

/* normalize quadric by dividing by the sum of the face areas
   and the harmonic mean of the edge lengths squared */
void normalizequadrics(tetcomplex* mesh);

/* create quadrics for all surface vertices */
void collectquadrics(tetcomplex* mesh);

/* do a bunch of checks on quadrics */
void checkquadricsstream(FILE* o, tetcomplex* mesh);

void checkquadrics(tetcomplex* mesh);
#endif
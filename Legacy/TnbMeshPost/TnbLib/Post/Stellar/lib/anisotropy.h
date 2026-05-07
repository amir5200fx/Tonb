#pragma once
#ifndef _anisotropy_header
#define _anisotropy_header
#include "Starbase.h"
/* given a single vector, return two more that are mutually
   orthogonal to it */
void getorthobasis(starreal v1[3],
    starreal v2[3],
    starreal v3[3]);
/* given three mutually orthogonal vectors and three corresponding
   eigenvalues, compute a transformation matrix E */
void tensorfromeigen(starreal v1[3],
    starreal v2[3],
    starreal v3[3],
    starreal e1,
    starreal e2,
    starreal e3,
    starreal E[3][3]);
/* tensor field that compresses space orthogonal to lines radiating
   from the origin */
void sinktensor(starreal x,
    starreal y,
    starreal z,
    starreal E[3][3]);
/* tensor field that compresses space orthogonal to lines radiating
   from the origin */
void swirltensor(starreal x,
    starreal y,
    starreal z,
    starreal E[3][3]);
/* tensor field that runs sin(x) */
void sinetensor(starreal x,
    starreal y,
    starreal z,
    starreal E[3][3]);
/* tensor with denser elements in the middle */
void centertensor(starreal x,
    starreal y,
    starreal z,
    starreal E[3][3]);
/* tensor with denser elements away from the middle */
void perimetertensor(starreal x,
    starreal y,
    starreal z,
    starreal E[3][3]);
/* tensor with denser elements on the +x side */
void righttensor(starreal x,
    starreal y,
    starreal z,
    starreal E[3][3]);
void scaletensor(starreal scalex,
    starreal scaley,
    starreal scalez,
    starreal E[3][3]);
/* get scaling tensor by sampling strain field */
void straintensor(starreal x,
    starreal y,
    starreal z,
    starreal E[3][3]);
/* blend the scaling tensor with the identity matrix */
void blendtensor(starreal E[3][3], starreal Eb[3][3]);
/* return the deformation tensor for the query point */
void deformtensor(starreal x,
    starreal y,
    starreal z,
    starreal E[3][3]);
/* fetch the deformation tensor sampled at the barycenter of
   the specified tetrahedron */
void tettensor(tetcomplex* mesh,
               tag vtx1,
               tag vtx2,
               tag vtx3,
               tag vtx4,
               starreal E[3][3]);
/* fetch the deformation tensor sampled at the midpoint of the specified edge */
void edgetensor(tetcomplex* mesh,
                tag vtx1,
                tag vtx2,
                starreal E[3][3]);
/* transform a point to isotropic space with deformation tensor E */
void tensortransform(starreal p[3], starreal pout[3], starreal E[3][3]);
#endif
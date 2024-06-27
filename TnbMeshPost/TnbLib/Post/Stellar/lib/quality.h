#pragma once
#ifndef _quality_header
#define _quality_header
#include "top.h"

/* determine if a tet has any boundary vertices.
   return the number of boundary verts as well as
   their tags in boundtags */
int boundverts(tetcomplex* mesh,
               tag vtx1,
               tag vtx2,
               tag vtx3,
               tag vtx4,
               tag boundtags[]);
#define NOBOUNDFACE -2

/* Retrieve the ring of tetrahedra around a particular edge, and meanwhile
   detect whether it's a boundary edge. Potentially don't store the ring of
   tets if the array to store them is null. Return a boolean indicating
   whether it is a bounary edge, as well as the third vertices of the boundary
   faces */
bool getedgering(tetcomplex* mesh,
                 tag vtx1, /* first vertex of the edge */
                 tag vtx2, /* second vertex of the edge */
                 tag vtx3, /* third vertex of a tet that contains the edge */
                 tag vtx4, /* fourth vertex of a tet that contains the edge */
                 int* numringtets, /* number of tets in the ring */
                 tag ringtets[MAXRINGTETS][4], /* the vertices of tets in the ring */
                 tag boundfaceverts[2] /* the third vertex of the two boundary faces */
);
/* returns the number of edges of this tet that lie on the boundary
   along with a list of them */
int boundedges(tetcomplex* mesh,
               tag vtx1,
               tag vtx2,
               tag vtx3,
               tag vtx4,
               tag edgelist[][2],
               tag edgefaces[6][2],
               int numedgetets[6],
               tag edgetets[6][MAXRINGTETS][4]);
/* determine if any of the faces of a tet lie on
   the boundary. if so, return true, and put
   the boundary faces in boundfaces */
bool boundfaces(tetcomplex* mesh,
                tag vtx1,
                tag vtx2,
                tag vtx3,
                tag vtx4,
                tag boundfaces[][3],
                int* numboundary);
/* returns true if any of this tet's faces lie
   on the boundary */
bool boundtet(tetcomplex* mesh,
              tag vtx1,
              tag vtx2,
              tag vtx3,
              tag vtx4);
/* generate a list of all boundary faces in the mesh */
void getsurface(tetcomplex* mesh,
                arraypool* facepool,
                int* numfaces);
/* return the volume of a tetrahedron */
starreal tetvolume(tetcomplex* mesh,
                   tag vtx1,
                   tag vtx2,
                   tag vtx3,
                   tag vtx4);
/* return the length of a tet's longest (shortest) edge,
   as well as the indices of its endpoints. "getlong"
   argument set to true computes longest, otherwise shortest */
starreal tetedge(tetcomplex* mesh,
                 tag vtx1,
                 tag vtx2,
                 tag vtx3,
                 tag vtx4,
                 int edge[2],
                 bool getlong);

/* compute the (square) of the minimum sine
   of all the dihedral angles in the tet defined
   by the four vertices (vtx1, vtx2, vtx3, vtx4)
*/
starreal minsine(tetcomplex* mesh,
                 tag vtx1,
                 tag vtx2,
                 tag vtx3,
                 tag vtx4);

/* compute the minimum or maximum angle of the tet defined
   by the four vertices (vtx1, vtx2, vtx3, vtx4)
*/
starreal minmaxangle(tetcomplex* mesh,
                     tag vtx1,
                     tag vtx2,
                     tag vtx3,
                     tag vtx4,
                     bool max);

/* warp the sine of the dihedral angle to penalize obtuse angles more than acute */
starreal warpsine(starreal sine);

/* compute the (square) of the minimum sine
   of all the dihedral angles in the tet defined
   by the four vertices (vtx1, vtx2, vtx3, vtx4)
*/
starreal warpedminsine(tetcomplex* mesh,
                       tag vtx1,
                       tag vtx2,
                       tag vtx3,
                       tag vtx4);

/* compute the (square) of the minimum sine
   of all the dihedral angles in the tet defined
   by the four vertices (vtx1, vtx2, vtx3, vtx4)
*/
starreal minsineandedgeratio(tetcomplex* mesh,
                             tag vtx1,
                             tag vtx2,
                             tag vtx3,
                             tag vtx4);

/* compute the mean of the sines
   of all the dihedral angles in the tet defined
   by the four vertices (vtx1, vtx2, vtx3, vtx4)
*/
starreal meansine(tetcomplex* mesh,
                  tag vtx1,
                  tag vtx2,
                  tag vtx3,
                  tag vtx4);

/* compute Z, a quantity associated with circumradius computation
   TODO this code is lifted from Jonathan's tetcircumcenter computation
   in primitives.c */
starreal getZ(starreal* tetorg,
    starreal* tetdest,
    starreal* tetfapex,
    starreal* tettapex);

/* the inradius to circumradius ratio */
starreal radiusratio(tetcomplex* mesh,
                     tag vtx1,
                     tag vtx2,
                     tag vtx3,
                     tag vtx4);

/* compute the ratio of the tet volume to the cube of
   the rms edge length */
starreal vlrms3ratio(tetcomplex* mesh,
                     tag vtx1,
                     tag vtx2,
                     tag vtx3,
                     tag vtx4);

/* harness function for all quality measures */
starreal tetquality(tetcomplex* mesh,
                    tag vtx1,
                    tag vtx2,
                    tag vtx3,
                    tag vtx4,
                    int measure);

/********* Statistics printing routines begin here                   *********/
/**                                                                         **/
/**                                                                         **/

void statisticsqualitystream(FILE* o,
                             behavior* behave,
                             tetcomplex* plex,
    bool anisotropic);

void improvestatistics(behavior* behave,
                       tetcomplex* plex,
                       bool anisotropic);

void getextremeangles(behavior* behave,
                      tetcomplex* plex,
                      starreal* outsmallestangle,
                      starreal* outbiggestangle);

void setbeginqual(behavior* behave,
                  tetcomplex* plex);

/* given the two vertices of a known boundary edge,
   compute the angle between it's two incident
   boundary faces */
starreal getboundaryedgeangle(tetcomplex* mesh,
                              tag v1,
                              tag v2,
                              tag vleft,
                              tag vright);

/* given an input mesh, find the worst "input" angle.
   that is, find the smallest angle between two faces
   of the boundary */
starreal worstinputangle(tetcomplex* mesh);

/* gather some information about the worst tets in the mesh */
/* according to the given quality measure, report information
   about all the tets within degreesfromworst of the worst tet */
void worsttetreport(tetcomplex* mesh,
                    int qualmeasure,
                    starreal degreesfromworst);

/* determine if there is threshold improvement in some mean */
bool localmeanimprove(starreal oldmeans[], starreal newmeans[], starreal threshold);


#endif
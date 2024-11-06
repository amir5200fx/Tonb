#pragma once
#ifndef _topological_header
#define _topological_header
#include "Starbase.h"
#include "top.h"
/*****************************************************************************/
/*                                                                           */
/*  topological improvement functions                                        */
/*                                                                           */
/*****************************************************************************/

/* determine the number of reflex edges that a face has, to determine what sort
   of flips might be done to it */
int countreflex(tetcomplex* mesh,
                tag vtx1,
                tag vtx2,
                tag vtx3,
                int* numcoplanar,
                int coplanaredges[][2]);

/* my wrapper for single tet insertion, gets recorded in the journal */
void inserttet(tetcomplex* mesh,
               tag vtx1,
               tag vtx2,
               tag vtx3,
               tag vtx4,
               bool record);

/* my wrapper for single tet deletion, gets recorded in the journal */
void deletetet(tetcomplex* mesh,
               tag vtx1,
               tag vtx2,
               tag vtx3,
               tag vtx4,
               bool record);

/* bryan's own version of 2-3 flip that uses explicit
   delete and insert calls to perform the flip */
void flip23(tetcomplex* mesh,
            tag vtx1,
            tag vtx2,
            tag vtx3,
            tag vtxbot,
            tag vtxtop,
            bool record);

/* bryan's own version of a 3-2 flip that uses explicit
   delete and insert calls to perform the flip */
void flip32(tetcomplex* mesh,
            tag vtx1,
            tag vtx2,
            tag vtx3,
            tag vtxbot,
            tag vtxtop,
            bool record);

/* perform a 2-2 flip using the edge from vtx1 to vtx2 */
void flip22(tetcomplex* mesh,
            tag vtx1,
            tag vtx2,
            tag vtx3,
            tag vtxbot,
            tag vtxtop,
            bool record);

/* given the tet (1,2,3,4), and the vertex bodyvertex
   in its interior, delete the original tet and connect
   the interior vertex to the old vertices, forming 4 new
   tets */
void flip14(tetcomplex* mesh,
            tag vtx1,
            tag vtx2,
            tag vtx3,
            tag vtx4,
            tag bodyvtx,
            bool record);

/* reverses a 1-4 flip */
void flip41(tetcomplex* mesh,
            tag vtx1,
            tag vtx2,
            tag vtx3,
            tag vtx4,
            tag bodyvtx,
            bool record);

/* given a tetrahedron with a boundary face and a new vertex that
   lies inside that face, remove the old tet and create three new
   ones. vtx2, vtx3, vtx4 should be the boundary face oriented
   toward vtx1 with a right-hand rule */
void flip13(tetcomplex* mesh,
            tag vtx1,
            tag vtx2,
            tag vtx3,
            tag vtx4,
            tag facetvtx,
            bool record);

/* the opposite of a 1-3 flip. Given three tets that share
   a facet vertex and an interior vertex, remove the facet
   vertex and replace them with one tet. vtx1 is the
   interior vertex, facetvtx is the facet vtx, and
   the other three vertices are on the future boundary
   facet and will form face (2,3,4) oriented toward vtx1 */
void flip31(tetcomplex* mesh,
            tag vtx1,
            tag vtx2,
            tag vtx3,
            tag vtx4,
            tag facetvtx,
            bool record);

/* given a tetrahedron with a boundary edge and a new vertex that
   lies on that segment, remove the old tet and create two new
   ones. vtx1, vtx2 should be the boundary edge */
void flip12(tetcomplex* mesh,
            tag vtx1,
            tag vtx2,
            tag vtx3,
            tag vtx4,
            tag segmentvtx,
            bool record);

/* reverse the above 1-2 flip */
void flip21(tetcomplex* mesh,
            tag vtx1,
            tag vtx2,
            tag vtx3,
            tag vtx4,
            tag segmentvtx,
            bool record);

/* creates the tetrahedra for the optimal triangulation of Tij */
void flip23recurse(tetcomplex* mesh,
                   tag vtx1,
                   tag vtx2,
                   tag* ring,
                   int ringcount,
                   int K[][MAXRINGTETS],
                   int i,
                   int j,
                   tag newtets[][4],
                   int* newtetcount);

/* Replaces all tetrahedra that include the edge from vtx1 to vtx2 with
   the tetrahedra induced by the optimal triangulation of the ring of
   vertices around that egde, computed by filltables. K is a table of
   indices that identify the optimal triangulations of every subset of
   the ring Tij. */
void removeedgeflips(tetcomplex* mesh,
                     tag vtx1,
                     tag vtx2,
                     tag* ring,
                     int ringcount,
                     int K[][MAXRINGTETS],
                     tag newtets[][4],
                     int* newtetcount,
                     bool boundary);

/* fill Q and K tables for Klincsek's algorithm */
void filltables(tetcomplex* mesh,
                tag vtx1,
                tag vtx2,
                tag* ring,
                int ringcount,
                starreal oldminqual,
                starreal Q[][MAXRINGTETS],
                int K[][MAXRINGTETS]);

/* try contracting the edge from v1 to v2 that is in the
   tet (v1, v2, v3, v4). Return true if edge contraction
   succeeds in improving quality of all affected tets,
   and false otherwise (mesh unchanged on failure) */
#define CONTRACTPARANOID false

bool edgecontract(tetcomplex* mesh,
                  tag v1,
                  tag v2,
                  tag v3,
                  tag v4,
                  starreal* minqualbefore,
                  starreal* minqualafter,
                  int* numouttets,
                  tag outtets[MAXINCIDENTTETS][4],
                  bool requireimprove);

/* try to contract all six edges of a tet */
bool tryedgecontract(tetcomplex* mesh,
                     tag vtx1, tag vtx2, tag vtx3, tag vtx4,
                     arraypoolstack* outstack,
                     starreal* minqualafter,
                     bool requireimprove,
                     bool justfirstedge);

/* attempt to remove the edge from vtx1 to vtx2. ring is the ring
   of vertices to be removed. Return 1 if edge removal successfully
   improves quality, zero otherwise. */
int removeedge(tetcomplex* mesh,
               tag vtx1,
               tag vtx2,
               tag* ring,
               int ringcount,
               starreal oldminqual,
               tag newtets[][4],
               int* newtetcount,
               starreal* outminqual,
               bool boundary);

/* check for any boundary edge removal opportunities in this tet. */
int tryboundaryedgeremove(tetcomplex* mesh,
                          tag vtx1,
                          tag vtx2,
                          tag vtx3,
                          tag vtx4,
                          arraypoolstack* tetstack,
                          int ringsizes[MAXRINGTETS],
                          int* biggestring,
                          starreal* minafterqual);

/* try edge removal on all 6 edges of the specified tet. if removal
   succeeds, return 1. Otherwise, return 0. */
int tryedgeremove(tetcomplex* mesh,
                  tag vtx1,
                  tag vtx2,
                  tag vtx3,
                  tag vtx4,
                  arraypoolstack* tetstack,
                  int ringsizes[MAXRINGTETS],
                  int* biggestring,
                  starreal* minafterqual);

bool try22flip(tetcomplex* mesh,
               tag face[3],
               tag bot,
               tag top,
               int edge[2],
               tag newtets[][4],
               int* numnewtets,
               bool requireimprove);

/* given an edge (1,2) and a pair of "sandwich" vertices a and b,
   (a above) determine what the neighbor across the edge is.
   if there is none, return GHOSTVERTEX */
tag sandwichneighbor(tetcomplex* mesh,
                     tag v1,
                     tag v2,
                     tag a,
                     tag b);

/* structure to hold a face, g, and pointers to it's two children */
struct facechildren
{
    tag face[3];
    int child1;
    int child2;
};
#define NOCHILD -1

void printfacetree(tetcomplex* mesh,
                   facechildren tree[],
                   int treesize);

/* given a face f, an edge uw of that face, and two sandwiching vertices a and b,
   determine if when removing f whether also removing it's neighbor across uw, g,
   would be beneficial. if so, return true. otherwise, return false */
bool testneighbor(tetcomplex* mesh,
                  facechildren facetree[],
                  int* treesize,
                  tag a,
                  tag b,
                  tag u,
                  tag w,
                  starreal* qold,
                  starreal* qnew,
                  int* g);

/* remove face g and, recursively, it's children */
void flip32recurse(tetcomplex* mesh,
                   facechildren tree[],
                   int treesize,
                   int g,
                   tag a,
                   tag b,
                   tag newtets[][4],
                   int* numnewtets);

/* f (u, v, w) is a triangular face under consideration for removal. all faces
   sandwiched between the same two vertices (a and b) as f are considered
   for removal */
bool removemultiface(tetcomplex* mesh,
                     tag u,
                     tag v,
                     tag w,
                     int* numfaces,
                     tag newtets[][4],
                     int* numnewtets);

#define FLIP23SUCCESS 1
#define FLIP22SUCCESS 2
#define MULTIFACESUCCESS 3

/* attempt a 2-3 flip to remove the face vtx1, vtx2, vtx3. it can be
   required or not that this flip improve the quality of the submesh.
   TODO is this function really necessary? Need to clean up edge removal in general... */
int try23flipold(tetcomplex* mesh,
                 tag vtx1,
                 tag vtx2,
                 tag vtx3,
                 tag newtets[][4],
                 int* numnewtets,
                 bool requireimprove);

/* attempt to remove the face (1,2,3). If it has coplanar boundary faces,
   use a 2-2 flip where appropriate. Otherwise, use multi-face removal.
   If a quality-insensitive flip is desired, for now use the old 2-3 single
   flip */
int tryfaceremove(tetcomplex* mesh,
                  tag vtx1,
                  tag vtx2,
                  tag vtx3,
                  int* numfaces,
                  tag newtets[][4],
                  int* numnewtets,
                  bool requireimprove);

/* try a 2-3 flip on all four faces of the specified tet
   returns 1 if a flip was performed, 0 otherwise */
int tryremoveallfaces(tetcomplex* mesh,
                      tag vtx1,
                      tag vtx2,
                      tag vtx3,
                      tag vtx4,
                      arraypoolstack* tetstack,
                      int facesizes[],
                      int* biggestsize,
                      starreal* outqual,
                      bool requireimprove);

/* perform a pass of topological improvement.
   for now, this means trying to remove each edge
   of each tet in the stack that is passed in,
   and if no edge can be removed, trying to remove
   each face. */
bool topopass(tetcomplex* mesh,
              arraypoolstack* tetstack,
              arraypoolstack* outstack,
              int qualmeasure,
              starreal bestmeans[],
              starreal meanqualafter[],
              starreal* minqualafter,
              bool quiet);

/* for each tet in the stack, try to contract its edges */
bool contractpass(tetcomplex* mesh,
                  arraypoolstack* tetstack,
                  arraypoolstack* outstack,
                  int qualmeasure,
                  starreal bestmeans[],
                  starreal meanqualafter[],
                  starreal* minqualafter,
                  bool justfirstedge,
                  bool quiet);

/* go after the worst tets with contraction */
void contractworst(tetcomplex* mesh,
                   int qualmeasure,
                   starreal percentinsert,
                   starreal bestmeans[],
                   starreal outmeanqual[],
                   starreal* outminqual,
                   bool desperate);
#endif
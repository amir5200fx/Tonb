#pragma once
#ifndef _insertion_header
#define _insertion_header
#include "Starbase.h"
#include "top.h"
/*****************************************************************************/
/*                                                                           */
/*  Vertex insertion routines                                                */
/*                                                                           */
/*****************************************************************************/

/* check an array of tets to see if it contains the query tet */
bool tetinlist(tag v1,
    tag v2,
    tag v3,
    tag v4,
    tag list[][4],
    int listsize);

/* check an array of faces to see if it contains the query face */
bool faceinlist(tag v1,
    tag v2,
    tag v3,
    tag list[][3],
    int listsize);

/* removed the specified face from a face list */
void deletelistface(tag v1,
    tag v2,
    tag v3,
    tag list[][3],
    int* listsize);

/* removed the specified tet from a tet list */
void deletelisttet(tag v1,
    tag v2,
    tag v3,
    tag v4,
    tag list[][4],
    int* listsize);

/* add the specified tet to a list */
void addlisttet(tag v1,
    tag v2,
    tag v3,
    tag v4,
    tag list[][4],
    int* listsize);

/* add the specified face to a list */
void addlistface(tag v1,
    tag v2,
    tag v3,
    tag list[][3],
    int* listsize);

#define NOCAVITYTET -1
#define NOCAVITYFACE -1

struct cavityface
{
    tag verts[3];
    starreal qual;
    int child;
    bool inH;
};

struct cavityedge
{
    starreal qual;
    int parent;
    int child;
    int childnum;
};

#define EDGELABEL 0
#define TETLABEL 1

struct cavityedgeortet
{
    starreal qual;
    int label;
    int parent;
    int child;
    int childnum;
};

struct cavitytet
{
    tag verts[4];
    starreal qual;
    int numoutfaces;
    int depth;
    cavityface outfaces[MAXOUTFACES];
    int parents[3];
    int label;
};

void printcavitytet(cavitytet* tet);

void printcavitydag(tetcomplex* mesh,
                    cavitytet cavity[],
                    int cavitysize);

/* check an array of tets to see if it contains the query tet.
   if so, return its location. if not, return NOCAVITYTET */
int cavitytetinlist(tag v1,
    tag v2,
    tag v3,
    tag v4,
    cavitytet list[],
    int listsize);

/* check a tet to see if it contains the query face.
   if so, return its location. if not, return NOCAVITYFACE */
int cavityfaceintet(tag v1,
    tag v2,
    tag v3,
    cavitytet* tet);

/* add a tet to the cavity */
void addcavitytet(cavitytet* tet,
                  cavitytet list[],
                  int* listsize);

/* return the number of parents a tet has */
int numparents(cavitytet* tet);

/* add an outgoing face to a cavity tet */
void addcavitytetface(cavitytet* tet,
                      cavityface* face);

/* return the number of faces of the tet t that are positively
   oriented with respect to the vertex v */
int numpositivefaces(tetcomplex* mesh,
                     tag t[4],
                     starreal* v);

/* check the DAG to make sure it's constructed correctly */
bool cavitydagcheck(tetcomplex* mesh,
                    cavitytet cavity[],
                    int cavitysize);

/* given a vertex, it's position, an initial cavitiy of tets and
   a set of outward-oriented faces of that cavity, build a DAG
   representing the largest star-shaped cavity from the point of
   view of the inserted vertex */
void buildcavitydag(tetcomplex* mesh,
                    tag vtag,
                    tag initialC[][4],
                    int initialCsize,
                    tag initialF[][3],
                    int initialFsize,
                    cavitytet outcavity[],
                    int* cavitysize,
                    bool allowvertexdeletion);

/* debug routine to print out edge list */
void printedgelist(cavityedge edges[],
                   int numedges);

/* debug routine to print out combined tet/edge list */
void printedgeortetlist(cavityedgeortet edges[],
                        int numedges);

/* compare two edges, to be used for standard qsort call */
int compareedges(const void* a, const void* b);

/* compare two elements in a hybrid edge/tet list, for qsort */
int compareedgeortets(const void* a, const void* b);

/* function to sort an array of edges */
void sortedges(cavityedge array[],
               int arraylength);

/* function to sort an hybrid array of edges/tets */
void sortedgeortets(cavityedgeortet array[],
                    int arraylength);

#define CAVLABEL 0
#define ANTICAVLABEL 1
#define NOLABEL 2

/* table of factors by which to augment deeper tets
   TODO automatically select weights somehow */
#define DEPTHTABLESIZE 10
extern starreal depthtable[DEPTHTABLESIZE];

/* recursively label parents and children as cavity tets */
void cavitylabel(cavitytet cavity[],
                 int cavitysize,
                 int tetid);

/* recursively label parents and children as anti-cavity tets */
void anticavitylabel(cavitytet cavity[],
                     int cavitysize,
                     int tetid);

/* ALGORITHM 3 + CONSIDER DELETED TETS*/
/* given the DAG representing the largest possible cavity,
   find the subcavity that has the lexicographically maximum
   quality, then dig it out and connect the exposed faces to
   the new vertex, returning the new tets as well as the worst
   quality in this cavity */
void lexmaxcavity3(tetcomplex* mesh,
                   tag vtag,
                   cavitytet cavity[],
                   int cavitysize,
                   tag outtets[][4],
                   int* numouttets,
                   starreal* worstdeleted,
                   starreal* worstincavity);

/* given a vertex, it's position, and an initial cavity of tets
   and a set of outward-oriented faces of that cavity, dig out an
   optimal cavity around the vertex and connect the central vertex
   to all of the cavity faces, and return a list of the new tets */
void optimalcavity(tetcomplex* mesh,
                   tag vtag,
                   tag initialC[][4],
                   int initialCsize,
                   tag initialF[][3],
                   int initialFsize,
                   tag outtets[][4],
                   int* numouttets,
                   starreal* worstdeleted,
                   starreal* worstincavity,
                   bool allowvertexdeletion);

/* given a cavity of tets built around a single vertex,
   try to improve the cavity, and return the final quality */
starreal improvecavity(tetcomplex* mesh,
                       tag v,
                       tag tets[][4],
                       int numtets,
                       bool tryhard,
                       arraypoolstack* outstack,
                       starreal* shortest, starreal* longest);

/* insert a new vertex in the facet specified, returning
   the new vertex tag, the new vertex position, and the
   outward-oriented faces of the new tets */
bool facetinsert(tetcomplex* mesh,
                 tag v1,
                 tag v2,
                 tag v3,
                 tag v4,
                 tag face[3],
                 tag* vnew,
                 tag newfaces[][3],
                 int* numnewfaces,
                 tag newtets[][4],
                 int* numnewtets);

void bodyinsert(tetcomplex* mesh,
                tag v1,
                tag v2,
                tag v3,
                tag v4,
                tag* vnew,
                tag newfaces[][3],
                int* numnewfaces,
                tag newtets[][4],
                int* numnewtets);

bool segmentinsert(tetcomplex* mesh,
                   tag v1,
                   tag v2,
                   tag v3,
                   tag v4,
                   int numtets,
                   tag tets[][4],
                   tag boundfaces[],
                   tag* vnew,
                   tag newfaces[][3],
                   int* numnewfaces,
                   tag newtets[][4],
                   int* numnewtets,
                   bool boundedge);

/* general vertex insertion routine */
bool insertvertex(tetcomplex* mesh,
                  tag v1,
                  tag v2,
                  tag v3,
                  tag v4,
                  starreal inquality,
                  starreal meshworstquality,
                  starreal* outquality,
                  arraypoolstack* outstack,
                  bool tryhard);

/* attempt insertion on a stack of tets */
bool insertpass(tetcomplex* mesh,
                arraypoolstack* tetstack,
                arraypoolstack* outstack,
                int qualmeasure,
                starreal meanqualafter[],
                starreal* minqualafter,
                starreal okayqual,
                bool quiet);

/* go after the worst tets. with insertion */
void worsttetattack(tetcomplex* mesh,
                    int qualmeasure,
                    starreal percentinsert,
                    starreal outmeanqual[],
                    starreal* outminqual,
                    bool desperate);



#endif
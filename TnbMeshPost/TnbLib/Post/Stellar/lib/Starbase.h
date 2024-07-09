#ifndef _Starbase_header
#define _Starbase_header
/* This file was automatically generated.  Do not edit! */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#if !defined(NO_TIMER)
#include <sys/time.h>
#endif
#if defined(CPU86)
#include <float.h>
#endif
#if defined(LINUX)
#include <fpu_control.h>
#endif
#if !defined(NOMAIN)

struct tetcomplexposition;
struct tetcomplexstar;
int main(int argc, char** argv);
#endif
// Forward Declarations
struct behavior;
struct inputs;
struct outputs;
struct tetcomplex;
void statistics(behavior* behave, inputs* in, outputs* out, tetcomplex* plex);
void statisticsquality(behavior* behave, tetcomplex* plex);
typedef size_t starulong;
typedef starulong arraypoolulong;
void outputfaces(behavior* behave, inputs* in, tetcomplex* plex, arraypoolulong facecount, int argc, char** argv);
void outputedges(behavior* behave, inputs* in, tetcomplex* plex, arraypoolulong edgecount, int argc, char** argv);
void outputtetrahedra(behavior* behave, inputs* in, tetcomplex* plex, int argc, char** argv);
// Forward Declarations
struct proxipool;
void outputnumbervertices(behavior* behave, inputs* in, proxipool* pool);
void outputvertices(behavior* behave, inputs* in, proxipool* pool, arraypoolulong vertexcount, int argc, char** argv);
void outputpreparevertices(behavior* behave, tetcomplex* plex);
#if !defined(STARLIBRARY)
void outputfilefinish(FILE* outfile, int argc, char** argv);
#endif
// Forward Declarations
struct segment;
segment* inputsegments(behavior* behave, inputs* in, FILE* polyfile);
void inputsegment(behavior* behave, inputs* in, FILE* polyfile, arraypoolulong segnumber, int markflag, segment* seg);
int inputsegmentheader(behavior* behave, inputs* in, FILE* polyfile);
void inputtetrahedra(behavior* behave, inputs* in, proxipool* vertexpool, outputs* out, tetcomplex* plex);
typedef arraypoolulong tag;
void inputmaketagmap(proxipool* vertexpool, arraypoolulong firstnumber, tag* vertextags);
FILE* inputverticesreadsortstore(behavior* behave, inputs* in, proxipool* pool);
void inputverticessortstore(char* vertices, inputs* in, proxipool* pool);
void inputverticesintopool2(char* vertices, inputs* in, proxipool* pool);
void inputverticesintopool(char* vertices, inputs* in, proxipool* pool);
void inputvertexsort2(char* vertices, tag* vertextags, arraypoolulong vertexcount, size_t vertexbytes, unsigned int attribcount);
void inputvertexsort(char* vertices, tag* vertextags, arraypoolulong vertexcount, size_t vertexbytes, unsigned int attribcount);
char* inputvertexfile(behavior* behave, inputs* in, FILE** polyfile);
#if !defined(STARLIBRARY)
char* inputvertices(FILE* vertexfile, char* vertexfilename, inputs* in, int markflag);
char* inputfindfield(char* string);
char* inputtextline(char* string, FILE* infile, char* infilename);
#endif
int vertexcheckdelaunay(behavior* behave, tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag adjacencies[2]);
void vertexcheckpointintet(behavior* behave, tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4, tag invertex);
void vertexcheckorientation(behavior* behave, tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4);
struct outputs {
    arraypoolulong vertexcount;
    arraypoolulong tetcount;
    arraypoolulong facecount;
    arraypoolulong boundaryfacecount;
    arraypoolulong edgecount;
};
struct inputs {
    tag* vertextags;
    arraypoolulong vertexcount;                   /* Number of input vertices. */
    unsigned int attribcount;              /* Number of attributes per vertex. */
    arraypoolulong firstnumber;   /* Vertices are numbered starting from this. */
    arraypoolulong deadvertexcount;     /* Non-corner input vertices (killed). */
    arraypoolulong tetcount;                    /* Number of input tetrahedra. */
    unsigned int tetattribcount;      /* Number of attributes per tetrahedron. */
    arraypoolulong segmentcount;                  /* Number of input segments. */
    arraypoolulong facetcount;                      /* Number of input facets. */
    arraypoolulong holecount;                        /* Number of input holes. */
    arraypoolulong regioncount;                    /* Number of input regions. */
};
typedef int vertexmarktype;
struct facet {
    vertexmarktype mark;
    arraypoolulong number;
};
struct segment {
    tag endpoint[2];
    segment* nextsegment[2];
    vertexmarktype mark;
    short acute[2];
    arraypoolulong number;
};
/*  For single precision (which will save some memory and reduce paging),    */
/*  define the symbol SINGLE by using the -DSINGLE compiler switch or by     */
/*  writing "#define SINGLE" below.                                          */
/*                                                                           */
/*  For double precision (which will allow you to refine meshes to a smaller */
/*  edge length), leave SINGLE undefined.                                    */

/* #define SINGLE */

#ifdef SINGLE
typedef float starreal;
#else /* not SINGLE */
typedef double starreal;
#endif /* not SINGLE */

/*  A `vertexshort' is a structure that represents a vertex in the mesh.     */
/*  It is like a `vertex', but the vertex number is omitted to save space.   */
/*  The `coord' array comes last because it is treated as a variable-length  */
/*  array, with indices 3 and greater representing user-provided floating-   */
/*  point attributes.  This structure is typically used for vertex sorting   */
/*  prior to triangulation.                                                  */

struct vertexshort {
    vertexmarktype mark;
    starreal coord[3];
};

/*  A `vertex' is a structure that represents a vertex in the mesh.  Each    */
/*  vertex has three coordinates (x, y, and z) in `coord', a vertex mark     */
/*  stored in `mark', and a `number' by which the user indexes the vertex.   */
/*  Note that a vertex may have a different number in the output files than  */
/*  it had in the input files.  Note that each vertex may have auxiliary     */
/*  user-provided floating-point attributes, but these are not stored        */
/*  contiguously with the vertex structures.                                 */

struct vertex {
    starreal coord[3];
    vertexmarktype mark;
    arraypoolulong number;
};
#define ACTIVEVERTEX ((arraypoolulong) ~1)
#define DEADVERTEX ((arraypoolulong) ~0)
arraypoolulong tetcomplexbytes(tetcomplex* plex);
arraypoolulong tetcomplexghosttetcount(tetcomplex* plex);
arraypoolulong tetcomplextetcount(tetcomplex* plex);
void tetcomplexremoveghosttets(tetcomplex* plex);
void tetcomplexbuild3dstar(tetcomplex* plex, tag newvertex, struct arraypool* trianglelist, arraypoolulong firstindex, arraypoolulong trianglecount);
void tetcomplex41flip(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4, tag deletevertex);
void tetcomplex32flip(tetcomplex* plex, tag vtxtop, tag vtx1, tag vtx2, tag vtx3, tag vtxbot);
void tetcomplex23flip(tetcomplex* plex, tag vtxtop, tag vtx1, tag vtx2, tag vtx3, tag vtxbot);
void tetcomplex14flip(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4, tag newvertex);
void tetcomplex12flipon6edges(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4, tag newvertex);
void tetcomplex12flipon3edges(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4, tag newvertex);
void tetcomplexsqueezetriangle(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3);
void tetcomplexsqueezeonedge(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3);
void tetcomplexsqueezeonhalfedge(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3);
void tetcomplexdeletetriangle(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3);
void tetcomplex21fliponedge(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3);
int tetcomplexinserttetontripod(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4);
void tetcomplex12fliponedge(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4, tag newvertex);
int tetcomplexinserttet(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4);
int tetcomplexinsertorderedtet(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4);

tetcomplexstar* tetcomplexlookup3dstar(tetcomplex* plex, tag vtx);
int tetcomplexdeletetet(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4);
int tetcomplexdeleteorderedtet(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4);
void tetcomplexconsistency(tetcomplex* plex);
unsigned int tetcomplexmissingtet(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag vtx4);
void tetcomplexprintstars(tetcomplex* plex);
void tetcomplexprint(tetcomplex* plex);
void tetcomplexiteratenoghosts(tetcomplexposition* pos, tag nexttet[4]);
void tetcomplexiterate(tetcomplexposition* pos, tag nexttet[4]);
void tetcomplexiterateall(tetcomplexposition* pos, tag nexttet[4]);
void tetcomplexiteratorinit(tetcomplex* plex, tetcomplexposition* pos);
int tetcomplexvertex2tet(tetcomplex* plex, tag vtx, tag adjtet[4]);
int tetcomplexedge2tet(tetcomplex* plex, tag vtx1, tag vtx2, tag adjtet[4]);
int tetcomplexadjacencies(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag adjacencies[2]);
int tetcomplexringadjacencies(tetcomplex* plex, tag vtx1, tag vtx2, tag vtx3, tag adjacencies[2]);

/*****************************************************************************/
/*                                                                           */
/*  arraypoolfastlookup()   A fast, unsafe "dereferencing" operation:        */
/*                          return the pointer to the object with a given    */
/*                          index.  The object's second-tier block must have */
/*                          been allocated.                                  */
/*                                                                           */
/*  Use this procedure only for indices that have previously been allocated  */
/*  with arraypoolnewindex() or "dereferenced" with arraypoolforcelookup().  */
/*  WARNING:  fails catastrophically, probably with a segmentation fault, if */
/*  the index's second-tier block doesn't yet exist.                         */
/*                                                                           */
/*  Implemented as a macro to meet your need for speed.                      */
/*                                                                           */
/*  pool:  The arraypool containing the object.                              */
/*         Type (struct arraypool *).                                        */
/*  index:  The index of the object sought.                                  */
/*          Type (arraypoolulong).                                           */
/*                                                                           */
/*  Returns a pointer to the object if its block exists; might crash         */
/*    otherwise.                                                             */
/*    Type (void *).                                                         */
/*                                                                           */
/*****************************************************************************/

/* Dereference the top tier `toparray' with the upper bits to find the  */
/*   second-tier bock, then add an offset computed from the lower bits. */

#define arraypoolfastlookup(pool, index)  \
  (void *) ((pool)->toparray[(index) >> (pool)->log2objectsperblock] +  \
            ((index) & ((pool)->objectsperblock - 1)) * (pool)->objectbytes)
/*  The following MUST be the base-2 logarithm of the above.  If you change  */
/*  one, change the other to match.  Also, make sure that a `miniindex' can  */
/*  hold this many bits plus one.                                            */

#define LOG2OBJECTSPERMINI 10

/*****************************************************************************/
/*                                                                           */
/*  proxipooltag2mini()   Map a tag to the minipool it indexes.              */
/*                                                                           */
/*  WARNING:  fails catastrophically, probably with a segmentation fault, if */
/*  the tag's minipool doesn't yet exist.                                    */
/*                                                                           */
/*  Implemented as a macro to meet your need for speed.                      */
/*                                                                           */
/*  pool:  The proxipool in which to find a minipool.                        */
/*         Type (struct proxipool *).                                        */
/*  searchtag:  The tag whose minipool is sought.                            */
/*              Type (tag).                                                  */
/*                                                                           */
/*  Returns the minipool that contains the object with the given tag.  Might */
/*    crash if no such minipool has been allocated yet.                      */
/*    Type (struct minipoolheader *).                                        */
/*                                                                           */
/*****************************************************************************/

#define proxipooltag2mini(pool, searchtag)  \
  ((minipoolheader *)  \
   arraypoolfastlookup(&(pool)->minipoolarray,  \
                       (searchtag) >> LOG2OBJECTSPERMINI))
/*  The number of objects in a minipool.  (A minipool is the smallest unit   */
/*  of objects allocated at one time.)  Must be a power of 2.                */
#define OBJECTSPERMINI 1024

/*****************************************************************************/
/*                                                                           */
/*  proxipooltag2object2()   Map a tag to the supplementary object it        */
/*                           indexes.                                        */
/*                                                                           */
/*  WARNING:  fails catastrophically, probably with a segmentation fault, if */
/*  the tag's minipool doesn't yet exist.                                    */
/*                                                                           */
/*  Implemented as a macro to meet your need for speed.                      */
/*                                                                           */
/*  pool:  The proxipool in which to find a supplementary object.            */
/*         Type (struct proxipool *).                                        */
/*  searchtag:  The tag whose supplementary object is sought.                */
/*              Type (tag).                                                  */
/*                                                                           */
/*  Returns a pointer to the supplementary object.  Might crash if the tag   */
/*    has not been allocated yet.                                            */
/*    Type (void *).                                                         */
/*                                                                           */
/*****************************************************************************/

#define proxipooltag2object2(pool, searchtag)  \
  ((void *) (proxipooltag2mini(pool, searchtag)->object2block +  \
             (searchtag & (tag) (OBJECTSPERMINI - 1)) * (pool)->objectbytes2))

/*****************************************************************************/
/*                                                                           */
/*  tetcomplextag2attributes()   Map a tag to the vertex attributes (stored  */
/*                               in a supplementary object) it indexes.      */
/*                                                                           */
/*  This procedure is much like proxipooltag2object2(), but it saves callers */
/*  from needing to remember which proxipool holds the vertices associated   */
/*  with a tetrahedral complex (and possibly getting it wrong).              */
/*                                                                           */
/*  WARNING:  fails catastrophically, probably with a segmentation fault, if */
/*  the tag's minipool doesn't yet exist.                                    */
/*                                                                           */
/*  Implemented as a macro to meet your need for speed.                      */
/*                                                                           */
/*  plex:  The tetcomplex in which to find a vertex's attributes.            */
/*         Type (struct tetcomplex *).                                       */
/*  searchtag:  The tag whose attributes (supplementary object) are sought.  */
/*              Type (tag).                                                  */
/*                                                                           */
/*  Returns a pointer to the vertex attributes.  Might crash if the tag has  */
/*    not been allocated yet.                                                */
/*    Type (void *).                                                         */
/*                                                                           */
/*****************************************************************************/

#define tetcomplextag2attributes(plex, searchtag)  \
  proxipooltag2object2(plex->vertexpool, searchtag)

/*****************************************************************************/
/*                                                                           */
/*  proxipooltag2object()   Map a tag to the object it indexes.              */
/*                                                                           */
/*  WARNING:  fails catastrophically, probably with a segmentation fault, if */
/*  the tag's minipool doesn't yet exist.                                    */
/*                                                                           */
/*  Implemented as a macro to meet your need for speed.                      */
/*                                                                           */
/*  pool:  The proxipool in which to find an object.                         */
/*         Type (struct proxipool *).                                        */
/*  searchtag:  The tag whose object is sought.                              */
/*              Type (tag).                                                  */
/*                                                                           */
/*  Returns a pointer to the object.  Might crash if the tag has not been    */
/*    allocated yet.                                                         */
/*    Type (void *).                                                         */
/*                                                                           */
/*****************************************************************************/

#define proxipooltag2object(pool, searchtag)  \
  ((void *) (proxipooltag2mini(pool, searchtag)->object1block +  \
             (searchtag & (OBJECTSPERMINI - 1)) * (pool)->objectbytes1))

/*****************************************************************************/
/*                                                                           */
/*  tetcomplextag2vertex()   Map a tag to the vertex it indexes.             */
/*                                                                           */
/*  This procedure is much like proxipooltag2object(), but it saves callers  */
/*  from needing to remember which proxipool holds the vertices associated   */
/*  with a tetrahedral complex (and possibly getting it wrong).              */
/*                                                                           */
/*  WARNING:  fails catastrophically, probably with a segmentation fault, if */
/*  the tag's minipool doesn't yet exist.                                    */
/*                                                                           */
/*  Implemented as a macro to meet your need for speed.                      */
/*                                                                           */
/*  plex:  The tetcomplex in which to find a vertex.                         */
/*         Type (struct tetcomplex *).                                       */
/*  searchtag:  The tag whose vertex is sought.                              */
/*              Type (tag).                                                  */
/*                                                                           */
/*  Returns a pointer to the vertex.  Might crash if the tag has not been    */
/*    allocated yet.                                                         */
/*    Type (void *).                                                         */
/*                                                                           */
/*****************************************************************************/

#define tetcomplextag2vertex(plex, searchtag)  \
  proxipooltag2object(plex->vertexpool, searchtag)
void tetcomplexdeinit(tetcomplex* plex);
void tetcomplexrestart(tetcomplex* plex);
void tetcomplexinit(tetcomplex* plex, proxipool* vertexpool, int verbose);

/*  The tetcomplexlinktriangle struct is part of the interface of            */
/*  tetcomplexbuild3dstar().  The procedure takes as input a complete 2D     */
/*  link made up of tetcomplexlinktriangles linked together, and converts    */
/*  them into link rings and a 2D link.                                      */

struct tetcomplexlinktriangle {
    tag vtx[3];
    arraypoolulong neighbor[3];
};
typedef char* molecule;

/*  A linkposition represents an atom in a link ring or 2D link.  Usually,   */
/*  the atom is the first atom in some compressed vertex, or the STOP tag at */
/*  the end of the linked list.  Among other things, this struct is useful   */
/*  as an iterator that walks through a link ring or 2D link.                */
/*                                                                           */
/*  The atom in question appears at index `textindex' in molecule `cule',    */
/*  usually.  However, if textindex > lasttextindex, the atom in question is */
/*  really the first atom of the next molecule in the linked list.  This may */
/*  seem oblique, but it's sometimes useful.  For instance, when deleting    */
/*  atoms at a given position in a link ring, this representation increases  */
/*  the likelihood of being able to free an additional molecule at the end   */
/*  of the linked list for reuse elsewhere.                                  */
/*                                                                           */
/*  `moleculetag' is the tag of the current molecule (which is needed for    */
/*  use as a base for compressing the next tag when a new molecule gets      */
/*  appended to the linked list).  `lasttextindex' is the index of the last  */
/*  index in this tag used for compressed vertices (as opposed to the "next  */
/*  molecule tag").  `nextmoleculetag' is the tag of the next molecule in    */
/*  the linked list (possibly STOP).  These two fields are stored so that    */
/*  they only need to be computed once, when `cule' is first encountered.    */

struct linkposition {
    molecule cule;      /* The molecule containing the atom (or right before). */
    int textindex;                                   /* The index of the atom. */
    int lasttextindex;   /* The last atom not part of the "next molecule" tag. */
    tag moleculetag;                       /* The tag for the molecule `cule'. */
    tag nextmoleculetag;  /* The next tag following `moleculetag' in the list. */
    tag groundtag;            /* Tag for the link's owner, used to decompress. */
    proxipool* pool;  /* The pool in which the molecules are allocated. */
};

/*  A link2dposition represents an atom in a 2D link.  It is the data        */
/*  structure used as an iterator that walks through a 2D link.              */

struct link2dposition {
	linkposition innerpos;                  /* Position in the 2D link. */
    tag linktag;     /* Tag for the link's first molecule, used to decompress. */
};

/*  A tetcomplexposition represents a position in a tetrahedral complex, and */
/*  is used to iterate over all the tetrahedra in the complex.               */

struct tetcomplexposition {
	tetcomplex* mycomplex;          /* The complex this position is in. */
    tag starvertex;     /* The vertex whose star is currently being traversed. */
	link2dposition link2dposition;            /* That vertex's 2D link. */
    tag link2dvertex;                  /* Vertex in 2D link, denoting an edge. */
	linkposition link1dposition;           /* That edge's 1D link ring. */
    tag link1dfirstvertex;    /* First vertex in ring (needed at end of ring). */
    tag link1dprevvertex;                 /* Vertex visited on last iteration. */
};

/*  A tetcomplexstar addresses a vertex's 3D star, represented by a 2D link, */
/*  stored as a link2d data structure.  `linkhead' and `linktail' are tags   */
/*  referencing the first and last molecules, respectively, of the link2d    */
/*  linked list.  The tail is stored to make `link2dinsertvertex' fast.      */

struct tetcomplexstar {
    tag linkhead;                 /* First molecule of the link2d linked list. */
    tag linktail;                  /* Last molecule of the link2d linked list. */
};
/*  An arraypool is a two-tiered array from which object can be allocated,   */
/*  either by index or by pointer.  `toparray' is a pointer to the upper     */
/*  tier, which is an array of pointers to the blocks that make up the lower */
/*  tier; and `toparraylen' is the upper tier's length.                      */
/*                                                                           */
/*  There are two mutually exclusive ways to store the stack of freed        */
/*  objects that are waiting to be reallocated.  `deadindexstack' and        */
/*  `deadobjectstack' store the indices or pointers, respectively, of the    */
/*  freed objects.  Indices are more flexible, as they can be converted to   */
/*  pointers, whereas pointers cannot be converted to indices.               */
/*                                                                           */
/*  Other fields are explained by comments below.  `objectsperblock' must be */
/*  2 raised to an integral power.  `objects' is a count of objects that the */
/*  arraypool has allocated for the client, NOT a count of objects malloc'd  */
/*  from the operating system.  `objects' does not include objects that have */
/*  been freed and are waiting on the dead stack to be reallocated.          */
/*  `objects' does not include objects that a client has accessed directly   */
/*  by a call to arraypoolforcelookup() without first being allocated by the */
/*  arraypool.                                                               */
struct arraypool {
    arraypoolulong objectbytes;       /* Size of one object in the lower tier. */
    arraypoolulong objectsperblock;           /* Objects per lower tier block. */
    arraypoolulong log2objectsperblock;      /* Base-2 logarithm of the above. */
    arraypoolulong totalmemory;     /* Total bytes used by whole tiered array. */
    arraypoolulong objects;          /* Number of currently allocated objects. */

    char** toparray;                             /* Pointer to the upper tier. */
    arraypoolulong toparraylen;      /* Length of the upper tier, in pointers. */
    arraypoolulong firstvirgin;          /* First never-allocated array index. */
    arraypoolulong deadindexstack;        /* Stack of freed objects, by index. */
    void* deadobjectstack;              /* Stack of freed objects, by pointer. */
};
typedef arraypoolulong proxipoolulong;
/*  A proxipool is a pool from which objects can be allocated.  With the     */
/*  help of an allocation tree, it allocates objects so that they are close  */
/*  in memory to objects they are spatially close to.  `objectbytes1' is the */
/*  length of each object in bytes, and `objectbytes2' is the length of the  */
/*  supplementary information (if any) associated with each object.          */
/*  `block1offset' is the offset (in bytes) at which the first object        */
/*  appears after the beginning of each minipoolheader, and `block2offset'   */
/*  is the offset at which the first supplementary object appears.           */
/*  `minipoolsize' is the size (in bytes) of each minipool, including one    */
/*  minipoolheader, OBJECTSPERMINI objects, and perhaps OBJECTSPERMINI       */
/*  supplementary objects.                                                   */
/*                                                                           */
/*  `minipoolarray' is a tiered array of minipools.  `objects' is the number */
/*  of objects currently allocated from the proxipool, and `maxobjects' is   */
/*  the largest number that have been allocated at any one time.             */
/*  `nextgroup' is the first tag of the first minipool of the group of       */
/*  minipools that will be allocated next.                                   */
/*                                                                           */
/*  For each allocation index, each proxipool has a poolpool (pool of        */
/*  minipools) from which to allocate objects.  `poolpools' is an arraypool  */
/*  used to map allocation indices to poolpools.  `nextinitindex' is the     */
/*  index of the first poolpool that has not yet been initialized.           */
/*                                                                           */
/*  The number `verbosity' indicates how much debugging information to       */
/*  print, from none (0) to lots (4+).                                       */
struct proxipool {
    size_t objectbytes1;                    /* Size of one object in the pool. */
    size_t objectbytes2;                      /* Size of supplementary object. */
    size_t block1offset;                /* Offset of first object from header. */
    size_t block2offset;              /* Offset of first supplementary object. */
    size_t minipoolsize;            /* Size of one minipool, including header. */

    arraypool minipoolarray;              /* Tiered array of minipools. */
    arraypoolulong objects;          /* Number of currently allocated objects. */
    arraypoolulong maxobjects;              /* Maximum allocated objects ever. */
    tag nextgroup;                 /* Next group of minipools to be allocated. */

    arraypool poolpools;                  /* Tiered array of poolpools. */
    proxipoolulong nextinitindex;   /* First uninitialized index in the array. */
    int verbosity;                /* Amount of debugging information to print. */
};

/*  LINK2DCACHESIZE is the total number of entries in the cache that speeds  */
/*  up lookup of vertices in 2D links.  Because the cache is two-way         */
/*  associative, the number of buckets is half this number.  LINK2DCACHESIZE */
/*  _must_ be a power of two.                                                */

#define LINK2DCACHESIZE 16384

/*  A link2dcache is an array that caches the link rings for 2D link/vertex  */
/*  pairs that have been recently looked up or updated.  A link cache        */
/*  greatly speeds up the link2dfindring() procedure.                        */

typedef struct {
    tag mylink2d;
    tag myvertex;
    tag mylinkring;
}link2dcache[LINK2DCACHESIZE];

/*  A tetcomplex is a tetrahedral complex data structure.  It is composed of */
/*  a set of 3D stars, one for each vertex.  These stars have type `struct   */
/*  tetcomplexstar', and are stored (referenced by vertex tag) through the   */
/*  array `stars'.  The molecules that the stars are composed of are stored  */
/*  in the memory pool `moleculepool'.  All of the stars in `stars' having   */
/*  index less than `nextinitindex' have been initialized, and all the stars */
/*  having index `nextinitindex' or greater have not.                        */
/*                                                                           */
/*  Each tetcomplex has a pointer `vertexpool' to the memory pool in which   */
/*  the complex's vertices are stored.  One set of vertices can be shared by */
/*  any number of tetcomplexes.  Recall that no tetcomplex procedure ever    */
/*  looks at the coordinates of a vertex.  So what is `vertexpool' for?      */
/*  First, it is used to look up allocation indices; the molecules that make */
/*  up a vertex's star are allocated using the same allocation index that    */
/*  was used to allocate the vertex itself.  Second, the procedures          */
/*  `tetcomplextag2vertex' and `tetcomplextag2attributes' are provided to    */
/*  clients, so that clients can look up vertices without having to remember */
/*  which vertices go with which tetcomplex (and perhaps getting it wrong!). */
/*                                                                           */
/*  `tetcount' is the number of solid tetrahedra in the complex, and         */
/*  `ghosttetcount' is the number of ghost tetrahedra.  These counts are not */
/*  guaranteed to be preserved correctly by all operations.  In particular,  */
/*  if the stars become mutually inconsistent during star splaying, these    */
/*  counts will become wrong.  (When the stars are inconsistent with each    */
/*  other, you can't meaningfully say how many tetrahedra there are.)  Also, */
/*  sometimes inserting or removing a ghost tetrahedron doesn't change the   */
/*  data structure at all (except the count of ghost tetrahedra), so         */
/*  `ghosttetcount' is maintained primarily by counting the tetrahedra       */
/*  inserted or removed by the calling application, and can be fooled if the */
/*  application adds or removes a ghost tetrahedron whose absence or         */
/*  presence the tetcomplex cannot verify.                                   */
/*                                                                           */
/*  `consistentflag' indicates whether the stars are (believed to be)        */
/*  mutually consistent.                                                     */
/*                                                                           */
/*  The number `verbosity' indicates how much debugging information to       */
/*  print, from none (0) to lots (4+).                                       */

struct tetcomplex {
	proxipool moleculepool;     /* Pool of molecules storing the links. */
	arraypool stars;    /* `tetcomplexstar' array addressing the links. */
	proxipool* vertexpool;                     /* The pool of vertices. */
    tag nextinitindex;      /* First uninitialized index in the `stars' array. */
    arraypoolulong tetcount;           /* Number of tetrahedra in the complex. */
    arraypoolulong ghosttetcount;          /* Ghost tetrahedra in the complex. */
    int consistentflag;           /* Are the stars consistent with each other? */
    int verbosity;                /* Amount of debugging information to print. */
    link2dcache cache;                  /* Cache for fast lookups in 2D links. */
};
void tricircumcenter3d(behavior* b, starreal* triorg, starreal* tridest, starreal* triapex, starreal* circumcenter, starreal* normal, starreal* xi, starreal* eta);
void tetcircumcenter(behavior* b, starreal* tetorg, starreal* tetdest, starreal* tetfapex, starreal* tettapex, starreal* circumcenter, starreal* xi, starreal* eta, starreal* zeta);
starreal nonregular(behavior* b, starreal* pa, starreal* pb, starreal* pc, starreal* pd, starreal* pe);
starreal orient4d(behavior* b, starreal* pa, starreal* pb, starreal* pc, starreal* pd, starreal* pe, starreal aheight, starreal bheight, starreal cheight, starreal dheight, starreal eheight);
starreal orient4dadapt(starreal* pa, starreal* pb, starreal* pc, starreal* pd, starreal* pe, starreal aheight, starreal bheight, starreal cheight, starreal dheight, starreal eheight, starreal permanent);
starreal orient4dexact(starreal* pa, starreal* pb, starreal* pc, starreal* pd, starreal* pe, starreal aheight, starreal bheight, starreal cheight, starreal dheight, starreal eheight);
starreal insphere(behavior* b, starreal* pa, starreal* pb, starreal* pc, starreal* pd, starreal* pe);
starreal insphereadapt(starreal* pa, starreal* pb, starreal* pc, starreal* pd, starreal* pe, starreal permanent);
starreal insphereexact(starreal* pa, starreal* pb, starreal* pc, starreal* pd, starreal* pe);
starreal orient3d(behavior* b, starreal* pa, starreal* pb, starreal* pc, starreal* pd);
starreal orient3dadapt(starreal* pa, starreal* pb, starreal* pc, starreal* pd, starreal permanent);
starreal orient2d(behavior* b, starreal ax, starreal ay, starreal bx, starreal by, starreal cx, starreal cy);
starreal orient2dadapt(starreal ax, starreal ay, starreal bx, starreal by, starreal cx, starreal cy, starreal detsum);
starreal estimate(int elen, starreal* e);
int scale_expansion_zeroelim(int elen, starreal* e, starreal b, starreal* h);
int fast_expansion_sum_zeroelim(int elen, starreal* e, int flen, starreal* f, starreal* h);
void primitivesinit(void);
tag link2ddeletevertex(proxipool* pool, link2dcache cache, tag linkhead, tag* linktail, tag groundtag, tag deletevertex);
tag link2ddeletevertexnocache(proxipool* pool, tag linkhead, tag* linktail, tag groundtag, tag deletevertex);
tag link2dfindinsert(proxipool* pool, link2dcache cache, tag linkhead, tag* linktail, tag groundtag, tag searchvertex);
void link2dinsertvertex(proxipool* pool, link2dcache cache, tag linkhead, tag* linktail, tag groundtag, tag newvertex, tag linkring);
void link2dinsertvertexnocache(proxipool* pool, tag linkhead, tag* linktail, tag groundtag, tag newvertex, tag linkring);
tag link2dfindring(proxipool* pool, link2dcache cache, tag link, tag groundtag, tag searchvertex);
tag link2dfindringnocache(proxipool* pool, tag link, tag groundtag, tag searchvertex, tag* linktail);
void link2dcacheinit(link2dcache cache);
void link2dprint(proxipool* pool, tag link, tag groundtag);
void link2diterate(link2dposition* pos, tag vertexandlink[2]);
void link2diteratorinit(proxipool* pool, tag link, tag groundtag, link2dposition* pos);
int link2disempty(proxipool* pool, tag link);
void link2ddelete(proxipool* pool, tag link);
tag link2dnew(proxipool* pool, proxipoolulong allocindex);

/*  LINK2DPRIME is a prime number used in a (not very good) hash function.   */

#define LINK2DPRIME 16908799u

int linkringdelete2vertices(proxipool* pool, tag linkring, tag groundtag, tag deletevertex);
int linkringdeletevertex(proxipool* pool, tag linkring, tag groundtag, tag deletevertex);
int linkringinsertvertex(proxipool* pool, tag linkring, tag groundtag, tag searchvertex, tag newvertex);
int linkringdeleteedge(proxipool* pool, tag linkring, tag groundtag, tag endpoint1, tag endpoint2);
int linkringinsertedge(proxipool* pool, tag linkring, tag groundtag, tag endpoint1, tag endpoint2);
struct linkpossmall;
void linkringrotateatoms(proxipool* pool, tag linkring, linkpossmall* pos1, linkpossmall* pos2, linkpossmall* pos3);
tag linkringdeleteatoms(proxipool* pool, linkpossmall* deleteposition, int numatoms);
tag linkringdeleteatoms2(proxipool* pool, linkpossmall* deleteposition, int numatoms);
tag linkringinsertatoms(proxipool* pool, linkpossmall* insertposition, int numatoms, char* newatombuffer, proxipoolulong allocindex);
tag linkringinsertatoms2(proxipool* pool, linkpossmall* insertposition, int numatoms, char* newatombuffer, proxipoolulong allocindex);
void linkringprint(proxipool* pool, tag linkring, tag groundtag);
tag linkringiterate(linkposition* pos);
void linkringiteratorinit(proxipool* pool, tag linkring, tag groundtag, linkposition* pos);
int linkringadjacencies(proxipool* pool, tag linkring, tag groundtag, tag searchvertex, tag adjacencies[2]);
int linkringadjacencies2(proxipool* pool, tag linkring, tag groundtag, tag searchvertex, tag adjacencies[2]);
void linkringdelete(proxipool* pool, tag linkring);
void linkringrestart(proxipool* pool, tag linkring);

/*  MOLECULESIZE is the size of one molecule in characters (and atoms).      */
/*  The choice makes a trade-off between wasted space (most compressed link  */
/*  rings do not use the entirely of the last molecule in their linked       */
/*  lists) and space occupied by the compressed "next molecule tag" index    */
/*  (which is space that can't be used for compressed vertices).  To obtain  */
/*  high speed, 20 seems to be a good choice.  (Higher values don't buy much */
/*  more speed, but cost a lot of memory.)  To obtain maximum compactness,   */
/*  8 is a good choice.                                                      */

#define MOLECULESIZE 20
#define STOP (~ (tag) 1)
void internalerror(void);

/*****************************************************************************/
/*                                                                           */
/*  linkringreadtag()   Read the "next molecule" tag from a molecule.        */
/*                                                                           */
/*  This macro is a sequence of operations repeated in a bunch of the        */
/*  linkring procedures.  It's repeated often enough that it's worth         */
/*  inlining; hence, I've made it a macro.                                   */
/*                                                                           */
/*  moleculetag:  Used as a ground tag for decompressing `nextmoleculetag'   */
/*    (input, not changed).                                                  */
/*  cule:  The molecule to read (input, not changed).                        */
/*  atomindex:  Output only, whereupon it is the last index devoted to       */
/*    compressed vertices (i.e. one before the first index devoted to the    */
/*    compressed "next molecule" tag) in `cule'.                             */
/*  nextmoleculetag:  Output only, whereupon it is the tag for the next      */
/*    molecule after `cule' in the linked list.                              */
/*  nowatom:  A work variable; neither input nor output.                     */
/*  errstring:  A string to print if there's an unrecoverable error.         */
/*                                                                           */
/*****************************************************************************/

#define linkringreadtag(moleculetag, cule, atomindex, nextmoleculetag,  \
                        nowatom, errstring)  \
  nowatom = cule[MOLECULESIZE - 1];  \
  atomindex = MOLECULESIZE - 2;  \
  if (nowatom == (char) STOP) {  \
    nextmoleculetag = STOP;  \
  } else {  \
    nextmoleculetag = nowatom & (char) 127;  \
    while (nowatom >= (char) 0) {  \
      if (atomindex < 0) {  \
        printf(errstring);  \
        printf("  Tag for next molecule not properly terminated.\n");  \
        internalerror();  \
      }  \
      nowatom = cule[atomindex];  \
      nextmoleculetag = (nextmoleculetag << 7) + (nowatom & (char) 127);  \
      atomindex--;  \
    }  \
    nextmoleculetag += (moleculetag >>  \
                        (7 * (MOLECULESIZE - 1 - atomindex))) <<  \
                       (7 * (MOLECULESIZE - 1 - atomindex));  \
  }
tag linkringnewfill(proxipool* pool, tag groundtag, tag* tagarray, proxipoolulong tagarraylen, proxipoolulong allocindex);
tag linkringnew(proxipool* pool, proxipoolulong allocindex);
int linkringtagcompress(tag groundtag, tag newtag, char* newtagatoms);

/*  A smaller version of a linkposition, used internally only.               */

struct linkpossmall {
    molecule cule;      /* The molecule containing the atom (or right before). */
    int textindex;                                   /* The index of the atom. */
    int lasttextindex;   /* The last atom not part of the "next molecule" tag. */
    tag moleculetag;                       /* The tag for the molecule `cule'. */
    tag nextmoleculetag;  /* The next tag following `moleculetag' in the list. */
};

/*  COMPRESSEDTAGLENGTH is an upper bound on the maximum number of bytes a   */
/*  tag occupies after it is compressed.  Used to allocate buffers for       */
/*  atoms in transit.                                                        */

#define COMPRESSEDTAGLENGTH (8 * sizeof(tag) / 7 + 2)

/*  MOLECULEQUEUESIZE is the number of molecules that linkringdeleteatoms()  */
/*  can remember at once.  linkringdeleteatoms() should not be asked to      */
/*  delete more than this many molecules' atoms at once.  Fortunately, the   */
/*  maximum number of atoms that any procedure wants to delete at once is no */
/*  more than three compressed vertices' worth.                              */

#define MOLECULEQUEUESIZE 40

/*  GHOSTVERTEX is a tag that represents a "ghost vertex," which represents  */
/*  a gap in a link ring or a simplicial complex.  If a ghost vertex lies    */
/*  between vertices v and w in a link ring, it means that vw is not an edge */
/*  of the link, even though v and w are successive vertices in the link.    */
/*  To give another example, if a tetrahedron has a face f not shared by     */
/*  another tetrahedron in the simplicial complex, we represent it as        */
/*  sharing a face with a "ghost tetrahedron" whose fourth vertex is the     */
/*  ghost vertex.  Cast to a character, GHOSTVERTEX is also an atom that     */
/*  serves as the compressed form of the GHOSTVERTEX tag.                    */
/*                                                                           */
/*  STOP is a tag used to terminate a sequence of atoms in a molecule,       */
/*  implying either that the atoms continue in the next molecule, or there   */
/*  are no more atoms in the link ring.  STOP is also used as a "next tag"   */
/*  index at the end of a molecule, to indicate that it is the last molecule */
/*  in the linked list.  The STOP tag is not part of the interface of any of */
/*  the linkring procedures, but it is returned by some of the link2d        */
/*  procedures.  Cast to a character, STOP is the one-atom compressed form   */
/*  of the STOP tag.                                                         */

#define GHOSTVERTEX (~ (tag) 0)
arraypoolulong allocmapbytes(struct allocmap* tree);
void allocmapdeletepoint(allocmap* tree, starreal x, starreal y, starreal z);
proxipoolulong allocmapnewpoint(allocmap* tree, starreal x, starreal y, starreal z);
proxipoolulong allocmapindex(allocmap* tree, starreal x, starreal y, starreal z);
void allocmapremoveroot(struct allocmapnode** treeroot);
void allocmapinsertroot(allocmapnode** treeroot, allocmapnode* insertnode, int splayside);
void allocmapmax(allocmapnode** treeroot);
int allocmapsplay(allocmapnode** treeroot, starreal x, starreal y, starreal z, allocmapnode** nearnode);
allocmapnode* allocmapnewnode(allocmap* tree);
void allocmapdeinit(allocmap* tree);
void allocmapinit(allocmap* tree, int verbose);
void allocmaprestart(allocmap* tree);

/*  Each `allocmap' is an allocation tree, used to map a point in 3D space   */
/*  to an index that specifies which minipool (in a proxipool) an object     */
/*  should be allocated from.  The idea is that points that are spatially    */
/*  close together should be close together in memory too.  The allocation   */
/*  tree data structure is a splay tree whose points are ordered along a     */
/*  z-order space-filling curve.                                             */
/*                                                                           */
/*  The nodes are allocated from the memory pool `nodearray'.  The root of   */
/*  the allocation tree is `allocroot'.  When a node is removed from the     */
/*  allocation tree, it is inserted into the spare tree, whose root is       */
/*  `spareroot'.  Nodes in the spare tree can be reused, whereupon they are  */
/*  inserted back into the allocation tree.  The purpose of the spare tree   */
/*  is to allow reuse of allocation indices in a spatially coherent way--    */
/*  ideally, a new point in the allocation tree will receive an index that   */
/*  was previously used by a point close to it.                              */
/*                                                                           */
/*  The number "verbosity" indicates how much debugging information to       */
/*  print, from none (0) to lots (4+).                                       */

struct allocmap {
	arraypool nodearray;      /* Tiered array of allocation tree nodes. */
	allocmapnode* allocroot;                /* Root of allocation tree. */
	allocmapnode* spareroot;                /* Root of spare node tree. */
    int verbosity;                /* Amount of debugging information to print. */
};

/*  Each `allocmapnode' is a node in the allocation tree.  Its fields        */
/*  include its `left' and `right' children and its sample point             */
/*  (xsam, ysam, zsam).  Each node has an allocation index `index', which is */
/*  the node's index in the arraypool of nodes, and is also used by          */
/*  memorypools to decide which chunks of memory to allocate objects from.   */
/*                                                                           */
/*  The node with index zero is the "default" node.  This node can never be  */
/*  part of the splay tree.  It is the node returned when the splay tree is  */
/*  empty, so that every point can be assigned an allocation index even when */
/*  there are no points in the tree.  Nodes allocated to participate in the  */
/*  tree are numbered starting from one.                                     */

struct allocmapnode {
	allocmapnode* left, * right;          /* My left and right children. */
    starreal xsam, ysam, zsam;     /* Coordinates of this node's sample point. */
    proxipoolulong index;                      /* My index (in the arraypool). */
};

/*  The logarithm of the number of allocation tree nodes allocated at once.  */

#define LOG2OCTREENODESPERBLOCK 8
int zorderbefore(starreal x1, starreal y1, starreal z1, starreal x2, starreal y2, starreal z2);
arraypoolulong proxipoolbytes(proxipool* pool);
arraypoolulong proxipoolobjects(proxipool* pool);
void proxipoolfree(proxipool* pool, tag killtag);
tag proxipoolnew(proxipool* pool, proxipoolulong allocindex, void** outobject);
void proxipoolinitpoolpools(proxipool* pool, proxipoolulong endindex);
tag proxipooliterate(proxipool* pool, tag thistag);

/*****************************************************************************/
/*                                                                           */
/*  proxipooltag2allocindex()   Map a tag to its allocation index.           */
/*                                                                           */
/*  WARNING:  fails catastrophically, probably with a segmentation fault, if */
/*  the tag's minipool doesn't yet exist.                                    */
/*                                                                           */
/*  Implemented as a macro to meet your need for speed.                      */
/*                                                                           */
/*  pool:  The proxipool in which an object is allocated.                    */
/*         Type (struct proxipool *).                                        */
/*  searchtag:  The tag of the object whose allocation index is sought.      */
/*              Type (tag).                                                  */
/*                                                                           */
/*  Returns the allocation index of the object.  Might crash if the tag has  */
/*    not been allocated yet.                                                */
/*    Type (proxipoolulong).                                                 */
/*                                                                           */
/*****************************************************************************/

#define proxipooltag2allocindex(pool, searchtag)  \
  (proxipooltag2mini(pool, searchtag)->allocindex)
void proxipooldeinit(proxipool* pool);
void proxipoolinit(proxipool* pool, size_t objectbytes1, size_t objectbytes2, int verbose);
void proxipoolrestart(proxipool* pool);
void proxipoolrestartmini(proxipool* pool, struct minipoolheader* mini);

/*  A poolpool is a pool of minipools associated with one allocation index.  */
/*  It references a list of minipools that have free space, through          */
/*  `freelisthead' and `freelisttail'.  It also references a group in which  */
/*  further minipools can be allocated.  `mygroup' specifies a group by      */
/*  tagging the next minipool that will be allocated in the group.           */
struct poolpool {
    tag freelisthead;            /* Head of list of minipools with free space. */
    tag freelisttail;            /* Tail of list of minipools with free space. */
    tag mygroup;                 /* Next minipool to be allocated in my group. */
};
typedef unsigned short miniindex;
/*  A minipool is a block of OBJECTSPERMINI objects.  It consists of one     */
/*  minipoolheader, then OBJECTSPERMINI contiguous objects, then optionally  */
/*  OBJECTSPERMINI contiguous "supplementary" objects that are paired with   */
/*  the first OBJECTSPERMINI objects.  Typically, the supplementary objects  */
/*  contain information that is rarely accessed, and so ought to go into     */
/*  separate pages of virtual memory.                                        */
/*                                                                           */
/*  The minipoolheader contains information about the minipool.  To keep     */
/*  track of objects that are free to be allocated, `firstvirgin' indicates  */
/*  the index of the first object in the minipool that has never been        */
/*  allocated (implying that the objects that follow it are virgins too),    */
/*  and `freestack' is the head of a linked stack of objects in the minipool */
/*  that have been freed.  `object1block' and `object2block' indicate where  */
/*  the two blocks of OBJECTSPERMINI objects start.                          */
/*                                                                           */
/*  One goal is that objects that are spatially close should be close in     */
/*  memory too.  Therefore, each minipool has an allocation index,           */
/*  `allocindex'.  Typically, geometric objects like vertices are assigned   */
/*  allocation indices based on their positions.  For each alloction index,  */
/*  there is a structure of type `struc poolpool' (stored in an array of     */
/*  poolpools) that maintains a linked list of all the minipools associated  */
/*  with that allocation index.  `nextminifree' is the next minipool in the  */
/*  linked list of minipools that have free space.  (There is one such       */
/*  linked list for each allocation index.)                                  */
struct minipoolheader {
    char* object1block;    /* Pointer to the block of objects in the minipool. */
    char* object2block;          /* Optional pointer to supplementary objects. */
    proxipoolulong allocindex;                       /* Index of the poolpool. */
    tag nextminifree;     /* Next in linked list of minipools with free space. */
    miniindex firstvirgin;        /* First never-allocated object in minipool. */
    miniindex freestack; /* Head of linked stack of freed objects in minipool. */
};
/*  LOG2POOLPOOLSPERBLOCK is the base-2 logarithm of the number of poolpools */
/*  allocated at a time.                                                     */

#define LOG2POOLPOOLSPERBLOCK 8
/*  The number of minipools that are clustered together in a group, all      */
/*  associated with the same allocation index.  Must be a power of 2.        */

#define MINISPERGROUP 8

/*  NOTAMINIINDEX is an index denoting no freed object within a minipool.    */

#define NOTAMINIINDEX ((miniindex) ~0)

/*  NOTATAG is a tag denoting no object in a proxipool.                      */

#define NOTATAG ((tag) ~0)
arraypoolulong arraypoolbytes(arraypool* pool);
arraypoolulong arraypoolallocated(arraypool* pool);
void arraypoolfreeindex(arraypool* pool, arraypoolulong dyingindex);
arraypoolulong arraypoolnewindex(arraypool* pool, void** newptr);
void arraypoolfreeptr(arraypool* pool, void* dyingobject);
void* arraypoolnewptr(arraypool* pool);
void* arraypoollookup(arraypool* pool, arraypoolulong index);
void* arraypoolforcelookup(arraypool* pool, arraypoolulong index);
char* arraypoolsecondtier(arraypool* pool, arraypoolulong index);
void arraypooldeinit(arraypool* pool);
void arraypoolinit(arraypool* pool, arraypoolulong objectbytes, arraypoolulong log2objectsperblock, int alloctype);
void arraypoolrestart(arraypool* pool);

/*  NOTAPOOLINDEX is an index denoting no freed object in the arraypool.     */

#define NOTAPOOLINDEX ((arraypoolulong) ~0)

/*  When the `toparray' runs out of room, it is enlarged, its length         */
/*  multiplied by the following factor.  If you think that the freed space   */
/*  occupied by the old array will not be reused (e.g. it's too small to be  */
/*  re-malloc'd for any other purpose), then a factor of 3 minimizes the     */
/*  average-case memory wasted.  If you think the freed space will be        */
/*  reused, then a factor of (1 + epsilon) minimizes the average-case memory */
/*  wasted, but you should choose at least 2 for speed's sake.               */

#define TOPRESIZEFACTOR 3

/*  TOPARRAYSTARTSIZE is the initial size of the top tier of the tiered      */
/*  array, namely the array `toparray'.  Its value is not critical, as the   */
/*  `toparray' is enlarged whenever necessary.                               */

#define TOPARRAYSTARTSIZE 128
unsigned long randomnation(unsigned long choices);
extern unsigned long randomseed;
void parsecommandline(int argc, char** argv, behavior* b);
#if !defined(STARLIBRARY)
void info(void);
void syntax(void);
#endif
void starfree(void* memptr);
void* starmalloc(size_t size);
void starexit(int status);
/*  Global constants.                                                        */

extern starreal splitter;   /* Used to split real factors for exact multiplication. */
extern starreal epsilon;                         /* Floating-point machine epsilon. */
extern starreal resulterrbound;
extern starreal o2derrboundA, o2derrboundB, o2derrboundC;
extern starreal o3derrboundA, o3derrboundB, o3derrboundC;
extern starreal isperrboundA, isperrboundB, isperrboundC;
typedef ptrdiff_t starlong;
#define FILENAMESIZE 2048

/*  Data structure for command line switches, file names, and operation      */
/*  counts.  Used (instead of global variables) to allow reentrancy.         */

struct behavior {

    /*  Switches for the tetrahedralizer.                                        */
    /*  Read the instructions to find out the meaning of these switches.         */

    int poly;                                                    /* -p switch. */
    int refine;                                                  /* -r switch. */
    int quality;                                                 /* -q switch. */
    /* Maximum acceptable tetrahedron circumradius-to-shortest edge ratio:     */
    starreal qmeasure;                           /* Specified after -q switch. */
    starreal minangle;          /* Min dehedral angle bound, after -q/ switch. */
    starreal goodangle;                         /* Cosine squared of minangle. */
    int varvolume;                      /* -a switch without number following. */
    int fixedvolume;                       /* -a switch with number following. */
    starreal maxvolume;    /* Maximum volume bound, specified after -a switch. */
    int usertest;                                                /* -u switch. */
    int regionattrib;                                            /* -A switch. */
    int convex;                                                  /* -c switch. */
    int weighted;                         /* 1 for -w switch, 2 for -W switch. */
    int conformdel;                                              /* -D switch. */
    int jettison;                                                /* -j switch. */
    int edgesout;                                                /* -e switch. */
    int facesout;                                                /* -f switch. */
    int voronoi;                                                 /* -v switch. */
    int neighbors;                                               /* -n switch. */
    int geomview;                                                /* -g switch. */
    int nobound;                                                 /* -B switch. */
    int nopolywritten;                                           /* -P switch. */
    int nonodewritten;                                           /* -N switch. */
    int noelewritten;                                            /* -E switch. */
    int noiterationnum;                                          /* -I switch. */
    int noholes;                                                 /* -O switch. */
    int noexact;                                                 /* -X switch. */
    /* All items are numbered starting from `firstnumber':                     */
    starulong firstnumber;                            /* Inverse of -z switch. */
    int order;                    /* Element order, specified after -o switch. */
    int nobisect;                 /* Count of how often -Y switch is selected. */
    starlong steiner;   /* Max # of Steiner points, specified after -S switch. */
    int jumpwalk;                                                /* -J switch. */
    int norandom;                                                /* -k switch. */
    int fullrandom;                                              /* -K switch. */
    int docheck;                                                 /* -C switch. */
    int quiet;                                                   /* -Q switch. */
    int verbose;                  /* Count of how often -V switch is selected. */
    /* Determines whether new vertices will be added, other than the input:    */
    int addvertices;                              /* -p, -q, -a, or -u switch. */
    /* Determines whether segments and facets are used at all:                 */
    int usefacets;                        /* -p, -r, -q, -a, -u, or -c switch. */

    int readnodefileflag;                       /* Has a .node file been read? */

    /*  Variables for file names.                                                */

#ifndef STARLIBRARY
    char innodefilename[FILENAMESIZE];                    /* Input .node file. */
    char inelefilename[FILENAMESIZE];                      /* Input .ele file. */
    char inpolyfilename[FILENAMESIZE];                    /* Input .poly file. */
    char areafilename[FILENAMESIZE];                      /* Input .area file. */
    char outnodefilename[FILENAMESIZE];                  /* Output .node file. */
    char outelefilename[FILENAMESIZE];                    /* Output .ele file. */
    char outpolyfilename[FILENAMESIZE];                  /* Output .poly file. */
    char edgefilename[FILENAMESIZE];                     /* Output .edge file. */
    char facefilename[FILENAMESIZE];                     /* Output .face file. */
    char vnodefilename[FILENAMESIZE];                  /* Output .v.node file. */
    char vpolyfilename[FILENAMESIZE];                  /* Output .v.poly file. */
    char neighborfilename[FILENAMESIZE];                /* Output .neigh file. */
    char offfilename[FILENAMESIZE];                       /* Output .off file. */
#endif /* not STARLIBRARY */

    /*  Counts of operations performed.                                          */

    starulong inspherecount;            /* Number of insphere tests performed. */
    starulong orientcount;        /* Number of 3D orientation tests performed. */
    starulong orient4dcount;      /* Number of 4D orientation tests performed. */
    starulong tetcircumcentercount;/* Number of tet circumcenter calculations. */
    starulong tricircumcentercount;    /* Triangular face circumcenter calc's. */

};
#define INPUTLINESIZE 1024
#define INTERFACE 0

/*  To insert lots of self-checks for internal errors, define the SELF_CHECK */
/*  symbol.  This will slow down the program significantly.  It is best to   */
/*  define the symbol using the -DSELF_CHECK compiler switch, but you could  */
/*  write "#define SELF_CHECK" below.  If you are modifying this code, I     */
/*  recommend you turn self-checks on until your work is debugged.           */

/* #define SELF_CHECK */
/* #define PARANOID */

/*  On some machines, my exact arithmetic routines might be defeated by the  */
/*  use of internal extended precision floating-point registers.  The best   */
/*  way to solve this problem is to set the floating-point registers to use  */
/*  single or double precision internally.  On 80x86 processors, this may be */
/*  accomplished by setting the CPU86 symbol in Microsoft operating systems, */
/*  or the LINUX symbol in Linux.                                            */
/*                                                                           */
/*  An inferior solution is to declare certain values as `volatile', thus    */
/*  forcing them to be stored to memory and rounded off.  Unfortunately,     */
/*  this solution might slow Triangle down quite a bit.  To use volatile     */
/*  values, write "#define INEXACT volatile" below.  Normally, however,      */
/*  INEXACT should be defined to be nothing.  ("#define INEXACT".)           */
/*                                                                           */
/*  For more discussion, see Section 5 of my paper, "Adaptive Precision      */
/*  Floating-Point Arithmetic and Fast Robust Geometric Predicates" (also    */
/*  available as Section 6.6 of my dissertation).                            */

/* #define CPU86 */
/* #define LINUX */

#define INEXACT /* Nothing */
/* #define INEXACT volatile */

/*  Maximum number of characters in a file name (including the null).        */

#define FILENAMESIZE 2048

/*  Maximum number of characters in a line read from a file (including the   */
/*  null).                                                                   */

#define INPUTLINESIZE 1024

/*  A number that speaks for itself, every kissable digit.                   */

#define PI 3.141592653589793238462643383279502884197169399375105820974944592308

#endif

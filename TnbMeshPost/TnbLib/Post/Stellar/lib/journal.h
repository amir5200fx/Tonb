#pragma once
#ifndef _journal_header
#define _journal_header
#include "Starbase.h"
#include "top.h"
/*****************************************************************************/
/*             Global journal and helper functions                           */
/*****************************************************************************/
/* improvement journal entry. this should be general enough
   to store information on any change to the mesh, and for each
   change should store enough information to invert it */

enum journalentryclasses
{
    ALLENTRIES,    /* match all entries */
    INSERTDELETE,  /* insertion or deletion of vertices */
    SMOOTH,        /* change position of a single vertex */
    TOPOLOGICAL,   /* topological change involving multiple vertices */
    LABEL          /* classify a vertex */
};

enum journalentrytypes
{
    INSERTVERTEX,  /* insertion of a vertex */
    DELETEVERTEX,  /* deletion of a vertex */
    SMOOTHVERTEX,  /* smoothing of a vertex */
    DELETETET,     /* single tet deletion */
    INSERTTET,     /* single tet insertion */
    FLIP23,        /* 2-3 flip, base case for face removal */
    FLIP32,        /* 3-2 flip, base case for edge removal */
    FLIP22,        /* 2-2 flip */
    FLIP41,        /* 4-1 flip (precedes deletion of interior vertex) */
    FLIP14,        /* 1-4 flip (follows insertion of interior vertex) */
    FLIP13,        /* 1-3 flip (same as 1-4 but inserted vertex is on facet) */
    FLIP31,        /* the inverse of a 1-3 flip */
    FLIP12,        /* 1-2 flip (same as 1-4 but inserted vertex is on edge) */
    FLIP21,        /* inverse of 1-2 */
    CLASSIFY       /* classify vertex (FREEVERTEX, FACETVERTEX, etc) */
};

struct journalentry
{
    int id;             /* unique identifier for this entry */
    int Class;          /* class (smoothing, topological, etc) */
    int type;           /* type of entry, selected from jounalentrytypes */
    tag verts[5];       /* up to five vertices involved in the operation */
    int numverts;       /* the exact number involved in the operation, or the type (for classify)*/
    starreal newpos[3]; /* the new position of the vertex, if it was smoothed */
    starreal oldpos[3]; /* the old position of the vertex, if it was moved */
};

/* GLOBAL */
extern arraypoolstack* journal;
extern arraypoolstack journalstack;

/* print a single journal entry */
void printjournalentry(journalentry* entry);

/* print a single journal entry */
void printjournalentrystream(FILE* o, journalentry* entry, int index);

/* return the ID of the most recent journal entry */
int lastjournalentry(void);

/* copy the top fromtop elements from one stack to another */
void copyjournaltop(arraypoolstack* fromstack,
                    arraypoolstack* tostack,
                    int fromtop);

/* chop the journal down to half its current size */
void chopjournal(void);

/* insert the record of an improvement action in the journal */
void insertjournalentry(tetcomplex* mesh,
                        int type,
                        tag verts[],
                        int numverts,
                        starreal oldpos[],
                        starreal newpos[]);

/* playback a single journal entry */
void playbackjournalentry(tetcomplex* mesh,
                          journalentry* entry);

/* invert a single journal entry */
void invertjournalentry(tetcomplex* mesh,
                        journalentry* entry);

/* invert the last numentries journal entries */
void invertjournaltop(tetcomplex* mesh,
                      int numentries);

/* invert all the journal entries up to (but not including) the one
   with id 'id' */
void invertjournalupto(tetcomplex* mesh,
                       int id);

/* figure out number of ops and start, end indices for given id range */
void journalrangetoindex(int startid,
    int endid,
    int* startindex,
    int* endindex,
    int* numops);

/* print out a range of journal entries to the specified stream */
void printjournalrangestream(FILE* o, int startindex, int endindex);

/* print out the top numentries entries from the journal */
void printjournaltop(int numentries);

/* find and return the last journal entry that involved vtx */
journalentry* findjournalentryvertex(tag vtx, int entryclass);

/* given a vertex, return a tet that the vertex lies in.
   this assumes that the vertex has participated in some
   topological change to the mesh */
void findtetfromvertex(tetcomplex* mesh,
    tag vtx,
    tag outtet[4]);

/* write out current journal to a file  TODO this is unfinished...*/
void writejournal(behavior* b);

/* read a journal from a file  TODO unfinished...*/
void readjournal(char* journalfilename,
                 arraypoolstack* outjournal);

#endif
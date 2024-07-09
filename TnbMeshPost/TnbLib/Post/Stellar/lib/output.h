#pragma once
#ifndef _output_header
#define _output_header
#include "Starbase.h"
/*****************************************************************************/
/*                                                                           */
/*  output (screen, file) functions                                          */
/*                                                                           */
/*****************************************************************************/

/* renumber vertices to include the inserted ones */
void myoutputnumbervertices(behavior* behave,
                            inputs* in,
                            proxipool* pool);

/* customized vertex output TODO: this is mostly copied from Jonathan's
   output routines */
void myoutputvertices(behavior* behave,
                      inputs* in,
                      proxipool* pool,
                      int argc,
                      char** argv);

/* output a file with tet qualities */
void outputtetqualities(tetcomplex* plex,
                        behavior* behave,
                        char filename[],
                        int argc,
                        char** argv,
                        int qualmeasure);

/* output a file with mesh surface faces */
void outputsurfacefaces(tetcomplex* mesh,
                        behavior* behave,
                        char filename[],
                        int argc,
                        char** argv);

/* output improvement statistics */
void outputstats(behavior* behave,
                 tetcomplex* mesh,
                 char filename[],
                 int argc,
                 char** argv);

/* output a mapping from tag -> output vertex number
   TODO is this even still used? */
void outputtagmap(behavior* behave,
                  inputs* in,
                  proxipool* pool,
                  char filename[],
                  int argc,
                  char** argv);

/* output a file with animation info */
void outputanim(behavior* behave,
                tetcomplex* mesh,
                char filename[],
                int passnum,
                int passtype,
                int passstartid,
                int argc,
                char** argv);

/* print out the entire mesh. includes node positions,
   tet node values, and tet quality values */
void outputqualmesh(behavior* b,
                    inputs* in,
                    proxipool* vertexpool,
                    tetcomplex* mesh,
                    int argc,
                    char** argv,
                    int passnum,
                    int passtype,
                    int passstartid,
                    int qualmeasure);



#endif
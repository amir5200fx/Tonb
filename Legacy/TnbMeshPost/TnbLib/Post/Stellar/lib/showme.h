//#pragma once
//#ifndef _showme_header
//#define _showme_header
///*****************************************************************************/
///*                                                                           */
///*    ,d88""\ 888                                   o    o                   */
///*    8888    888o888,  o88""o Y88b    o    /      d8b  d8b      o88888o     */
///*    "Y88b   888  888 d888   b Y88b  d8b  /      d888bdY88b    d888  88b    */
///*     "Y88b, 888  888 8888   8  Y888/Y88b/      / Y88Y Y888b   8888oo888    */
///*       8888 888  888 q888   p   Y8/  Y8/      /   YY   Y888b  q888         */
///*    \_o88P' 888  888  "88oo"     Y    Y      /          Y888b  "88oooo"    */
///*                                                                           */
///*  A Display Program for Meshes and More.                                   */
///*  (showme.c)                                                               */
///*                                                                           */
///*  Version 1.61                                                             */
///*  5 July 2009                                                              */
///*                                                                           */
///*  Portions of Show Me written prior to June 30, 1998 are                   */
///*  Copyright 1995, 1996, 1998                                               */
///*  Jonathan Richard Shewchuk                                                */
///*  965 Sutter Street #815                                                   */
///*  San Francisco, California  94109-6082                                    */
///*  jrs@cs.berkeley.edu                                                      */
///*                                                                           */
///*  Portions of Show Me written after June 30, 1998 are in the public        */
///*  domain, but Show Me as a whole is not.  All rights reserved.             */
///*                                                                           */
///*  This version of Show Me is provided as part of Stellar, a program for    */
///*  improving tetrahedral meshes.  Stellar and this version of Show Me are   */
///*  open source software provided under the Berkeley Source Distribution     */
///*  (BSD) license, which follows.  If you want to use Stellar in a           */
///*  commercial product, the BSD license permits you to do so freely.  Bryan  */
///*  Klingner and I request that you kindly send me an email to let us know   */
///*  what products include Stellar, but it is not a legal requirement.        */
///*                                                                           */
///*  ======================= BSD license begins here. ======================= */
///*                                                                           */
///*  Redistribution and use in source and binary forms, with or without       */
///*  modification, are permitted provided that the following conditions are   */
///*  met:                                                                     */
///*                                                                           */
///*  - Redistributions of source code must retain the above copyright notice, */
///*    this list of conditions and the following disclaimer.                  */
///*                                                                           */
///*  - Redistributions in binary form must reproduce the above copyright      */
///*    notice, this list of conditions and the following disclaimer in the    */
///*    documentation and/or other materials provided with the distribution.   */
///*                                                                           */
///*  - Neither the name of Jonathan Shewchuk nor the name of the University   */
///*    of California nor the names of its contributors may be used to endorse */
///*    or promote products derived from this software without specific prior  */
///*    written permission.                                                    */
///*                                                                           */
///*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS  */
///*  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED    */
///*  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A          */
///*  PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT      */
///*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
///*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED */
///*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR   */
///*  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF   */
///*  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING     */
///*  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS       */
///*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.             */
///*                                                                           */
///*  ======================== BSD license ends here. ======================== */
///*                                                                           */
///*  Additional disclaimer:  Neither I nor any institution I have been        */
///*  associated with warrant this code in any way whatsoever.  This code is   */
///*  provided "as is".  Use at your own risk.                                 */
///*                                                                           */
///*  Hypertext instructions for Show Me will some day be available at         */
///*                                                                           */
///*      http://www.cs.cmu.edu/~quake/showme.html                             */
///*                                                                           */
///*  If you make any improvements to this code, please please please let me   */
///*  know, so that I may obtain the improvements.  Even if you don't change   */
///*  the code, I'd still love to hear what it's being used for.               */
///*                                                                           */
///*****************************************************************************/
//
//
///*  For single precision (which will save some memory and reduce paging),    */
///*  define the symbol SINGLE by using the -DSINGLE compiler switch or by     */
///*  writing "#define SINGLE" below.                                          */
///*                                                                           */
///*  For double precision (which will allow you to display finer meshes),     */
///*  leave SINGLE undefined.                                                  */
//
///* #define SINGLE */
//
//#ifdef SINGLE
//typedef float showmereal;
//#else /* not SINGLE */
//typedef double showmereal;
//#endif /* not SINGLE */
//
///*  On some machines, my exact arithmetic routines might be defeated by the  */
///*  use of internal extended precision floating-point registers.  The best   */
///*  way to solve this problem is to set the floating-point registers to use  */
///*  single or double precision internally.  On 80x86 processors, this may be */
///*  accomplished by setting the CPU86 symbol in Microsoft operating systems, */
///*  or the LINUX symbol in Linux.                                            */
///*                                                                           */
///*  An inferior solution is to declare certain values as `volatile', thus    */
///*  forcing them to be stored to memory and rounded off.  Unfortunately,     */
///*  this solution might slow Triangle down quite a bit.  To use volatile     */
///*  values, write "#define INEXACT volatile" below.  Normally, however,      */
///*  INEXACT should be defined to be nothing.  ("#define INEXACT".)           */
///*                                                                           */
///*  For more discussion, see Section 5 of my paper, "Adaptive Precision      */
///*  Floating-Point Arithmetic and Fast Robust Geometric Predicates" (also    */
///*  available as Section 6.6 of my dissertation).                            */
//
///* #define CPU86 */
///* #define LINUX */
//
///* On some machines, the exact arithmetic routines might be defeated by the  */
///*   use of internal extended precision floating-point registers.  Sometimes */
///*   this problem can be fixed by defining certain values to be volatile,    */
///*   thus forcing them to be stored to memory and rounded off.  This isn't   */
///*   a good solution, though, as it slows Pyramid down.                      */
///*                                                                           */
///* To try this out, write "#define INEXACT volatile" below.  Normally,       */
///*   however, INEXACT should be defined to be nothing.  ("#define INEXACT".) */
//
//#define INEXACT /* Nothing */
///* #define INEXACT volatile */
//
///*  Maximum number of characters in a file name (including the null).        */
//
//#define FILENAMESIZE 2048
//
///*  Maximum number of characters in a line read from a file (including the   */
///*  null).                                                                   */
//
//#define INPUTLINESIZE 1024
//
//#define STARTWIDTH 414
//#define STARTHEIGHT 414
//#define MINWIDTH 50
//#define MINHEIGHT 50
//#define BUTTONHEIGHT 21
//#define BUTTONROWS 4
//#define PANELHEIGHT (BUTTONHEIGHT * BUTTONROWS)
//#define MAXCOLORS 64
//#define MAXGRAYS 64
//
//#define IMAGE_TYPES 8
//#define NOTHING -1
//#define NODE 0
//#define POLY 1
//#define ELE 2
//#define EDGE 3
//#define PART 4
//#define ADJ 5
//#define VORO 6
//#define DATA 7
//
//#define TRIMLEFT 0
//#define TRIMRIGHT 1
//#define TRIMUP 2
//#define TRIMDOWN 3
//
//#define STARTEXPLOSION 0.5
//
//#define DEG2RAD 0.0174532925199433
//#define ONETHIRD 0.333333333333333333333333333333333333333333333333333333333333
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <X11/Xatom.h>
//#ifdef CPU86
//#include <float.h>
//#endif /* CPU86 */
//#ifdef LINUX
//#include <fpu_control.h>
//#endif /* LINUX */
//
//
///*  `showmelong' and `showmeulong' are the types of integer (signed and      */
///*  unsigned, respectively) of most of the indices used internally and       */
///*  externally by ShowMe, including vertex and tetrahedron numbers.  They    */
///*  determine the number of internal data structures that can be allocated,  */
///*  so long choices (e.g. ptrdiff_t and size_t, defined in stddef.h) are     */
///*  recommended.  If the number of tetrahedra might be around 2^28 or more,  */
///*  use 64-bit integers.  On a machine with 32-bit pointers (memory          */
///*  addresses), though, there's no point using integers bigger than 32 bits. */
///*  On a machine with limited memory, smaller integers might allow you to    */
///*  create larger meshes.                                                    */
//
//typedef ptrdiff_t showmelong;
//typedef size_t showmeulong;
//
//
//struct tetra {
//    /* Which tetrahedron is opposite vertex 0-3?  Zero means none.  A number */
//    /* less than zero means it's -neighbor[i], but the neighbor has been     */
//    /* marked invisible.                                                     */
//    showmelong neighbor[4];
//    showmelong nexttet;        /* Links list of tetrahedra with exposed faces. */
//    int invisible;         /* True if this tetrahedron should not be rendered. */
//};
//
///*  A necessary forward declaration.                                         */
//
//int load_image();
//
///*  Global constants.                                                        */
//
//showmereal splitter; /* Used to split real factors for exact multiplication. */
//showmereal epsilon;                       /* Floating-point machine epsilon. */
//showmereal o3derrboundA, o3derrboundB, o3derrboundC, resulterrbound;
//
//
//struct tetra* tetraptr;
//
//Display* display;
//int screen;
//Window rootwindow;
//Window mainwindow;
//Window quitwin;
//Window leftwin;
//Window rightwin;
//Window upwin;
//Window downwin;
//Window resetwin;
//Window pswin;
//Window epswin;
//Window expwin;
//Window exppluswin;
//Window expminuswin;
//Window widthpluswin;
//Window widthminuswin;
//Window versionpluswin;
//Window versionminuswin;
//Window fillwin;
//Window motionwin;
//Window rotatewin[6];
//Window rotateamtwin;
//Window wireframeoptionwin;
//Window perspectivewin;
//Window perspluswin;
//Window persminuswin;
//Window cutleftwin;
//Window cutrightwin;
//Window cutupwin;
//Window cutdownwin;
//Window qualitywin;
//Window nodewin[2];
//Window polywin[2];
//Window elewin[2];
//Window edgewin[2];
//Window partwin[2];
//Window adjwin[2];
//Window voronoiwin[2];
//Window datawin[2];
//
//int windowdepth;
//XEvent event;
//Colormap rootmap;
//XFontStruct* myfont;
//unsigned int width, height;
//int black, white;
//unsigned int showme_foreground;
//GC fontgc;
//GC blackfontgc;
//GC linegc;
//GC trianglegc;
//int bitreverse[MAXCOLORS];
//unsigned int colors[MAXCOLORS];
//XColor rgb[MAXCOLORS];
//unsigned int grays[MAXGRAYS];
//XColor gray[MAXGRAYS];
//int colordisplay;
//int wireframe = 0;
//int perspective = 0;
//int motion = 0;
//
//int start_image, current_image;
//int start_inc, current_inc;
//int loweriteration;
//unsigned int line_width;
//int loaded[2][IMAGE_TYPES];
//showmereal xlo[2][IMAGE_TYPES], ylo[2][IMAGE_TYPES], zlo[2][IMAGE_TYPES];
//showmereal xhi[2][IMAGE_TYPES], yhi[2][IMAGE_TYPES], zhi[2][IMAGE_TYPES];
//showmereal xscale, yscale;
//showmereal xoffset, yoffset;
//int zoom;
//
//showmelong nodes[2];
//int nodedim[2];
//showmereal* nodeptr[2];
//showmelong polynodes[2];
//int polydim[2];
//showmelong polyedges[2], polyholes[2];
//showmereal* polynodeptr[2], * polyholeptr[2];
//showmelong* polysegptr[2];
//showmelong elems[2];
//int elecorners[2];
//showmelong* eleptr[2];
//showmelong edges[2];
//showmelong* edgeptr[2];
//showmereal* normptr[2];
//int subdomains[2];
//int* partition[2];
//showmereal* subdomcenter[2], * subdomshift[2];
//int adjsubdomains[2];
//int* adjptr[2];
//showmelong vnodes[2];
//int vnodedim[2];
//showmereal* vnodeptr[2];
//showmelong vedges[2];
//showmelong* vedgeptr[2];
//showmereal* vnormptr[2];
//showmelong datavalues[2];
//int datadim[2];
//showmereal* dataptr[2];
//showmereal datahist[2][2]; /* Hi & Lo for adaptive scaling of 2D height info */
//int firstnumber[2];
//
//int quiet, fillelem, bw_ps, explode;
//showmereal explosion;
//
//unsigned long randomseed;                     /* Current random number seed. */
//
//int dlist_drawn = 0;
//showmereal amtLeft = 0.0, amtUp = 0.0;
//showmereal lightsourcex = 0.1;
//showmereal lightsourcey = 0.7937;
//showmereal lightsourcez = 0.6;
//
//char filename[FILENAMESIZE];
//char nodefilename[2][FILENAMESIZE];
//char polyfilename[2][FILENAMESIZE];
//char elefilename[2][FILENAMESIZE];
//char edgefilename[2][FILENAMESIZE];
//char partfilename[2][FILENAMESIZE];
//char adjfilename[2][FILENAMESIZE];
//char vnodefilename[2][FILENAMESIZE];
//char vedgefilename[2][FILENAMESIZE];
//char datafilename[2][FILENAMESIZE];
//
///* Original colors */
///*
//char *colorname[] = {"aquamarine", "red", "green yellow", "magenta",
//                     "yellow", "green", "orange", "blue",
//                     "white", "sandy brown", "cyan", "moccasin",
//                     "cadet blue", "coral", "cornflower blue", "sky blue",
//                     "firebrick", "forest green", "gold", "goldenrod",
//                     "gray", "hot pink", "chartreuse", "pale violet red",
//                     "indian red", "khaki", "lavender", "light blue",
//                     "light gray", "light steel blue", "lime green", "azure",
//                     "maroon", "medium aquamarine", "dodger blue", "honeydew",
//                     "medium orchid", "medium sea green", "moccasin",
//                     "medium slate blue", "medium spring green",
//                     "medium turquoise", "medium violet red",
//                     "orange red", "chocolate", "light goldenrod",
//                     "orchid", "pale green", "pink", "plum",
//                     "purple", "salmon", "sea green",
//                     "sienna", "slate blue", "spring green",
//                     "steel blue", "tan", "thistle", "turquoise",
//                     "violet", "violet red", "wheat",
//                     "yellow green"};
//*/
//
//char* colorname[] = { "green4", "green3", "green2", "chartreuse2",
//                     "OliveDrab2", "DarkOliveGreen2",
//                     "SpringGreen3", "SpringGreen2",
//                     "SeaGreen2", "DarkSeaGreen2", "aquamarine2",
//                     "SlateGray2", "LightSteelBlue2",
//                     "LightSkyBlue2", "LightBlue2",
//                     "LightCyan2", "PaleTurquoise2", "CadetBlue2",
//                     "turquoise2", "cyan2", "cyan3",
//                     "SkyBlue2", "DeepSkyBlue2", "SteelBlue2",
//                     "DodgerBlue2", "RoyalBlue2",
//                     "RoyalBlue1", "royal blue",
//                     "blue1", "blue2",
//                     "medium blue", "midnight blue", "navy", "blue4",
//                     "dark slate blue", "purple3", "purple2", "purple1",
//                     "MediumPurple2", "MediumPurple3",
//                     "DarkOrchid2", "DarkOrchid3",
//                     "red4", "red3", "DeepPink3",
//                     "maroon3", "magenta3", "maroon2", "magenta2",
//                     "DeepPink2", "OrangeRed3", "red2", "red", "orange red",
//                     "DarkOrange2", "chocolate2", "tan2", "DarkGoldenRod2",
//                     "goldenrod2", "gold2", "yellow3", "yellow2",
//                     "LightGoldenrod2", "khaki2" };
//
//
//
///* This section is matrix support for 3D graphics. */
//
//struct vec_t {
//    showmereal x, y, z;
//};
//
//struct int_t {
//    int x, y, z;
//};
//
//typedef showmereal matrix_t[3][3];
//typedef showmereal vector_t[3];
//
//matrix_t viewmatrix; /* The current viewing transformation matrix */
//showmereal xcenter, ycenter, zcenter;
//#endif
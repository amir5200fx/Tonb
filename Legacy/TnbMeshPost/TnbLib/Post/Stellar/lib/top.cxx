#include "top.h"

starreal meanthresholds[NUMQUALMEASURES][NUMMEANTHRESHOLDS] =
{
    /* QUALMINSINE thresholds */
    {
        SINE1,
        SINE5,
        SINE10,
        SINE15,
        SINE25,
        SINE35,
        SINE45
    },
    /* QUALRADIUSRATIO thresholds */
    {
        0.1,
        0.2,
        0.3,
        0.4,
        0.5,
        0.6,
        0.7
    },
    /* QUALVLRMS3RATIO thresholds */
    {
        0.1,
        0.2,
        0.3,
        0.4,
        0.5,
        0.6,
        0.7
    },
    /* QUALMEANSINE thresholds */
    {
        SINE1,
        SINE5,
        SINE10,
        SINE15,
        SINE25,
        SINE35,
        SINE45
    },
    /* QUALMINSINEANDEDGERATIO thresholds */
    {
        SINE1,
        SINE5,
        SINE10,
        SINE15,
        SINE25,
        SINE35,
        SINE45
    },
    /* QUALWARPEDMINSINE thresholds */
    {
        SINE1,
        SINE5,
        SINE10,
        SINE15,
        SINE25,
        SINE35,
        SINE45
    }
};

int meanthresholdangles[NUMMEANTHRESHOLDS] =
{
    1,
    5,
    10,
    15,
    25,
    35,
    45
};

/*****************************************************************************/
/*                                                                           */
/*  Global variables                                                         */
/*                                                                           */
/*****************************************************************************/

/* global behavior struct */
behavior behave;

/* global improvement behavior struct */
improvebehavior improvebehave;

/* global statistics */
improvestats stats;

/* global vertex info */
arraypool vertexinfo;

/* global vertex pool */
proxipool* vertexpoolptr;

/* global surface vertex quadrics */
arraypool surfacequadrics;

/* counter for journal IDs */
int maxjournalid = 1;

int globalvertexcount;

/* bounding box for the mesh */
starreal G_boundingbox[6];
starreal G_center[3];
starreal G_range[3];

/* pointer to strain thing from Nutt's sim */
double (*G_evalstrain)(const double* point);
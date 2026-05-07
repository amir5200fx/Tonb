#pragma once
#ifndef _HydDyna_XFoil_Params_Header
#define _HydDyna_XFoil_Params_Header

// XFoil Direct Parameters - refer to XFoil documentation
#define IQX 602  /**< 300 = number of surface panel nodes + 6 */
#define IQX2 301 /**< IQX/2 */
#define IWX 50   /**< number of wake panel nodes */
#define IPX 6    /**< 6 number of qspec[s] distributions */
#define ISX 3    /**< number of airfoil sides */
#define IBX 1204  /**< 600 number of buffer airfoil nodes = 2*IQX */
#define IZX 650  /**< 350 = number of panel nodes [airfoil + wake] */
#define IVX \
  602 /**< 300 = number of nodes along bl on one side of airfoil and wake. */

// XFoil INVERSE parameters  - refer to XFoil documentation
#define ICX \
  257 /**< number of circle-plane points for complex mapping   ( 2^n  + 1 ) */
#define IMX 64  /**< number of complex mapping coefficients  Cn */
#define IMX4 16 /**< = IMX/4 */

#define MIDPOINTCOUNT \
  100 /**< the number of points which define the foil's mid camber line */

#endif

/*
 *******************************************************************************
 * acklib.h
 * Creation date: 21.06.2009
 * Author:        Firoball
 *
 *******************************************************************************
 * $Date: 2010-08-05 00:23:10 +0200 (Do, 05 Aug 2010) $
 * $Revision: 4 $
 * $Author: Firo $
 *
 *******************************************************************************
 * Description
 *
 * Definition Script for Library functions 
 *
 * Comments
 * 
 * for short descriptions see comments in this file
 *
 *******************************************************************************
 */

#ifndef ACKLIB_H
#define ACKLIB_H
/*! \file 
 *  Include for general purpose functions.
 */

/*! \name General Purpose Variables 
 *  These variables can be used temporaily in own scripts:
 *
 *  - VECTOR vecTemp;
 *  - ANGLE  angTemp;
 *  - COLOR  colTemp;
 *  - var    vTemp;
 *  - int    iTemp;
 *  - char   cTemp;
 *  - float  fTemp;
 *  - long   lTemp;
 *
 *  Their value remains valid until the next wait() instruction or the next
 *  function call which could also use those temporary variables.
 */
#ifdef only_for_doxygen
extern VECTOR vecTemp;
extern ANGLE  angTemp;
extern COLOR  colTemp;
extern var    vTemp;
extern int    iTemp;
extern char   cTemp;
extern float  fTemp;
extern long   lTemp;
#endif

/* ----- DEFINITIONS ----- */


/* ----- STRUCTURES ----- */


/* ----- EXTERNAL FUNCTIONS ----- */


/*! Limit angles for ANGLE vector like ang(). 
 *  \param	pang pointer to affected ANGLE 
 */
void vec_ang(ANGLE* pang);

/*! Avoid hysteresis for VECTOR. 
 *  \param	pvec pointer to affected VECTOR 
 *  \param	vHys allowed hysteresis (base 0) 
 */
void vec_hys(VECTOR* pvec, var vHys);

/*! perform clamp() on all elements of a VECTOR. 
 *  \param	pvec pointer to affected VECTOR 
 *  \param	vMinLim minimum limit 
 *  \param	vMaxLim maximum limit 
 */
void vec_clamp(VECTOR* pvec, var vMinLim, var vMaxLim);

/*! Calculate cross product of two vectors. 
 *  \param	pvecN pointer to normal (will be overwritten) 
 *  \param	pvec1 pointer to first VECTOR 
 *  \param	pvec2 pointer to second VECTOR 
 */
void vec_cross(VECTOR* pvecN, VECTOR* pvec1, VECTOR* pvec2);

#include "acklib.c"

#endif
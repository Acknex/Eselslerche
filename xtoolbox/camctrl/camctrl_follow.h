/*
 *******************************************************************************
 * camctrl_follow.h
 * Creation date: 24.06.2009
 * Author:        Firoball
 *
 *******************************************************************************
 * $Date: 2008-11-16 20:30:40 +0100 (So, 16 Nov 2008) $
 * $Revision: 21 $
 * $Author: Firo $
 *
 *******************************************************************************
 * Description
 *
 * Definition script for follower camera
 *
 * Comments
 * 
 * for short descriptions see comments in this file
 *
 *******************************************************************************
 */
#ifndef CAMCTRL_FOLLOW_H
#define CAMCTRL_FOLLOW_H
/*! \file */

/* ----- INCLUDES ----- */


/* ----- DEFINITIONS ----- */

#define CAMCTRL_FOLLOW_ACTIVE	/*!< This define can be evaluated to check if this module is included and active */


/* ----- STRUCTURES ----- */


/* ----- EXTERNAL FUNCTIONS ----- */


/* ----- INTERNAL FUNCTIONS - DO NOT USE ----- */

/*! \internal - Do not use! */
void CAMCTRL__follow_loop(CAMCTRL* psCamctrl);
/*! \internal - Do not use! */
void CAMCTRL__follow_init(CAMCTRL* psCamctrl);

#include "camctrl_follow.c"
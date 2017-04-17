#ifndef actor_c
#define actor_c

// Header
#include "actor.h"
#include "skilldef.h"
#include "movement.h"

/* toolbox project */
#define PRAGMA_PATH "xtoolbox"
#define TOOLBOX_USE_ACKLIB
#define TOOLBOX_USE_CAMCTRL
#define TOOLBOX_USE_ANIMATE
#include "toolbox.h"


VECTOR vecCamdist;
ANGLE angCamAng;
CAMCTRL* cam;
var counter = 0;
var counter2 = 0;
var counter3 = 0;
var vMovemode = 0;
STRING* strActor_anim[3];
var v3Cam_dist[3] = {-300, 0, 0};
var v3Cam_ang[3] = {0, -33, 0};
ENTITY* myPlayer;
SOUND* sndEat = "squish.wav";
SOUND* sndSick = "die.wav";
SOUND* sndFart = "swamp.wav";
SOUND* sndBurp = "roeps.wav";
SOUND* sndJump = "jump.wav";
var sickness = 0;

#include "movement.c"

var camarc;
var camaspect;
VIEW* viewTmp;

void camera_init()
{
	vec_set(&vecCamdist, v3Cam_dist);
	vec_set(&angCamAng, v3Cam_ang);
	cam = CAMCTRL_create(camera);
	CAMCTRL_setMode(cam, CAMCTRL_CHASE);
	CAMCTRL_setDist(cam, &vecCamdist);
	CAMCTRL_setAngle(cam, &angCamAng);
	CAMCTRL_setEntity(cam, me);
	CAMCTRL_show(cam);
	viewTmp = CAMCTRL_getView(cam);
	camarc = viewTmp->arc;
	camaspect =	viewTmp->aspect;
}

var vTimer;
var vSickSound = 0;
var vAnimTimer = 0;

void chase_camera(VECTOR* vecDist)
{
	/* change camera distance to actor relative to moved distance of actor */
	if ((abs(vecDist->y) > vecDist->x) && vecDist->y != 0)
		vTemp = abs(vecDist->y) * 10 / time_step;
	else
		vTemp = vecDist->x * 10 / time_step;
	vec_set (&vecCamdist, v3Cam_dist);
	vecCamdist.x -= vTemp;

	/* camera tilting using mouse */
	angCamAng.tilt += -mouse_force.y * 20 * time_step;
	
	if (sickness != 0)
	{
		/* lustiger mist*/
		vTimer += time_step;
		angCamAng.roll = 20 * sinv(vTimer * 3);
		angCamAng.tilt -= 0.01 * sinv(vTimer * 5) * time_step;
		vecCamdist.y -= 15 * cosv(vTimer * 5) * time_step;
		
		viewTmp->arc -= 0.03 * sinv(vTimer * 7) * time_step;
		viewTmp->aspect -= 0.002 * cosv(vTimer * 7) * time_step;
		my->green = 50 + absv(100 * sinv(vTimer * 4));
		my->red = 0;
		my->blue = 50 + absv(100 * cosv(vTimer * 4));
		set(my, LIGHT);

		/* only when standing */
		if (vMovemode == 2)
		{
			/* ambient sounds */
			if (vAnimTimer >= 45 && vAnimTimer < 85 && vSickSound == 0)
			{
				vSickSound = 1;
				vTemp = snd_play(sndBurp, 100, 0);
				snd_tune(vTemp, 0, random(30) + 70, 0);			
			}
			if (vAnimTimer >= 85 && vSickSound == 1)
			{
				vSickSound = 2;
				vTemp = snd_play(sndFart, 100, 0);
				snd_tune(vTemp, 0, random(30) + 40, 0);			
			}
			if (vAnimTimer < 45)
			{
				vSickSound = 0;
			}
		}
#ifdef furz
		if (vFartTimer < vFartTimerMax)
		{
			vFartTimer += time_step;
		}
		else
		{
			vTemp = snd_play(sndFart, 100, 0);
			snd_tune(vTemp, 0, random(20) + 50, 0);			
			vFartTimer -= vFartTimerMax;
			vFartTimerMax = 16 + random(32);
		}	
#endif
	}
	else
	{
		if (angCamAng.roll > 0)
		{
			angCamAng.roll = maxv(angCamAng.roll - time_step, 0); 
		}
		if (angCamAng.roll < 0)
		{
			angCamAng.roll = minv(angCamAng.roll + time_step, 0); 
		}
		
		if (viewTmp->arc > camarc)
		{
			viewTmp->arc = maxv(viewTmp->arc - time_step, camarc); 
		}
		if (viewTmp->arc < camarc)
		{
			viewTmp->arc = minv(viewTmp->arc + time_step, camarc); 
		}

		if (viewTmp->aspect > camarc)
		{
			viewTmp->aspect = maxv(viewTmp->aspect - time_step, camaspect); 
		}
		if (viewTmp->aspect < camarc)
		{
			viewTmp->aspect = minv(viewTmp->aspect + time_step, camaspect); 
		}

		my->green = maxv(my->green -= time_step,0);
		my->blue = maxv(my->blue -= time_step, 0);

		if (my->green == 0 && my->blue == 0)
			reset(my, LIGHT);
	}
	angCamAng.tilt = clamp(angCamAng.tilt, -60, 0);

}

var vTemplock = 0;
void actor_setForce()
{
	angTemp.pan = -mouse_force.x * ACTOR_TURN_SPEED * time_step;
	angTemp.tilt = 0;
	angTemp.roll = 0;
	
	c_rotate(me, angTemp, GLIDE | IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_SPRITES);

	if ((key_w - key_s) > 0)
		my->forceX = AforceMove * (key_shift + 1);
	else if ((key_w - key_s) < 0)
		my->forceX = AforceMoveBack * (key_shift + 1);
	else
		my->forceX = AforceNone;
	
	my->forceY = (key_a - key_d) * AforceStrafe;
	
	
	//jumping
	if (key_space != 0 && vTemplock == 0)
	{
		vTemplock = 1;
		actor_jump();
		vTemp = snd_play(sndJump, 100, 0);
		snd_tune(vTemp, 0, 50, 0);
		
	}
	else if (key_space == 0)
		vTemplock = 0; 
}


var actor_anim(VECTOR* vecDist)
{

	/* calculate animation speeds dependent from moved distance */
	if (my->forceX != 0)
	{
		vMovemode = 0;
		/* also take strafe into account */
		if (abs(vecDist->x) < abs(vecDist->y))
			vTemp = abs(vecDist->y);
		else
			vTemp = abs(vecDist->x);
					
	}

	else if (my->forceY != 0)
	{
		vMovemode = 1;
		vTemp = abs(vecDist->y);
					
	}
	else
	{
		vMovemode = 2;
		vTemp = 0;
	}
	
	return vTemp;
}

void actor ()
{
	VECTOR vecDist;
	VECTOR vecAdist;

	/* init animation */
	ANIM* psAnim = ANIM_create(me);

/*
	ANIM_addCycle(psAnim, 0, "walk", 0, ANM_CYCLE);	
	ANIM_addCycle(psAnim, 1, "strafe", 0, ANM_CYCLE);	
	ANIM_addCycle(psAnim, 2, "stand", 1, ANM_CYCLE);	
*/
	CYCLES* psCycles = CYCLES_create(3);
	CYCLES_addCycle(psCycles, 0, "walk", 0, ANM_CYCLE);	
	CYCLES_addCycle(psCycles, 1, "strafe", 0, ANM_CYCLE);	
	CYCLES_addCycle(psCycles, 2, "stand", 1, ANM_CYCLE);
	ANIM_addExtCycles(psAnim, psCycles);	
	
	player = me;
	set(my, SHADOW);
	vec_scale(my->scale_x, 1.5);
	my->scale_z = 1;
	c_setminmax(my);
	vec_set(my->scale_x, vector(1,1,1));
	actorInit(my);
	my.z += 20;

	camera_init();
	myPlayer = (ENTITY*)me;
		
	while (1)
	{

		actor_setForce();
		
		/* move player */
		actor_force(vecDist, vecAdist);
		
		/* animate player */
		vTemp = actor_anim(vecDist);
		ANIM_play(psAnim, vMovemode, vTemp);
		/* get state of current animation for animation based events */
		vAnimTimer = ANIM_getAnimPercent(psAnim);

		/* move camera */
		chase_camera(vecDist);
		
		wait(1);
	}
	//should normally be done here but currently is never reached
	ANIM_remove(psAnim);
	ent_remove(me);
	CYCLES_remove(psCycles);
}

	void actorInit (ENTITY* this)
	{
		reset(my, POLYGON);
	}


action flower()
{
	vec_scale(my->scale_x, 0.3);
	vec_set (vecTemp, my->x);
	c_setminmax(my);
	vecTemp.z -= 3000;
	c_trace (my->x, vecTemp, IGNORE_ME|IGNORE_PASSABLE|IGNORE_SPRITES); 
	my->z = target.z - my->min_z; 
	set (my, PASSABLE);
	
	while (myPlayer == NULL)
		wait (1);
		
	while(!is(my, INVISIBLE))
	{
		if (vec_dist(my->x, myPlayer->x) < 40)
		{
			set (my, INVISIBLE);
			//ent_playsound (me, sndEat, 1000);
			if (is(my, FLAG1))
			{
				sickness = 1;
				vTemp = snd_play(sndSick, 100, 0);
				snd_tune(vTemp, 0, random(70) + 70, 0);
				var i = 0;
				while(i < 75)
				{
					i += time_step*2.0;
					ppRadBlur.skill1 = floatd(i, 100);
					wait(1);
				}
				while(i > 0)
				{
					i -= time_step*2.0;
					ppRadBlur.skill1 = floatd(i, 100);
					wait(1);
				}
				ppRadBlur.skill1 = floatd(0, 100);
			}
			else
			{
				sickness = 0;
				snd_play(sndEat, 100, 0);
			}
		}
		wait (1);
	}
	ptr_remove(me);		
}

action flower_sick()
{
	set(my, FLAG1);
	set(my, LIGHT);
	my->red = 255;
	my->green = 0;
	my->blue = 0;
	flower();
}

#endif /* actor_c */
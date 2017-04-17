#include "movement.h"
#include "skilldef.h"
//#include "animate.h"

VECTOR vecTrace;

void actor_init()
{
	vec_set (vecTemp, my->x);
	vecTemp.z -= 3000;
	c_trace (my->x, vecTemp, IGNORE_ME|IGNORE_PASSABLE|/*IGNORE_MODELS|*/IGNORE_SPRITES/*|USE_AABB|USE_BOX*/); 
	my->z = target.z - my->min_z; 
	my->jumpActive = 0;
	my->moveState = Amove_ground;
}

void actor_force(VECTOR* vecDist, VECTOR* vecAdist)
{
	my->lastMoveState = my->moveState;
	if(my->jumpActive > 0)
	{
		my->jumpActive += time_step;
		my->forceZ = AforceJump;
		if (my->jumpActive >= 3.5)
			my->jumpActive = 0;
	}
	else
		my->forceZ = AforceNone;
	/* force calculations */
	my->aforceZ = Agravity;

	vec_accelerate(vecDist, my->speedX, my->forceX, Afriction);
	vec_accelerate(vecAdist, my->aspeedX, my->aforceX, Afriction);

	/* check what is below actor */
	vec_set (vecTemp, my->x);
	vecTemp.z -= 3000;
	c_trace (my->x, vecTemp, IGNORE_ME|IGNORE_PASSABLE/*|IGNORE_MODELS*/|IGNORE_SPRITES/*|USE_BOX*/); 
//DEBUG_VAR(vecAdist->z,3);	

	/* actor on floor or still in air? */
	vTemp = target.z - my->min_z;
	if (my->z <= vTemp)
	{
		my->z = vTemp;
		vecAdist->z = 0;

		/* allow switching to ground mode only after jump has finished to avoid hysteresis and sinking into floor */
		if (my->jumpActive == 0)
		{
			/* switch back from air mode */
			my->moveState = Amove_ground;
		}
	}
	else
	{
		vecAdist->z = clamp(vTemp - my->z, vecAdist->z, 0); //vecAdist->z wird nicht ganz 0, erst wenn sich das vieh bewegt..?
		if (vecAdist->z >= -0.5)//?
			my->moveState = Amove_ground;
		else
			my->moveState = Amove_air;
	}
//DEBUG_VAR(vecAdist->z,23);	
//DEBUG_VAR(my->moveState,63);	
//DEBUG_VAR(vTemp - my->z,43);	
	c_move(me, vecDist, vecAdist, IGNORE_ME|IGNORE_YOU|IGNORE_PASSABLE|GLIDE);

	/* switch to wait mode if on ground and not moving */
	if (my->speedX < 0.1 && my->speedX != 0 && my->speedX > -0.1) my->speedX = 0;
	if (my->speedY < 0.1 && my->speedY != 0 && my->speedY > -0.1) my->speedY = 0;
	if (my->speedX == 0 && my->speedY == 0 && my->moveState == Amove_ground)
		my->moveState = Amove_wait;

}

void actor_jump()
{
	
	if(my->jumpActive == 0 && (my->moveState == Amove_ground || my->moveState == Amove_wait))
	{
		/* check what is above actor */
		vec_set (vecTemp, my->x);
		vecTemp.z += my->max_z + 60;

		if (c_trace (my->x, vecTemp, IGNORE_ME|IGNORE_PASSABLE|/*IGNORE_MODELS|*/IGNORE_SPRITES/*|USE_AABB*/|USE_BOX) == 0)
		{
			/* no obstacle found, start jump procedure */
			my->jumpActive += time_step;
		}
	}
}

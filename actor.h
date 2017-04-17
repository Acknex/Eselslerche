#ifndef actor_h
#define actor_h

// DEFINES

	#define ACTOR_TURN_SPEED 20

	#define ACTOR_CAM_POS_BLEND_FAC 0.3
	#define ACTOR_CAM_POS_OFFSET vector(-400, 0, 128)

	#define ACTOR_CAM_ANG_BLEND_FAC 0.75
	#define ACTOR_CAM_ANG_LOOKAT_OFFSET vector(128, 0, 0)
	
	#define ACTOR_FORWARD_SPEED 200
	#define ACTOR_STRAFE_SPEED 200


void actor ();

void actorInit (ENTITY* this);
void actorPose (ENTITY* this);
void actorCamera (ENTITY* this);

// Code include
#include "actor.c"

#endif /* actor_h */
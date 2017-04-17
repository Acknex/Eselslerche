#ifndef MOVEMENT_H
#define MOVEMENT_H

//Movement subtype
#define Amove_ground 0
#define Amove_wait 1
#define Amove_air 2
#define Amove_slope 3


//Movement behaviour
#define AforceMove 7
#define AforceMoveBack -4
#define AforceStrafe 7
#define AforceJump 70
#define AforceNone 0
#define Agravity -25
#define Afriction 0.55


void actor_init();
void actor_jump();
void actor_force(VECTOR* vecDist, VECTOR* vecAdist);

#endif
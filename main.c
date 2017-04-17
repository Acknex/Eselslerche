#include <acknex.h>
#include <default.c>

#include "Materials.c"
#include "actor.h"

#include "modplay.c"
#define LEVEL_NAME "level.wmb"

var level_change_var = 0;

function level_change_event1()
{
	if(you == player)
	{
		level_change_var = 1;
	}
}

action level_change1()
{
	my.emask |=(ENABLE_IMPACT);
	my.event = level_change_event1;
	while(level_change_var == 0)
	{
		wait(1);
	}
	level_change_var = 0;
	level_load("level.wmb");
}

function level_change_event2()
{
	if(you == player)
	{
		level_change_var = 1;
	}
}

action level_change2()
{
	my.emask |=(ENABLE_IMPACT);
	my.event = level_change_event2;
	while(level_change_var == 0)
	{
		wait(1);
	}
	level_change_var = 0;
	level_load("level2.wmb");
}



int main ()
{
	fps_max = 100;
	// HAR HAR HAR HAR HAR
	level_load(LEVEL_NAME);
	ent_createlayer("Himmel1+6.tga", SKY|CUBE, 1);
	music_start();

	while(key_esc != 1)
		wait (1);
		
	music_stop();
}

function ent_animation() 
{
	if(my.ente_schnell_x > 0.015)
	{
		ent_animate(me, "walk", my.frame_percent, ANM_CYCLE);
		my.frame_percent += my.ente_schnell_x * 5 * time_step;
		my.frame_percent %= 100;
		if(my.frame_percent < 10)local_sound();
//		if(my.frame_percent > 90)steps();
	}
	else
	{
		ent_animate(me, "jump", my.frame_percent, ANM_CYCLE);
		my.frame_percent += 15 * time_step;
		my.frame_percent %= 100;
//		if(my.frame_percent < 1)local_sound();
	}
}

function ent_event() 
{
	if(my.ent_state != ent_flee)
	{
		if((_scan_id == _follow_me_scan)&&((you.id == ent_player)||(you.id == ent_follower)))
		{
			my.ent_handle = handle(you);
			my.ent_state = ent_follows;
		}
	}
	if(_scan_id == _morph_scan)
	{
  		ent_morph(me, "stern.tga");
		set(my, PASSABLE);
	}
	if((_scan_id == _push_scan)&&(you != me)&&(you.id == ent_player))
	{
		if(my.ent_state == ent_follows)
		{
			my.ent_state = ent_flee;
		}
		vec_diff(my.ente_umwelt_x, vector(my.x, my.y, my.z +40), your.x);
		vec_scale(my.ente_umwelt_x, 0.1);
		pushed();
	}
	if((_scan_id == _kick_scan)&&(you != me)&&(you.id == ent_follower))
	{
		if(my.ent_state == ent_follows)
		{
			my.ent_state = ent_flee;
		}
		vec_diff(my.ente_umwelt_x, vector(my.x, my.y, you.z + 40), your.x);
		vec_scale(my.ente_umwelt_x, 0.5);
		pushed();
	}
}

function ent_little()
{
//	init_skills();
	set(me, SHADOW);
	wait(1);
	c_setminmax(me);
//	my.min_z *= 0.5;
   var speed_down = 0;
   VECTOR vFeet;
   vec_for_min(vFeet,me);
   vec_scale(vFeet, my.scale_x);
	my.z -= c_trace(my.x,  vector(my.x, my.y, my.z - 6000), IGNORE_ME|IGNORE_YOU) + my.min_z;
	my.emask |= ENABLE_SCAN|ENABLE_SHOOT|ENABLE_DETECT;
	my.event = ent_event;
	my.id = ent_follower;
	while(1)
	{
		_scan_id = _follow_me_scan;
		c_scan(my.x, my.pan, vector(360, 90, 100), SCAN_ENTS|IGNORE_ME);
		if(ptr_for_handle(my.ent_handle) != NULL)//ohne Überprüfung des handles geht es nícht
		{
			if((my.ent_state == ent_follows))
			{
				you = ptr_for_handle(my.ent_handle);
				ich_schau_zu_dir();//ich_dreh_mich_zu_dir();
				my.roll = 0;
				my.tilt = 0;
				if(abs(my.z - you.z) < vec_dist(you.x, my.x)-20)
				{
					my.ente_schnell_x = (vec_dist(my.x, you.x)-80)*time_step;
					my.ente_schnell_x =  clamp(my.ente_schnell_x, 0, 3);
				}
				else
				{
					my.ente_schnell_x =  0;
					my.ent_state = ent_waits;
				}
			}
			if(my.ent_state == ent_flee)
			{
				you = ptr_for_handle(my.ent_handle);
				ich_schau_von_dir_weg();
				my.roll = 0;
				my.tilt = 0;
				if(vec_dist(my.x,you.x)< 400)
				{
					my.ente_schnell_x = (vec_dist(my.x, you.x)-20)*time_step;
					my.ente_schnell_x =  clamp(my.ente_schnell_x, 0, 3);
				}
				else
				{
					my.ente_schnell_x =  0;
					my.ent_state = ent_waits;
				}
			}
			if(my.ent_state == ent_waits)
			{
				my.ente_schnell_x =  0;
			}
		}
		ent_animation();
      var dist_down; 
      if (c_trace(my.x,vector(my.x,my.y,my.z-5000),IGNORE_ME | IGNORE_PASSABLE | USE_BOX) > 0)
         dist_down = my.z + vFeet.z - target.z; // get distance between player's feet and the ground
      else
         dist_down = 0;

      if (dist_down > 0)  
         dist_down = clamp(dist_down,0,accelerate(speed_down,5,0.1));
      else                
         speed_down = 0;

//      var dist_ahead = 5*(key_w-key_s)*time_step;
//      dist_ahead = sign(dist_ahead)*(abs(dist_ahead) + 0.5*dist_down); // adapt the speed on slopes
      c_move(me,vector(my.ente_schnell_x,0,0),vector(0,0,-dist_down),IGNORE_PASSABLE | GLIDE); // move the player
		wait(1);// in c_move should be my.ente_umwelt_x, my.ente_umwelt_y instead of 0,0, but it collides with ente_schnell_x
		vec_set(my.dist_diff_x, my.x);
	}

}

function ent_big_animation() 
{
	if((my.ent_state == ent_follows))
	{
		if(vec_dist(player.x, my.x)<180)
		{
			ent_animate(me, "push", my.frame_percent, ANM_CYCLE);
			my.frame_percent += 15 * time_step;
			my.frame_percent %= 100;
			if(my.frame_percent < 10)local_sound();
		}
		else
		{
			ent_animate(me, "walk", my.frame_percent, ANM_CYCLE);
			my.frame_percent += my.ente_schnell_x * 5 * time_step;
			my.frame_percent %= 100;
//			if(my.frame_percent < 10)local_sound();
	//		if(my.frame_percent > 90)steps();
		}
	}
	else
	{
		ent_animate(me, "push", my.frame_percent, ANM_CYCLE);
		my.frame_percent += time_step;
		my.frame_percent %= 100;
//		if(my.frame_percent < 1)local_sound();
	}
}
function ent_big_event() 
{
	if(my.ent_state != ent_flee)
	{
		if(_scan_id == _follow_me_scan)
		{
			my.ent_handle = handle(you);
			my.ent_state = ent_follows;
		}
	}
	if(_scan_id == _morph_scan)
	{
  		ent_morph(me, "stern.tga");
		set(my, PASSABLE);
	}
	if((_scan_id == _push_scan)&&(you != me))
	{
		vec_diff(my.ente_umwelt_x, vector(my.x, my.y, my.z +40), your.x);
		vec_scale(my.ente_umwelt_x, 0.1);
		pushed();
	}
}

function ent_big()
{
//	init_skills();
	var push_timer = 0;
	set(me, SHADOW);
	my.id = ent_follower;
	wait(1);
	c_setminmax(me);
	my.max_y *= 0.8;//verhindert, dass die Figuren sich beim Drehen in einander verhakeln.
	my.min_y *= 0.8;
	my.max_x = my.max_y;//verhindert, dass die Figuren sich beim Drehen in einander verhakeln.
	my.min_x = my.min_y;
//	my.min_z *= 0.5;
   var speed_down = 0;
   VECTOR vFeet;
   vec_for_min(vFeet,me);
	my.z -= c_trace(my.x,  vector(my.x, my.y, my.z - 6000), IGNORE_ME|IGNORE_YOU) + my.min_z;
	my.emask |= ENABLE_SCAN|ENABLE_SHOOT|ENABLE_DETECT;
	my.event = ent_big_event;
 	my.id = ent_follower;
 	while(1)
	{
		_scan_id = _follow_me_scan;
		c_scan(my.x, my.pan, vector(120, 90, 150), SCAN_ENTS|IGNORE_ME);
		if(my.ente_umwelt_z > 1)
		{
			vec_scale(my.ente_umwelt_x, 0.8);
//			my.ente_umwelt_x *= 0.8;
//			my.ente_umwelt_y *= 0.8;
//			my.ente_umwelt_z *= 0.8;
		}
		else
		{
			my.ente_umwelt_x = 0;my.ente_umwelt_y = 0;my.ente_umwelt_z = 0;
		}
		if(ptr_for_handle(my.ent_handle) != NULL)//ohne Überprüfung des handles geht es nícht
		{
			if((my.ent_state == ent_follows))
			{
				you = ptr_for_handle(my.ent_handle);
				ich_schau_zu_dir();//ich_dreh_mich_zu_dir();
				my.roll = 0;
				my.tilt = 0;
				if(abs(my.z - you.z) < vec_dist(you.x, my.x)-my.max_x)
				{
					my.ente_schnell_x = (vec_dist(my.x, you.x)-my.max_x)*time_step;
					my.ente_schnell_x =  clamp(my.ente_schnell_x, 0, 1.5);
				}
				else
				{
					my.ente_schnell_x =  0;
					my.ent_state = ent_waits;
				}
			}
			if(my.ent_state == ent_flee)
			{
				you = ptr_for_handle(my.ent_handle);
				ich_schau_von_dir_weg();
				if(vec_dist(my.x,you.x)< 400)
				{
					my.ente_schnell_x = (vec_dist(my.x, you.x)-20)*time_step;
					my.ente_schnell_x =  clamp(my.ente_schnell_x, 0, 1.5);
				}
				else
				{
					my.ente_schnell_x =  0;
					my.ent_state = ent_waits;
				}
			}
			if(my.ent_state == ent_waits)
			{
				my.ente_schnell_x =  0;
			}
		}
    var dist_down; 
      if (c_trace(my.x,vector(my.x,my.y,my.z-5000),IGNORE_ME | IGNORE_PASSABLE | USE_BOX) > 0)
         dist_down = my.z + vFeet.z - target.z; // get distance between player's feet and the ground
      else
         dist_down = 0;

      if (dist_down > 0)  
         dist_down = clamp(dist_down,0,accelerate(speed_down,5,0.1));
      else                
         speed_down = 0;

      var dist_ahead = 5*(key_w-key_s)*time_step;
 		ent_big_animation();
     dist_ahead = sign(dist_ahead)*(abs(dist_ahead) + 0.5*dist_down); // adapt the speed on slopes
      c_move(me,vector(my.ente_schnell_x,0,0),vector(my.ente_umwelt_x, my.ente_umwelt_y,-dist_down),IGNORE_PASSABLE | GLIDE); // move the player
		push_timer += time_step;
		if(push_timer > 1)
		{
			_scan_id = _kick_scan;
			c_scan(my.x, my.pan, vector(200, 190, my.max_x * 2), IGNORE_ME | SCAN_ENTS);
			push_timer = 0;
		}
 		wait(1);
		vec_set(my.dist_diff_x, my.x);
	}

}

function ent_little_old()
{
//	init_skills();
	init_schwerkraft();
	set(me, SHADOW);
	my.id = ent_follower;
	wait(1);
	c_setminmax(me);
	my.z -= c_trace(my.x,  vector(my.x, my.y, my.z - 6000), IGNORE_ME|IGNORE_YOU) + my.min_z;
	my.emask |= ENABLE_SCAN|ENABLE_SHOOT|ENABLE_DETECT;
	my.event = ent_event;
	my.steh_hoehe = my.min_z;
	my.min_z += 20;
  	while(1)
	{
		_scan_id = _follow_me_scan;
		c_scan(my.x, my.pan, vector(360, 90, 100), SCAN_ENTS|IGNORE_ME);
		if(my.ente_umwelt_z > 1)
		{
			vec_scale(my.ente_umwelt_x, 0.8);
//			my.ente_umwelt_x *= 0.8;
//			my.ente_umwelt_y *= 0.8;
//			my.ente_umwelt_z *= 0.8;
		}
		else
		{
			my.ente_umwelt_x = 0;my.ente_umwelt_y = 0;my.ente_umwelt_z = 0;
		}
		if(my.ent_state == ent_follows)
		{
			you = ptr_for_handle(my.ent_handle);
			ich_schau_zu_dir();//ich_dreh_mich_zu_dir();
			my.ente_schnell_x = (vec_dist(my.x, you.x)*time_step)-10;
			my.ente_schnell_x =  clamp(my.ente_schnell_x, 0, 3);
			schwerkraft();
			if(vec_dist(my.x,you.x)> 180)
			{
				temp = c_move(me, vector(my.ente_schnell_x,0, - my.abstand_unten), vector(my.ente_umwelt_x, my.ente_umwelt_y, my.ente_umwelt_z), GLIDE|IGNORE_PASSABLE);
			}
			else
			{
//				if(vec_dist(my.x,you.x)> 320)
				my.ent_state = ent_waits;
			}
		}
		if(my.ent_state == ent_flee)
		{
			you = ptr_for_handle(my.ent_handle);
			ich_schau_von_dir_weg();
			schwerkraft();
			if(vec_dist(my.x,you.x)< 400)
			{
				temp = c_move(me, vector(10*time_step,0, - my.abstand_unten), vector(my.ente_umwelt_x, my.ente_umwelt_y, my.ente_umwelt_z), GLIDE|IGNORE_PASSABLE);
			}
			else
			{
				my.ent_state = ent_waits;
			}
		}
		ent_animation();
		if(my.ent_state == ent_waits)
		{
			schwerkraft();
			c_move(me, vector(0,0, - my.abstand_unten), vector(my.ente_umwelt_x, my.ente_umwelt_y, my.ente_umwelt_z), GLIDE|IGNORE_PASSABLE);
		}
		wait(1);
		vec_set(my.dist_diff_x, my.x);
	}

}

function ente_flieg()
{
//	init_skills();
	my.id = ent_follower;
	wait(1);
	set(me, SHADOW);
	my.emask |= ENABLE_SCAN|ENABLE_SHOOT;
	my.event = ent_event;
  	while(1)
	{
		_scan_id = _follow_me_scan;
		c_scan(my.x, my.pan, vector(360, 90, 100), SCAN_ENTS|IGNORE_ME);
		if(my.ente_umwelt_z > 1)
		{
			vec_scale(my.ente_umwelt_x, 0.8);
//			my.ente_umwelt_x *= 0.8;
//			my.ente_umwelt_y *= 0.8;
//			my.ente_umwelt_z *= 0.8;
		}
		else
		{
			my.ente_umwelt_x = 0;my.ente_umwelt_y = 0;my.ente_umwelt_z = 0;
		}
		if(my.ent_state == ent_follows)
		{
			you = ptr_for_handle(my.ent_handle);
			ich_dreh_mich_zu_dir();
			my.ente_schnell_x = (vec_dist(my.x, you.x)*time_step);
			my.ente_schnell_x =  clamp(my.ente_schnell_x, 0, 3);
			if(vec_dist(my.x,you.x)> 80)
			{
				temp = c_move(me, vector(time_step*20,0, 0), vector(my.ente_umwelt_x, my.ente_umwelt_y, my.ente_umwelt_z), GLIDE|IGNORE_PASSABLE);
			}
			else
			{
//				if(vec_dist(my.x,you.x)> 320)
				my.ent_state = ent_waits;
			}
			ent_animation();
		}
		if(my.ent_state == ent_flee)
		{
			you = ptr_for_handle(my.ent_handle);
			ich_schau_von_dir_weg();
			if(vec_dist(my.x,you.x)< 400)
			{
				temp = c_move(me, vector(time_step*20,0, 0), vector(my.ente_umwelt_x, my.ente_umwelt_y, my.ente_umwelt_z), GLIDE|IGNORE_PASSABLE);
			}
			else
			{
				my.ent_state = ent_waits;
			}
			ent_animation();
		}
		if(my.ent_state == ent_waits)
		{
			c_move(me, vector(0,0, 0), vector(my.ente_umwelt_x, my.ente_umwelt_y, my.ente_umwelt_z), GLIDE|IGNORE_PASSABLE);
		}
		wait(1);
		vec_set(my.dist_diff_x, my.x);
	}
}

function speed_snake()
{
	set(my, PASSABLE);
	set(me, SHADOW);
	c_setminmax(me);
	var counter;
	var phase;
	var pan_sign;
	while(1)
	{
		my.z -= c_trace(my.x, vector(my.x,my.y,my.z-1000), IGNORE_ME|IGNORE_PASSABLE);
		my.z += 18;
		vec_to_angle(temp, normal);
		counter += time_step;
		if(counter < 100)
		{
			phase = 0;
		}
		else
		{
			phase = 1;
		}
		if(phase == 0)
		{
			my.frame_percent += time_step * 15;
			ent_animate(me,"walk",my.frame_percent,ANM_CYCLE);
			my.pan += time_step * sign(pan_sign);// + cos(counter);
			c_move(my, vector(time_step*8,0,0), nullvector, IGNORE_PASSABLE);
		}
		else
		{
			if(counter < 100)
			{
				ent_animate(me,"walk",my.frame_percent,ANM_CYCLE);
				ent_blend("idle",my.frame_percent,(counter-100)*15);
			}
			else
			{
				if(counter > 200)
				{
					counter = 0; phase = 0; pan_sign = random(1.5)-1;my.frame_percent = 0;
				}
				my.frame_percent += time_step * 15;
				ent_animate(me,"stand",my.frame_percent,ANM_CYCLE);
			}
		}
		if(player != 0)
		{
			if(my.y - player.y > 1.2*_sea_extension){my.y = player.y - 1.2*_sea_extension;}
			if(player.y - my.y > 1.2*_sea_extension){my.y = player.y + 1.2*_sea_extension;}
			if(my.x - player.x > 1.2*_sea_extension){my.x = player.x - 1.2*_sea_extension;}
			if(player.x - my.x > 1.2*_sea_extension){my.x = player.x + 1.2*_sea_extension;}
		}
		wait(1);
	}
}

function Zugvogel()
{
	set(my, PASSABLE);
	my.frame_percent = random(80);
	while(1)
	{
		if(player != 0)
		{
			if(my.y - player.y > 1.2*_sea_extension){my.y = player.y - 1.2*_sea_extension;}
			if(player.y - my.y > 1.2*_sea_extension){my.y = player.y + 1.2*_sea_extension;}
			if(my.x - player.x > 1.2*_sea_extension){my.x = player.x - 1.2*_sea_extension;}
			if(player.x - my.x > 1.2*_sea_extension){my.x = player.x + 1.2*_sea_extension;}
			if(my.z - player.z > 0.6*_sea_extension){my.z = player.z - 0.6*_sea_extension;}
			if(player.z - my.z > 0.6*_sea_extension){my.z = player.z + 0.6*_sea_extension;}
		}
		c_move(me,vector(my.scale_x*2*time_step,0,0), nullvector, IGNORE_PASSABLE|GLIDE|IGNORE_MODELS);
		my.frame_percent += 1/my.scale_x*time_step;
		ent_animate(my, "", my.frame_percent, ANM_CYCLE);
		wait(1);
	}
}

function stone_event() 
{
  if(_scan_id == _morph_scan)
  {
  		ent_morph(me, "dust.tga");
		set(my, PASSABLE);
  }
 if((_scan_id == _push_scan)&&(you != me))
  {
		vec_diff(my.ente_umwelt_x, vector(my.x, my.y, my.z +40), your.x);
		vec_scale(my.ente_umwelt_x, 0.1);
		pushed();
	}
if((_scan_id == _kick_scan)&&(you != me))
  {
		vec_diff(my.ente_umwelt_x, vector(my.x, my.y, my.z +40), your.x);
		vec_scale(my.ente_umwelt_x, 0.1);
		pushed();
	}
}

function ent_stone()
{
//	init_skills();
	set(me, SHADOW);
	wait(1);
	c_setminmax(me);
//	my.min_z *= 0.5;
   var speed_down = 0;
   VECTOR vFeet;
   vec_for_min(vFeet,me);
	my.z -= c_trace(my.x,  vector(my.x, my.y, my.z - 6000), IGNORE_ME|IGNORE_YOU) + my.min_z;
	my.emask |= ENABLE_SCAN|ENABLE_SHOOT|ENABLE_DETECT;
	my.event = stone_event;
  	while(1)
	{
		if(my.ente_umwelt_z > 1)
		{
			vec_scale(my.ente_umwelt_x, 0.8);
//			my.ente_umwelt_x *= 0.8;
//			my.ente_umwelt_y *= 0.8;
//			my.ente_umwelt_z *= 0.8;
		}
		else
		{
			my.ente_umwelt_x = 0;my.ente_umwelt_y = 0;my.ente_umwelt_z = 0;
		}
      var dist_down; 
      if (c_trace(my.x,vector(my.x,my.y,my.z-5000),IGNORE_ME | IGNORE_PASSABLE | USE_BOX) > 0)
         dist_down = my.z + vFeet.z - target.z; // get distance between player's feet and the ground
      else
         dist_down = 0;

      if (dist_down > 0)  
         dist_down = clamp(dist_down,0,accelerate(speed_down,5,0.1));
      else                
         speed_down = 0;

      var dist_ahead = 5*(key_w-key_s)*time_step;
      dist_ahead = sign(dist_ahead)*(abs(dist_ahead) + 0.5*dist_down); // adapt the speed on slopes
      c_move(me,vector(0,0,0),vector(my.ente_umwelt_x, my.ente_umwelt_y,-dist_down),IGNORE_PASSABLE | GLIDE); // move the player
		wait(1);
	}

}

function AI_to_adjust()
{
}
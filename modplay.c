/////////////////////////////////////////////////////////////////////////
// Wrapper for bass.dll - Version 1.0 (03/31/02) update 12/18/05	   //
// created by Firoball - http://www.firoball.de - master@firoball.de   //
/////////////////////////////////////////////////////////////////////////

var mod_load(var x,var y);
var mod_init(var x,var y);
var mod_unload();
var mod_play(var x);
var mod_stop(var x);
var mod_volume(var x);
var mod_getname(var x,var y);
var mod_amplify(var x,var y);
var mod_pause(var x);
var mod_resume(var x);
var mod_getattrib(var x, var y);

//Attributes
#define BASS_MUSIC_ATTRIB_AMPLIFY	0
#define BASS_MUSIC_ATTRIB_PANSEP	1
#define BASS_MUSIC_ATTRIB_PSCALER	2
#define BASS_MUSIC_ATTRIB_BPM		3
#define BASS_MUSIC_ATTRIB_SPEED		4
#define BASS_MUSIC_ATTRIB_VOL_GLOBAL 5
#define BASS_MUSIC_ATTRIB_VOL_CHAN	0x100 // + channel #
#define BASS_MUSIC_ATTRIB_VOL_INST	0x200 // + instrument # 

//Frequency Options
#define MOD_LOWFREQ		11025
#define MOD_MEDFREQ		22050
#define MOD_HIGHFREQ	44100 //default;


//Quality Flags (default: all turned off)
#define MOD_INIT8BIT	1	//8Bit playback for slow systems
#define MOD_INITMONO	2	//Mono playback for even slower systems
#define MOD_INIT3D		4	//3D playback for faster system
#define MOD_INITNOSYNC	8 	//turn this flag on to spare cpu time,
 							//but some mods won't work

//MOD Playback Flags (default: all turned off)
#define MOD_LOADLOOP	4		//Loop MOD until stopped
#define MOD_LOADSURROUND 512	//Enable Surround


var mod_handle;
STRING* MOD_Filename = "blirg.mod";
//STRING* MOD_Filename = "D:\\mods\\1.mod";
//STRING* MOD_Filename = "D:\\mods\\muffler_pissi.xm";


void music_start();
void music_stop();

void main()
{
	var bpm;
	video_mode = 7; 
	screen_color.blue = 150;

	
	music_start();

	while (key_esc != 1)
	{
		bpm = mod_getattrib(mod_handle, BASS_MUSIC_ATTRIB_BPM);
		DEBUG_VAR(bpm,23);	

		wait (1);
	}

	music_stop();

}

void music_start()
{
	mod_volume(10);
	mod_init(MOD_HIGHFREQ,MOD_INIT3D);
	mod_handle=mod_load(MOD_Filename,MOD_LOADLOOP+MOD_LOADSURROUND);
	mod_play(mod_handle);
}

void music_stop()
{
	mod_stop(mod_handle);
}


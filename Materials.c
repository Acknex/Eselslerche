#include "PP_Helper.c"

MATERIAL *ppRadBlur =
{
	effect = "ppRadBlur.fx";
}

void materials_startup()
{
	PP_Add(camera, ppRadBlur, NULL);
//	ppRadBlur.skill1 = floatv(0.25);
}

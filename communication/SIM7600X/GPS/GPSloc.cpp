#include "GPSloc.h"

GPSloc::GPSloc()
{
	Lat = 0;
	Log = 0;
	Speed = -1;
}

GPSloc::GPSloc(float lat, float log, float speed)
{
	Lat = lat;
	Log = log;
	Speed = speed;
}

GPSloc::~GPSloc(){
}

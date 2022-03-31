#ifndef gpsloc_h
#define gpsloc_h

class GPSloc{
public:
	 float Lat,Log,Speed;
	GPSloc();
	GPSloc(float lat,float log,float speed);
	~GPSloc();
};

#endif

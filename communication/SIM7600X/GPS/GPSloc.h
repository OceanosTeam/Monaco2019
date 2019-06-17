#ifndef gpsloc_h
#define gpsloc_h

class GPSloc{
public:
    float Lat,Log;
    
    GPSloc();
    GPSloc(float lat,float log);
	~GPSloc();
};

#endif

#ifndef GTSGENERATOR_HPP
#define GTSGENERATOR_HPP

#include <vector>

#define PI        3.1415926535897932
#define TWOPI     6.2831853071795864
#define INVHALFPI 0.6366197723675813


enum states { OFF, TRIG, ATK, ON, REL };


class GTSGenerator
{
public:
	GTSGenerator(int sampleRate);
	void setVol(float vol);
	void setEnv(float A, float R);
	void on(bool state);
	void stepEnv();
	virtual void getChunk(std::vector<float>& buff) = 0;
	virtual void setFreq(int freq) = 0;
	virtual ~GTSGenerator() {}

protected:
	int state_;
	int sampleRate_;
	int freq_;
	float phase_;
	float amp_;
	float vol_;
	float aLen_;
	float rLen_;
	float aInc_;
	float rDec_;
};


#endif

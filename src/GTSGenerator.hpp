#ifndef GTSGENERATOR_HPP
#define GTSGENERATOR_HPP

#include <vector>

#define PI        3.1415926535897932
#define TWOPI     6.2831853071795864
#define INVHALFPI 0.6366197723675813


class GTSGenerator
{
public:
	GTSGenerator(int sampleRate);
	void setVol(float vol);
	virtual void getChunk(std::vector<float>& buff) = 0;
	virtual void setFreq(int freq) = 0;
	virtual ~GTSGenerator() {}

protected:
	int sampleRate_;
	int freq_;
	float vol_;
};


#endif

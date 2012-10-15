/****************************************************************************
|*  ScanlineSampler.h
|*
|*  Declaration of the class ScanlineSampler.
|*  The ScanlineSampler is a sampler which generates samples row wise in 
|*  increasing x value.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#ifndef _SAMPLER_H
#define _SAMPLER_H


#include "ISampler.h"
#include <rendererelements/Sample.h>


class ScanlineSampler : public ISampler {

public:
	ScanlineSampler(void);
	
	~ScanlineSampler(void);

	void init(int res_x, int res_y);

	//generate the next sample in the sequence of all samples
	bool getNextSample(Sample* sample);

	//return whether a sample cyle is complete
	bool cycleComplete();

  //return percentage of generated samples [0,1]
  double percentageOfGeneratedSamples();

private:

	int m_resolutionX;
	int m_resolutionY;

	int m_nextX;
	int m_nextY;

	bool m_cycleComplete;
};


#endif //_SAMPLER_H

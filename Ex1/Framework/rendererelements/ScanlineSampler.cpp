/****************************************************************************
|*  ScanlineSampler.cpp
|*
|*  Defines a sampler which picks generates samples row wise in 
|*  increasing x value.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#include "ScanlineSampler.h"


ScanlineSampler::ScanlineSampler(void){
	m_resolutionX = 0;
	m_resolutionY = 0;

	m_nextX = 0;
	m_nextY = 0;

	m_cycleComplete = false;
}	


ScanlineSampler::~ScanlineSampler(void){
}


void ScanlineSampler::init(int res_x, int res_y) {
	m_resolutionX = res_x;
	m_resolutionY = res_y;

	m_nextX = 0;
	m_nextY = 0;
}

//generate the next sample in the sequence of all samples
bool ScanlineSampler::getNextSample(Sample* sample){
	m_cycleComplete = false;

	if (m_nextY < m_resolutionY) {
		sample->setPosX(m_nextX);
		sample->setPosY(m_nextY);
		sample->setColor(0.0, 0.0, 0.0, 1.0);
    sample->setSize(1);
    sample->setRenderWeight(1.);
    sample->setOldColorRenderWeight(0.);
		
		m_nextX++;

		//if a scanline is complete
		if (m_nextX == m_resolutionX) {
			m_cycleComplete = true;

			m_nextX = 0;
			m_nextY++;
		}
		return true;
	} else {
		sample->setPosX(-1);
		sample->setPosY(-1);
		sample->setColor(0.0, 0.0, 0.0, 1.0);
		return false;
	}
}

//return whether a sample cyle is complete
bool ScanlineSampler::cycleComplete() {
	return m_cycleComplete;
}

//return percentage of generated samples [0,1]
double ScanlineSampler::percentageOfGeneratedSamples(){
  return ((double)m_nextY / (double)m_resolutionY);
}

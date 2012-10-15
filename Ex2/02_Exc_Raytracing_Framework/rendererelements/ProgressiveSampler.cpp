/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#include "ProgressiveSampler.h"
#include <iostream>

ProgressiveSampler::ProgressiveSampler(void){
  m_resolutionX = 0;
  m_resolutionY = 0;

  m_progressionFactor = 0;
  m_nextX = 0;
  m_nextY = 0;

  m_cycleComplete = false;
  m_numberOfSteps = 0;
  m_maxNumberOfSteps = 0;
}	


ProgressiveSampler::~ProgressiveSampler(void){
}


void ProgressiveSampler::init(int res_x, int res_y) {
  m_resolutionX = res_x;
  m_resolutionY = res_y;

  //find nearest power of two with respect to the larger resolution of the image and set progression factor to this value
  double largerResolution = (double) (m_resolutionX > m_resolutionY? m_resolutionX : m_resolutionY);
  m_progressionFactor = 1;

  while (largerResolution > 1) {
    largerResolution /= 2;
    m_progressionFactor = m_progressionFactor << 1; //fast multiply by two
  }

  m_cycleComplete = false;
  m_maxNumberOfSteps = res_x*res_y;
  m_numberOfSteps = 0;
}

//generate the next sample in the sequence of all samples
bool ProgressiveSampler::getNextSample(Sample* sample){
  m_cycleComplete = false;

  if (m_progressionFactor >= 1) {

    sample->setPosX(m_nextX);
    sample->setPosY(m_nextY);
    sample->setSize(m_progressionFactor);
    sample->setColor(0.0, 0.0, 0.0, 1.0);
    sample->setRenderWeight(1.);
    sample->setOldColorRenderWeight(0.);

    int checkValueX, checkValueY;

    //calculate position of next sample
    //(perform this calculation in a loop to skip already rendered sample positions)
    do {
      //get next x position in scanline
      m_nextX += m_progressionFactor;

      //if the current scanline is finished
      if (m_nextX >= m_resolutionX) {
        //go to first pixel of next scanline
        m_nextX = 0;
        m_nextY += m_progressionFactor;

        //if the current rendering cycle is complete
        if (m_nextY >= m_resolutionY) {
          m_cycleComplete = true;
          //switch to next finer rendering cyle
          m_progressionFactor = m_progressionFactor >> 1;  //fast divide by two (will finally be zero)
          m_nextY = 0;
          m_nextX = m_progressionFactor; //(m_nextX = 0, m_nextY = 0 has already been rendered)
        }

      }

      //if this was the last rendering cylce we can already leave this function
      //(without caring about m_nextX or m_nextY)
      if (m_progressionFactor == 0)
        return true;

      checkValueX = m_nextX / (m_progressionFactor << 1);
      checkValueY = m_nextY / (m_progressionFactor << 1);
    }

    //check whether the calculated next sample position lies on the grid of the former rendering cyle
    //(which means that we already rendered this sample)
    while(m_nextX == checkValueX * (m_progressionFactor << 1) && m_nextY == checkValueY * (m_progressionFactor << 1));
    ++m_numberOfSteps;

    return true;
  }
  else {
    sample->setPosX(-1);
    sample->setPosY(-1);
    sample->setColor(0.0, 0.0, 0.0, 1.0);
    return false;
  }
}

//return whether a sample cyle is complete
bool ProgressiveSampler::cycleComplete() {
  return m_cycleComplete;
}

//return percentage of generated samples [0,1]
double ProgressiveSampler::percentageOfGeneratedSamples(){
  return ((double)m_numberOfSteps / (double)m_maxNumberOfSteps);
}
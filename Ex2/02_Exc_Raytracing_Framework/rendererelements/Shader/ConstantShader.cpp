/****************************************************************************
|*  ConstantShader.cpp
|*
|*  ConstantShader implements a shader that returns the color of the point 
|*  without using lights.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/



#include "ConstantShader.h"


ConstantShader::ConstantShader(void) {
}

ConstantShader::~ConstantShader(void) {
}

//Compute color of intersection point
Vector4 ConstantShader::shade(IntersectionData* iData, Scene * scene) {

  //=== EXERCISE 1.2 ===
  Vector4 color_tmp(0,0,0);
  color_tmp = iData->color;
  return color_tmp.clamp01();
}


/****************************************************************************
|*  DiffuseLightingShader.cpp
|*
|*  DiffuseLightingShader implements a shader that computes the color using the 
|*  diffuse part of the lighting equation.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/



#include "DiffuseLightingShader.h"


DiffuseLightingShader::DiffuseLightingShader(void) {
}


DiffuseLightingShader::~DiffuseLightingShader(void) {
}


//Compute color of intersection point
Vector4 DiffuseLightingShader::shade(IntersectionData* iData, Scene * scene) {

  //=== EXERCISE 2.1.2 ===
  Vector4 color_tmp(0,0,0);

  return color_tmp.clamp01();
}



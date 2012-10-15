/****************************************************************************
|*  PhongLightingShader.cpp
|*
|*  Returns phong shaded color.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/



#include "PhongLightingShader.h"



PhongLightingShader::PhongLightingShader(void) {
	m_dC = 1; // constant
	m_dL = 0; // linear
	m_dQ = 0; // quadratic
}


PhongLightingShader::PhongLightingShader(double m_distC, double m_distL, double m_distQ) {
	m_dC = m_distC; // constant
	m_dL = m_distL; // linear
	m_dQ = m_distQ; // quadratic
}


PhongLightingShader::~PhongLightingShader(void) {
}


//Compute color of intersection point
Vector4 PhongLightingShader::shade(IntersectionData* iData, Scene* scene) {

  //===EXERCISE 2.1.3 ===
  Vector4 color_tmp(0,0,0);

  return color_tmp.clamp01();
}



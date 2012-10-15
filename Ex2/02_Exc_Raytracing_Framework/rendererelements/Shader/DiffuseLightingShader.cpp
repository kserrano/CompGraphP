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
  
  Vector3 N = (iData->normal).normalize(); //get the normal at the intersection calculated in 2.1.1

	std::vector<ILight*> sourcelights = scene->getLights(); // get the vector of sources light

	Vector4 I; // intensity
	Vector3 L; // vector from intersection point to light
	for (std::vector<ILight*>::const_iterator l = sourcelights.cbegin(); l != sourcelights.cend(); ++l) { // Use iterator
		L = ((*l)->getPosition() - iData->position).normalize();
		if(N.dot(L)>0){
			I = I + (*l)->getColor().componentMul(iData->material->diffuse)* N.dot(L); // diffuse model formula
		}
	}
	color_tmp = I;
	return color_tmp.clamp01();
}


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
#include <math.h>


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
    Vector3 N = (iData->normal).normalize();
	std::vector<ILight*> sourcelights = scene->getNonOccludedLights(iData->position);
	Vector4 I_a,I_p,k_a,k_d,k_s;
	Vector4 I,Idiff,Iamb,Ispec;
	Vector3 L,R,V;
	double n;
	I_a = scene->getAmbient();
	k_a = iData->material->ambient;
	Iamb = I_a.componentMul(k_a);
	for (std::vector<ILight*>::const_iterator l = sourcelights.cbegin(); l != sourcelights.cend(); ++l) { // Use iterator
		L = ((*l)->getPosition() - iData->position).normalize(); // calculate L
		R = ((N.operator*(2)).operator*(N.dot(L))-L).normalize(); // calculate R
		V = ((scene->getCamera()->getPosition())-iData->position).normalize(); // calculate V
		if(N.dot(L)>0){
			I_p = (*l)->getColor(); // get the color of light source
			k_d = iData->material->diffuse;
			Idiff = Idiff + I_p.componentMul(k_d.operator*(N.dot(L))); // calculate the diffuse shading model
			if(V.dot(R)>0){ // check if the light contribute to specular reflection
				k_s = iData->material->specular;
				n = iData->material->shininess;
				Ispec = Ispec + I_p.componentMul(k_s).operator*(pow(V.dot(R),n)); // specular model
			}

		}
	}
	color_tmp = Iamb + Idiff + Ispec; // the phong model shading is the combination of the ambient, diffuse and specular reflection

  return color_tmp.clamp01();
}



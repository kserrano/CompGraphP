/****************************************************************************
|*  PhongLightingShader.h
|*
|*  Declaration of the class PhongLightingShader.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#ifndef _PHONGLIGHTINGSHADER_H
#define _PHONGLIGHTINGSHADER_H


#include <rendererelements/shader/IShader.h>
#include <utils/Ray.h>


class PhongLightingShader : public IShader  {

public:
	PhongLightingShader(void);

	PhongLightingShader(double disC, double distL, double distQ);

	~PhongLightingShader(void);

	//Compute color of intersection point
	Vector4 shade(IntersectionData* iData, Scene* scene);
	//Vector4 shade(const IntersectionData &iData, Scene* scene);

private:

	// light parameter
	double m_dC;
	double m_dL;
	double m_dQ;

};


#endif //_PHONGLIGHTINGSHADER_H

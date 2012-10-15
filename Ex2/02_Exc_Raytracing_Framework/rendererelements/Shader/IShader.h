/****************************************************************************
|*  IShader.h
|*
|*  Abstract Base Class definition of a Shader. The shader takes a list
|*  of non-occluded light sources and the intersection data to compute
|*  the color at the intersection point
|*   
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#ifndef _ISHADER_H
#define _ISHADER_H


#include <rendererelements/IntersectionData.h>
#include <Scene.h>


class IShader {

public:
	virtual ~IShader(void) {};

	//Compute color of intersection point
	virtual Vector4 shade(IntersectionData* iData, Scene* scene) = 0;
	//virtual Vector4 shade(const IntersectionData &iData, Scene* scene) = 0;
};


#endif //_ISHADER_H

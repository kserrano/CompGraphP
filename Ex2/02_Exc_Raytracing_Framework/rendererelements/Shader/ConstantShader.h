/****************************************************************************
|*  ConstantShader.h
|*
|*  Declaration of the class ConstantShader.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#ifndef _CONSTANTSHADER_H
#define _CONSTANTSHADER_H


#include <rendererelements/shader/IShader.h>
#include <utils/Ray.h>


class ConstantShader : public IShader  {

public:
	ConstantShader(void);

	~ConstantShader(void);

	//Compute color of intersection point
	Vector4 shade(IntersectionData* iData, Scene* scene);

};


#endif //_CONSTANTSHADER_H

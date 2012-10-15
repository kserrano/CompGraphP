/****************************************************************************
|*  DiffuseLightingShader.h
|*
|*  Declaration of the class DiffuseLightingShader.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#ifndef _DiffuseLightingShader_H
#define _DiffuseLightingShader_H


#include <rendererelements/shader/IShader.h>
#include <utils/Ray.h>


class DiffuseLightingShader : public IShader  {

public:
	DiffuseLightingShader(void);

	~DiffuseLightingShader(void);

	//Compute color of intersection point
	Vector4 shade(IntersectionData* iData, Scene* scene);
	//Vector4 shade(const IntersectionData &iData, Scene* scene);

};


#endif //_DiffuseLightingShader_H

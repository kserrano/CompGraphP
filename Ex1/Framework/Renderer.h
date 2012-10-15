/****************************************************************************
|*  Renderer.h
|*
|*  Declaration of a Renderer object.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#ifndef _SIMPLE_RENDERER_H
#define _SIMPLE_RENDERER_H

#include <stdlib.h>
#include <vector>

#include <Scene.h>
#include <rendererelements/ISampler.h>
#include <rendererelements/Sample.h>
#include <rendererelements/IntersectionData.h>
#include <rendererelements/shader/IShader.h>
#include <utils/Point.h>
#include <utils/Matrix4.h>
#include <utils/IFunctionObservable.h>


class Renderer : public IFunctionObservable {
	
public:	
	Renderer(void);

	~Renderer(void);

	//main renderloop that raytraces the given scene
	virtual void render(Scene* scene);

	void setShader(IShader* shader); 
	void setSampler(ISampler* sampler);

	void setRecursiondepth(unsigned int depth);

	double status();

private:
	//trace the ray and find out the color at its intersection point with the scene
	Vector4 traceColor(Ray ray, Scene* scene, unsigned int recDepth);


protected:

private:
	ISampler* m_sampler;

	IShader* m_shader;

	unsigned int m_recursionDepth;

	unsigned long m_numOfAllPixels;
	unsigned long m_numOfRenderedPixels;
};

#endif //_SIMPLE_RENDERER_H

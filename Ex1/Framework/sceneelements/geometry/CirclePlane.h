/****************************************************************************
|*  CirclePlane.h
|*
|*  Declaration of the class CirclePlane.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#ifndef _CIRCLEPLANE_H
#define _CIRCLEPLANE_H


#include <sceneelements/IElement.h>
#include <sceneelements/geometry/Plane.h>
#include <utils/Material.h>
#include <utils/Vector3.h>


class CirclePlane : public Plane {

public:

	CirclePlane(Material* material);
  ~CirclePlane();
	
	//intersect circleplane with a ray
	virtual bool intersect(const Ray &ray, IntersectionData* iData);


private://methods
	//chooses the right color for the given point on the plane
	Vector4 getColorAt(Vector3 point);

	//chooses the right material for the given point on the plane
	Material* getMaterialAt(Vector3 point);

private://data
	
	Vector4 m_alternativeColor;
	Material* m_alternativeMaterial;

};


#endif //_CIRCLEPLANE_H

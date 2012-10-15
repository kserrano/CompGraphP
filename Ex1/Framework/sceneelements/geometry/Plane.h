/****************************************************************************
|*  Plane.h
|*
|*  Declaration of the class Plane.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#ifndef _PLANE_H
#define _PLANE_H


#include <sceneelements/IElement.h>
#include <utils/Material.h>
#include <utils/Vector3.h>


class Plane : public IElement {

public:

	Plane(Material* material);
	
	//intersect plane with a ray
	virtual bool intersect(const Ray &ray, IntersectionData* iData);

	// setter & getter
	void setPoint(Vector3 point);
	Vector3 getPoint(void);

	void setNormal(Vector3 normal);
	Vector3 getNormal(void);


protected:
	Vector3 m_point;
	Vector3 m_normal;

};


#endif //_PLANE_H

/****************************************************************************
|*  Sphere.h
|*
|*  Declaration of the class Sphere.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#ifndef _SPHERE_H
#define _SPHERE_H


#define PI 3.1415926



#include <sceneelements/IElement.h>
#include <utils/Material.h>
#include <utils/Vector3.h>


class Sphere : public IElement {

public:

	Sphere(Material* material);
	
	//intersect sphere with a ray
	virtual bool intersect(const Ray &ray, IntersectionData* iData);

	// setter & getter
	void setCenter(Vector3 center);
	Vector3 getCenter(void);

	void setRadius(double r);
	double getRadius(void);

	AABB getBB() const;
	Vector3 getCentroid() const { return m_center; };
private:

	Vector3 m_center;
	double m_radius;


};


#endif //_SPHERE_H

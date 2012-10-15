/****************************************************************************
|*  Plane.cpp
|*
|*  Defines a infinite plane in space.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#include "Plane.h"


Plane::Plane(Material* material) {
	

	m_point = Vector3(0.0, 0.0, 0.0);
	m_normal = Vector3(0.0, 0.0, 1.0);

	m_material = material;

	m_finite = false;
}


//intersect plane with a ray
bool Plane::intersect(const Ray &ray, IntersectionData* iData) {

  double t = (m_point.dot(m_normal) - ray.point.dot(m_normal))/ray.direction.dot(m_normal);
  if ( ( t>=ray.min_t && t<=ray.max_t ) && t<iData->t )
  {
    iData->color=getColor();
    iData->t=t;
    iData->position=ray.getPointOnRay(iData->t);
	
    //===EXERCISE 2.1.1 ===

	iData->material = getMaterial();
	iData->normal = getNormal();
	iData->reflectionPercentage = getReflectionPercentage();
    return true;
  }

	return false;
}

// setter & getter
void Plane::setPoint(Vector3 point) {
	m_point = point;
}
Vector3 Plane::getPoint(void) {
	return m_point;
}


void Plane::setNormal(Vector3 normal) {
	m_normal = normal.normalize();
}
Vector3 Plane::getNormal(void) {
	return m_normal;
}


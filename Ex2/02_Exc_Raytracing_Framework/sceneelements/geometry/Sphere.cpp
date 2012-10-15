/****************************************************************************
|*  Sphere.cpp
|*
|*  Defines a sphere in space.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#include "Sphere.h"


Sphere::Sphere(Material* material) {
	m_center = Vector3();
	m_radius = 1.0;

	m_material = material;

	m_finite = true;
}

//intersect sphere with a ray
bool Sphere::intersect(const Ray &ray, IntersectionData* iData) {
  //=== EXERCISE 1.3.2 ===
  //Resolving the problem algebraicaly, we get the following coefficients of a quadratic equation in t:
  double a=ray.direction.dot(ray.direction);
  double b=2*(ray.point.dot(ray.direction) - m_center.dot(ray.direction));
  double c=m_center.dot(m_center)+ray.point.dot(ray.point) - 2.0*m_center.dot(ray.point) - m_radius*m_radius;

  double discriminant = b*b - 4.0*a*c;
  if (discriminant<0)
  {
    return false;

  }else{
    double t1=(-b+sqrt(discriminant))/(2.0*a);
    double t2=(-b-sqrt(discriminant))/(2.0*a);

    bool b1= (t1>=ray.min_t && t1<=ray.max_t) && t1<iData->t ;
    bool b2= (t2>=ray.min_t && t2<=ray.max_t) && t2<iData->t ;

    if (b1||b2)
    {

      if(b1)
        iData->t=t1;

      if(b2)
        iData->t=t2;

      if (b1 && b2)
      {
        iData->t=(t2<t1?t2:t1);
      }

      iData->position=ray.getPointOnRay(iData->t);
      iData->color=getColor();
      iData->material=getMaterial();
      iData->sourcePosition=ray.point;
      iData->normal=(ray.getPointOnRay(iData->t) - m_center).normalize();

      iData->reflectionPercentage=getReflectionPercentage();
      iData->refractionIndex=getRefractionIndex();
      iData->refractionPercentage=getRefractionPercentage();
      iData->rayEntersObject= (ray.direction.dot(iData->normal)<0.0);

	  iData->reflectionPercentage = getReflectionPercentage();

      return true;
    }
  }

  return false;
}


// setter & getter
void Sphere::setCenter(Vector3 center) {
	m_center = center;
	
}
Vector3 Sphere::getCenter(void) {
	return m_center;
}


void Sphere::setRadius(double r) {
	m_radius = r;
	
}
double Sphere::getRadius(void) {
	return m_radius;
}

AABB Sphere::getBB() const {
	AABB bb;
	
	Vector3 offset(m_radius, m_radius, m_radius);
	bb.lowerCorner = m_center - offset;
	bb.upperCorner = m_center + offset;

	return bb;
}

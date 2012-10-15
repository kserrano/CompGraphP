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


  //Resolving the problem algebraically, we get the following coefficients of a quadratic equation in t:
  double a=ray.direction.dot(ray.direction);
  double b=2*(ray.point.dot(ray.direction) - m_center.dot(ray.direction));
  double c=m_center.dot(m_center)+ray.point.dot(ray.point) - 2.0*m_center.dot(ray.point) - m_radius*m_radius;

  //Check if there is a solution:
  double discriminant = b*b - 4.0*a*c;
  if (discriminant<0)
  {
	//There is no solution:
    return false;

  }else{
	//Compute the two solutions:
    double t1=(-b+sqrt(discriminant))/(2.0*a);
    double t2=(-b-sqrt(discriminant))/(2.0*a);

	//Check if the solutions are valid for our problem:
    bool b1= (t1>=ray.min_t && t1<=ray.max_t) && t1<iData->t ;
    bool b2= (t2>=ray.min_t && t2<=ray.max_t) && t2<iData->t ;

    if (b1||b2)
    {
	  //Assign the smaller/closer valid solution 
      if(b1)
        iData->t=t1;

      if(b2)
        iData->t=t2;

      if (b1 && b2)
      {
        iData->t=(t2<t1?t2:t1);
      }

	  //Intersection information
      iData->position=ray.getPointOnRay(iData->t);
      iData->color=getColor();
      iData->sourcePosition=ray.point;


	  //Additional intersection information for Exercise 2.2.2
	  iData->normal=(ray.getPointOnRay(iData->t) - m_center).normalize();
	  iData->material=getMaterial();
      iData->reflectionPercentage=getReflectionPercentage();
      iData->refractionIndex=getRefractionIndex();
      iData->refractionPercentage=getRefractionPercentage();
      iData->rayEntersObject= (ray.direction.dot(iData->normal)<0.0);

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

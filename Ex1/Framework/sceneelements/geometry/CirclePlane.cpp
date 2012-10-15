/****************************************************************************
|*  CirclePlane.cpp
|*
|*  Defines a infinite plane in space which has circles of different 
|*  colors.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li - Applied Geometry Group ETH Zurich
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch
\***********************************************************/


#include "CirclePlane.h"


CirclePlane::CirclePlane(Material* material):Plane(material){

	m_point = Vector3(0.0, 0.0, 0.0);
	m_normal = Vector3(0.0, 0.0, 1.0);

	m_material = material;

	m_finite = false;

  m_alternativeMaterial = new Material();
  m_alternativeMaterial->emission = Vector4(0.0, 0.0, 0.0, 1.0);
  m_alternativeMaterial->ambient = Vector4(0.0, 0.0, 0.0, 1.0);
  m_alternativeMaterial->diffuse = Vector4(1.0, 1.0, 1.0, 1.0);
  m_alternativeMaterial->specular = Vector4(0.0, 0.0, 0.0, 1.0);
  m_alternativeMaterial->shininess = 10;

  m_alternativeColor = Vector4(1.0,1.0,1.0,1.0);
}

CirclePlane::~CirclePlane(){
  delete m_alternativeMaterial;
}


//intersect circleplane with a ray
bool CirclePlane::intersect(const Ray &ray, IntersectionData* iData) {

  if (Plane::intersect(ray,iData))
  {
    double t=iData->t;
    iData->color=getColorAt(ray.getPointOnRay(t));
    iData->material=getMaterialAt(ray.getPointOnRay(t));
    return true;
  }

  return false;
}


//chooses the right color for the given point on the plane
Vector4 CirclePlane::getColorAt(Vector3 point){
	int dist = (int)( point - m_point).length();
	if (dist%2 == 0) {
		return m_color;
	}
	else {
		return m_alternativeColor;
	}
}

Material* CirclePlane::getMaterialAt(Vector3 point) {
	int dist = (int)( point - m_point).length();
	if (dist%2 == 0) {
		return m_material;
	}
	else {
		return m_alternativeMaterial;
	}
}



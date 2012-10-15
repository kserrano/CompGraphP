/****************************************************************************
|*  Torus.cpp
|*
|*  Defines a quadric in space.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#include "Torus.h"
#include "utils/rpoly.h"

#include <iostream>

Torus::Torus(Material* material) : m_R(2), m_r(1) {
	m_center = Vector3();

	m_color = Vector4(1.0, 1.0, 1.0, 1.0);
	m_material = material;

	m_finite = true;
}



bool Torus::intersect(const Ray &ray, IntersectionData* iData) {

  //===EXERCISE 2.3.1 ===

  return false;
}

// setter & getter
void Torus::setCenter(Vector3 center) {
	m_center = center;
}
Vector3 Torus::getCenter(void) {
	return m_center;
}


void Torus::setR(double R) {
	m_R = R;
}

double Torus::getR(void) {
	return m_R;
}

void Torus::setr(double r) {
	m_r = r;
}

double Torus::getr(void) {
	return m_r;
}

AABB Torus::getBB() const {

	//initialize corners of BB 
	Vector3 lower;
  lower.x = m_center.x - m_R - m_r;
  lower.y = m_center.y - m_R - m_r;
  lower.z = m_center.z - m_r;

  Vector3 upper;
  upper.x = m_center.x + m_R + m_r;
  upper.y = m_center.y + m_R + m_r;
  upper.z = m_center.z + m_r;

	return AABB(lower*1.001, upper*1.001);
}


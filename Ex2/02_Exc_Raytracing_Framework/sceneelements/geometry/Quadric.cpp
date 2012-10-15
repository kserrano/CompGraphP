/****************************************************************************
|*  Quadric.cpp
|*
|*  Defines a quadric in space.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#include "Quadric.h"

#define PI 3.1415926

Quadric::Quadric(Material* material) : m_a(1,0), m_b(1,0), m_c(1,0) {
	m_center = Vector3();

	m_material = material;
	m_finite = false;
}

bool Quadric::intersect(const Ray &ray, IntersectionData* iData) {
  //=== EXERCISE 1.3.5 ===
	return false;
}


// setter & getter
void Quadric::setCenter(Vector3 center) {
	m_center = center;
}
Vector3 Quadric::getCenter(void) {
	return m_center;
}


void Quadric::setA(ComplexNumber a) {
	m_a = a;
}

ComplexNumber Quadric::getA(void) {
	return m_a;
}

void Quadric::setB(ComplexNumber b) {
	m_b = b;
}

ComplexNumber Quadric::getB(void) {
	return m_b;
}

void Quadric::setC(ComplexNumber c) {
	m_c = c;
}

ComplexNumber Quadric::getC(void) {
	return m_c;
}



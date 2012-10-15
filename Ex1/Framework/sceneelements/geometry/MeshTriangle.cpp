/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#include "MeshTriangle.h"

#include <iostream> 

MeshTriangle::MeshTriangle() : parentMesh(0) { 
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;

	m_finite = true;
}

MeshTriangle::MeshTriangle(Mesh *pm, MeshVertex* v0, MeshVertex* v1, MeshVertex* v2) : parentMesh(pm) {
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
	
	m_finite = true;
}

MeshTriangle::~MeshTriangle(void) {
}

bool MeshTriangle::intersect(const Ray &ray, IntersectionData* iData) {
	return false;
}


MeshVertex* MeshTriangle::getVertex(int i) {
	return v[i];
}


Vector2 MeshTriangle::minNmax(double a, double b, double c) {
	double tmp[3];
	tmp[0] = a;
	tmp[1] = b;
	tmp[2] = c;
	
	double m;

	for (int j=0; j<2; j++) {
		for (int i=0; i<(2-j); i++) {
			if (tmp[i] > tmp[i+1]) {
				m = tmp[i+1];
				tmp[i+1] = tmp[i];
				tmp[i] = m;
			}
		}
	}
	return Vector2(tmp[0], tmp[2]);
}

AABB MeshTriangle::getBB() const {

	Vector3 m_p1 = *(v[0]->getPosition());
	Vector3 m_p2 = *(v[1]->getPosition());
	Vector3 m_p3 = *(v[2]->getPosition());

	//initialize corners of BB with p1
	Vector3 lower = m_p1, upper = m_p1;

	//check components of p2
	for (int i = 0; i < 3; i++) {
		if (lower[i] > m_p2[i])
			lower[i] = m_p2[i];

		if (upper[i] < m_p2[i])
			upper[i] = m_p2[i];
	}

	//check components of p3
	for (int i = 0; i < 3; i++) {
		if (lower[i] > m_p3[i])
			lower[i] = m_p3[i];

		if (upper[i] < m_p3[i])
			upper[i] = m_p3[i];
	}

	return AABB(lower, upper);
}
/****************************************************************************
|*  Triangle.cpp
|*
|*  Defines a triangle in space with normals defined at the points.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#include "Triangle.h"
#include <utils/Matrix4.h>


Triangle::Triangle(Material* material) {

	// creating a default triangle
	m_p1 = Vector3(1.0, 0.0, 0.0);
	m_p2 = Vector3(0.0, 1.0, 0.0);
	m_p3 = Vector3(1.0, 1.0, 0.0);

	m_n1 = Vector3(0.0, 0.0, 1.0);
	m_n2 = Vector3(0.0, 0.0, 1.0);
	m_n3 = Vector3(0.0, 0.0, 1.0);

	m_material = material;

	m_finite = true;
}


Triangle::~Triangle(void) {
}


void Triangle::setNormals(Vector3 n1, Vector3 n2, Vector3 n3) {
	m_n1 = n1.normalize();
	m_n2 = n2.normalize();
	m_n3 = n3.normalize();
}


//intersect triangle with a ray
bool Triangle::intersect(const Ray &ray, IntersectionData* iData) {


//=== EXERCISE 1.4.2 ===
	Vector3 n = (m_p3 - m_p1).cross(m_p2 - m_p1);
	if (ray.direction.dot(n) == 0)
	{
		// no solution
		return false;
	}else{
		// compute the solution
		double t = - ((ray.point - m_p1).dot(n))/(ray.direction.dot(n));

		// check if solution is valid for our problem
		bool b = (t>=ray.min_t && t<=ray.max_t) && t<iData->t;
		if(b){

			// normal vector of small triangles
			Vector3 x = ray.getPointOnRay(t);
			Vector3 n_s1 = (m_p2 - m_p3).cross(x - m_p3);
			Vector3 n_s2 = (m_p1 - m_p2).cross(x - m_p2);
			Vector3 n_s3 = (m_p3 - m_p1).cross(x - m_p1);

			// compute s1 s2 s3 (normalise)
			double s1 = (n.dot(n_s1))/(n.x*n.x + n.y*n.y + n.z*n.z);
			double s2 = (n.dot(n_s2))/(n.x*n.x + n.y*n.y + n.z*n.z);
			double s3 = (n.dot(n_s3))/(n.x*n.x + n.y*n.y + n.z*n.z);

			// test if p is in triangle
			if(1-ray.epsilon_t < s1+s2+s3 && s1+s2+s3 < 1+ray.epsilon_t && 0 < s1 && s1<1 && 0<s2 && s2<1 && 0<s3 && s3<1){
				iData->t=t;
		
			//Intersection information
			iData->position=ray.getPointOnRay(iData->t);
			iData->color=getColor();
			iData->sourcePosition=ray.point;
			iData->reflectionPercentage = getReflectionPercentage();


			// Exercice 2.1.1
			iData->material = getMaterial();
			//Normal interpolation
			Vector3 normal1 = m_n1.operator*(s1);
			Vector3 normal2 = m_n2.operator*(s3);
			Vector3 normal3 = m_n3.operator*(s2); // s2 and s3 are inverted du to the typing error on the triangle in slide

			Vector3 normal = (normal1+normal2+normal3).normalize(); // get the interpolated normal in x
			iData->normal = normal;
			return true;
			}else{
				return false;
			}
		}else{

		return false;
		}
	}
  return false;



}


Vector2 Triangle::minNmax(double a, double b, double c) {
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



// setter & getter

void Triangle::setPoint1(Vector3 point1) {
	m_p1 = point1;

}
Vector3 Triangle::getPoint1(void) const {
	return m_p1;
}

void Triangle::setPoint2(Vector3 point2) {
	m_p2 = point2;

}
Vector3 Triangle::getPoint2(void) const {
	return m_p2;
}

void Triangle::setPoint3(Vector3 point3) {
	m_p3 = point3;

}
Vector3 Triangle::getPoint3(void) const {
	return m_p3;
}


void Triangle::setNormal1(Vector3 normal1) {
	m_n1 = normal1.normalize();
}
Vector3 Triangle::getNormal1(void) const {
	return m_n1;
}

void Triangle::setNormal2(Vector3 normal2) {
	m_n2 = normal2.normalize();
}
Vector3 Triangle::getNormal2(void) const {
	return m_n2;
}
void Triangle::setNormal3(Vector3 normal3) {
	m_n3 = normal3.normalize();
}
Vector3 Triangle::getNormal3(void) const {
	return m_n3;
}

AABB Triangle::getBB() const {
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
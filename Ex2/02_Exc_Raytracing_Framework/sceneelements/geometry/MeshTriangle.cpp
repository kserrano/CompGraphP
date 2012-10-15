/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#include "MeshTriangle.h"

#include <iostream> 
#include "../utils/Matrix4.h"

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

	/*
  Vector3 vd = ray.direction;
  Vector3 p = ray.point;

  Vector3 m_p1=*((v[0])->getPosition());
  Vector3 m_p2=*((v[1])->getPosition());
  Vector3 m_p3=*((v[2])->getPosition());

  Vector3 m_n1=*((v[0])->getNormal());
  Vector3 m_n2=*((v[1])->getNormal());
  Vector3 m_n3=*((v[2])->getNormal());


  //calc normal of triangle (vertex normals can be different in general)
  //and check whether the ray is parallel to the triangle
  Vector3 vT1 = m_p2 - m_p1;
  Vector3 vT2 = m_p3 - m_p1;
  Vector3 nT = vT1.cross(vT2);
  if (nT.dot(vd) == 0)
    return false;

  //solve linear equation system [A * param = b] for param = (t s2 s3)^T
  //(s2 and s3 are barycentric coordinates of the triangle)
  Matrix4 A(vd, -vT1, -vT2);
  Vector3 b = m_p1 - p;
  Vector3 param = A.Inverse() * b;

  //check if intersection point lies inside the triangle (0 <= s2,s3,s2+s3 <= 1)
  if (param[1] < 0 || param[2] < 0 || param[1]+param[2] < 0 ||
    param[1] > 1 || param[2] > 1 || param[1]+param[2] > 1)
    return false;

  //calculate ray parameter t and check whether the intersection is within the scope of the ray
  double intersection_t = param[0];
  if (intersection_t < ray.min_t || intersection_t > ray.max_t)
    return false;


  // check if intersection is nearer than the current nearest (stored in iData)
  if (intersection_t < iData->t) {
    // clear current iData
    iData->clear();

    //get other intersection info
    Vector3 intersection_p = ray.getPointOnRay(intersection_t);
    Vector4 intersection_c = m_color;


    //caculate normal at intersection_p
    Vector3 intersection_n = m_n1*(1-param[1]-param[2]) + m_n2*param[1] + m_n3*param[2];
    intersection_n.normalize();

    //calculate texture coordinates
    Vector2 texCoords = Vector2(1.0, 0.0)*(1-param[1]-param[2]) + Vector2(0.0, 0.0)*param[1] + Vector2(0.0, 1.0)*param[2];

    // set parameters 
    iData->position = intersection_p;
    iData->color = intersection_c;
    iData->t = intersection_t;
    iData->sourcePosition = ray.point;	

    iData->material = m_material;
    iData->texture = m_texture;
    iData->textureCoords = texCoords;

    iData->normal = intersection_n;

    iData->reflectionPercentage = m_reflectionPercentage;
    iData->refractionIndex = m_refractionIndex;
    iData->refractionPercentage = m_refractionPercentage;

    // compute if the ray enters the object
    if (iData->normal.dot(vd) < 0)
      iData->rayEntersObject = true;
    else
      iData->rayEntersObject = false;

    return true;
  } else {
    return false;
  }
  */
  

  // Solution from Moeller and Trumbore: Fast, minimum storage ray-triangle intersection 
  // http://www.graphics.cornell.edu/pubs/1997/MT97.html 


  Vector3 m_p1=*((v[0])->getPosition());
  Vector3 m_p2=*((v[1])->getPosition());
  Vector3 m_p3=*((v[2])->getPosition());

  Vector3 m_n1=*((v[0])->getNormal());
  Vector3 m_n2=*((v[1])->getNormal());
  Vector3 m_n3=*((v[2])->getNormal());

  double EPSILON = 10e-10;
  double u,w;
  Vector3 qvec;


  // find vectors for two edges sharing vert0
  Vector3 e1 = m_p2-m_p1;
  Vector3 e2 = m_p3-m_p1;

  // begin calculating determinant - also used to calculate U parameter 
  Vector3 pvec = ray.direction.cross(e2);

  // if determinant is near zero, ray lies in plane of triangle
  double det = e1.dot(pvec);

  if (det > EPSILON)
  {
    // calculate distance from vert0 to ray origin
    Vector3 tvec=ray.point-m_p1;

    // calculate U parameter and test bounds
    u = tvec.dot(pvec);
    if (u < 0.0 || u > det)
      return false;

    // prepare to testV parameter
    qvec=tvec.cross(e1);

    // calculate V parameter and test bounds
    w = ray.direction.dot(qvec);
    if (w < 0.0 || u + w > det)
      return false;

  }
  else if(det < -EPSILON)
  {
    // calculate distance from vert0 to ray origin 
    Vector3 tvec= ray.point-m_p1;

    // calculate U parameter and test bounds 
    u = tvec.dot(pvec);
    if( u > 0.0 || u < det )
      return false;

    // prepare to test V parameter 
    qvec = tvec.cross(e1);

    // calculate V parameter and test bounds 
    w = ray.direction.dot(qvec);
    if (w > 0.0 || u + w < det )
      return false;

  }
  else return false;  // ray is parallel to the plane of the triangle 


  double inv_det = 1.0f / det;

  // calculate t, ray intersects triangle 
  double t =e2.dot(qvec) * inv_det;
  u *= inv_det;
  w *= inv_det;

  if ( (t>=ray.min_t && t<=ray.max_t) && t<iData->t )
  {
    iData->color=getColor();
    iData->t=t;
    iData->material=getMaterial();
    iData->sourcePosition=ray.point;
    iData->normal=(m_n1*(1.0-u-w) + m_n2*u + m_n3*w).normalize();
    iData->position=ray.getPointOnRay(iData->t);

    iData->reflectionPercentage=getReflectionPercentage();
    iData->refractionIndex=getRefractionIndex();
    iData->refractionPercentage=getRefractionPercentage();
    iData->rayEntersObject= (ray.direction.dot(iData->normal)<0.0);

    return true;
  }

  return false;


}


bool MeshTriangle::fastIntersect(const Ray &ray) { 

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
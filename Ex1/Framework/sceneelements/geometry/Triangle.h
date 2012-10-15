/****************************************************************************
|*  Triangle.h
|*
|*  Declaration of the class Triangle.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#ifndef _TRIANGLE_H
#define _TRIANGLE_H


#include <sceneelements/IElement.h>
#include <utils/Material.h>
#include <utils/Vector3.h>
#include <utils/Vector2.h>


class Triangle : public IElement {

public:

	Triangle(Material* material);

	~Triangle(void);

	void setNormals(Vector3 _n1, Vector3 _n2, Vector3 _n3);


	void setPoint1(Vector3 point1);
	Vector3 getPoint1(void) const;

	void setPoint2(Vector3 point2);
	Vector3 getPoint2(void) const;

	void setPoint3(Vector3 point3);
	Vector3 getPoint3(void) const;

	Vector3 getCentroid() const { return (m_p1 + m_p2 + m_p3) / 3; };

	void setNormal1(Vector3 normal1);
	Vector3 getNormal1(void) const;

	void setNormal2(Vector3 normal2);
	Vector3 getNormal2(void) const;

	void setNormal3(Vector3 normal3);
	Vector3 getNormal3(void) const;

	//intersect triangle with a ray
	virtual bool intersect(const Ray &ray, IntersectionData* iData);

	AABB getBB() const;
private:

	Vector3 m_p1;
	Vector3 m_p2;
	Vector3 m_p3;

	Vector3 m_n1;
	Vector3 m_n2;
	Vector3 m_n3;


private:
	// returns the minimum and maximum of the three parameters
	// Vector2.x = min.  Vector2.y = max.
	Vector2 minNmax(double a, double b, double c);

};


#endif //_TRIANGLE_H

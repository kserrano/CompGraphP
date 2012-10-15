/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/



#ifndef _TORUS_H
#define _TORUS_H


#include <sceneelements/IElement.h>
#include <utils/Material.h>
#include <utils/Vector3.h>


class Torus : public IElement {

public:
	Torus(Material* material);

	//intersect torus with a ray
	virtual bool intersect(const Ray &ray, IntersectionData* iData);

	// setter & getter
	void setCenter(Vector3 center);
	Vector3 getCenter(void);

	void setR(double R);
	double getR(void);

	void setr(double r);
	double getr(void);

  AABB Torus::getBB() const;

private:

	Vector3 m_center;
	double m_R, m_r;

private:

};

#endif
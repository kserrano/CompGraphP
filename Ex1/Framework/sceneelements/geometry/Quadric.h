/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#ifndef _QUADRIC_H
#define _QUADRIC_H


#include <sceneelements/IElement.h>
#include <utils/Material.h>
#include <utils/Vector3.h>
#include <utils/ComplexNumber.h>


class Quadric : public IElement {

public:
	Quadric(Material* material);

	//intersect quadric with a ray
	virtual bool intersect(const Ray &ray, IntersectionData* iData);


	// setter & getter
	void setCenter(Vector3 center);
	Vector3 getCenter(void);

	void setA(ComplexNumber a);
	ComplexNumber getA(void);

	void setB(ComplexNumber b);
	ComplexNumber getB(void);

	void setC(ComplexNumber c);
	ComplexNumber getC(void);

private:

	Vector3 m_center;
	ComplexNumber m_a, m_b, m_c;

};

#endif
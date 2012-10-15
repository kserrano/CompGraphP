/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#ifndef _AABB_H
#define _AABB_H

#include <utils/Vector3.h>

struct AABB {
	AABB() {};
	AABB(Vector3 l, Vector3 u) { lowerCorner=l; upperCorner=u; };

	//info about axis aligned bounding box
	Vector3 lowerCorner;
	Vector3 upperCorner;
};

#endif

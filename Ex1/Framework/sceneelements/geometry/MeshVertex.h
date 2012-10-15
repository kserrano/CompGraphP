/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, B�lint Mikl�s, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#ifndef _MESH_VERTEX_H
#define _MESH_VERTEX_H

#include <utils/Vector3.h>
#include <utils/Vector2.h>

class MeshVertex {
public:
	MeshVertex();

	MeshVertex(const Vector3 &pos);

	~MeshVertex();

	void setNormal(Vector3 *normal);
	Vector3* getNormal();

	void setTexture(Vector2 *texture);
	Vector2* getTexture();

	Vector3* getPosition();

	unsigned int getIndex()
	{
		return index;
	}

	void setIndex(unsigned int i)
	{
		index = i;
	}

	void setPosition(Vector3 &point);

private:

	Vector3 position;
	Vector3* normal;
	Vector2* texture;
	unsigned int index;
};

#endif
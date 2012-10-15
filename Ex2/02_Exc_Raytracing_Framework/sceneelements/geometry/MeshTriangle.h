/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#ifndef _MESH_TRIANGLE_H
#define _MESH_TRIANGLE_H

#include <sceneelements/geometry/Mesh.h>
#include <sceneelements/geometry/MeshVertex.h>
#include <sceneelements/IElement.h>
#include <utils/AABB.h>

class MeshTriangle : public IElement {

public:
	MeshTriangle();
	MeshTriangle(Mesh *pm, MeshVertex* v0, MeshVertex* v1, MeshVertex* v2);

	~MeshTriangle(void);

	virtual bool intersect(const Ray &ray, IntersectionData* iData);
	virtual bool fastIntersect(const Ray &ray);

	MeshVertex* getVertex(int i);
	Vector3 getCentroid() const { return (
		*(v[0]->getPosition()) + 
		*(v[1]->getPosition()) + 
		*(v[2]->getPosition())
		) / 3; };
	AABB getBB() const; 

private:

	MeshVertex* v[3];
	Mesh* parentMesh;

private:

	// returns the minimum and maximum of the three parameters
	// Vector2.x = min.  Vector2.y = max.
	Vector2 minNmax(double a, double b, double c);


};

#endif
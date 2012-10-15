/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, B�lint Mikl�s, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#include <utils/Material.h>
#include <utils/Vector3.h>

#include "Mesh.h"
#include <sceneelements/geometry/MeshTriangle.h>
#include <sceneelements/geometry/MeshVertex.h>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>


Mesh::Mesh(int n_vertices, int n_triangles) {
	vertices.clear(); vertices.resize(n_vertices);
	triangles.clear(); triangles.resize(n_triangles);
}

Mesh::~Mesh(void) {
	for (unsigned int i=0; i < vertices.size(); i++) 
		delete vertices[i];
	vertices.clear();
	// triangles are added directly to the scene as well, so they will be deleted there
	triangles.clear();
}


MeshVertex* Mesh::getVertex(int i) {
	return vertices[i];
}


void Mesh::addTriangle(MeshTriangle *m) {
	triangles.push_back(m);
}

void Mesh::addVertex(MeshVertex *v) {
	v->setIndex(static_cast<unsigned int>(vertices.size()));
	vertices.push_back(v);
}


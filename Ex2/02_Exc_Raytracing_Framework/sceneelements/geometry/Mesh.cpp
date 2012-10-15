/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#include <utils/Material.h>
#include <utils/Vector3.h>

#include "Mesh.h"
#include <sceneelements/geometry/MeshTriangle.h>
#include <sceneelements/geometry/MeshVertex.h>

#include "../Scene.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>


Mesh::Mesh(Scene* _scene, int n_vertices, int n_triangles) {
  scene=_scene;
	vertices.clear(); vertices.resize(n_vertices);
	triangles.clear(); triangles.resize(n_triangles);
}

Mesh::~Mesh() {
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
  scene->addElement(m);
}

void Mesh::addVertex(MeshVertex *v) {
	v->setIndex(static_cast<unsigned int>(vertices.size()));
	vertices.push_back(v);
}


bool Mesh::setVertexPositions( std::vector<Vector3> positions )
{
  std::vector<Vector3>::iterator it = positions.begin();
  for(it;it!=positions.end();++it)
  {
    MeshVertex* m= new MeshVertex(*it);
    addVertex( m );
  }
  return true;
}

bool Mesh::setVertexNormals( std::vector<Vector3> normals )
{
  if (numberOfVertices() != normals.size() )
  {
    return false;
  }

  for( unsigned int i=0; i<numberOfVertices();++i)
  {
    Vector3* n= new Vector3((normals[i]).x,(normals[i]).y,(normals[i]).z);
    (*n)=(*n).normalize();
    (getVertex(i))->setNormal(n);
  }

  return true;
}

bool Mesh::setVertexTextureCoordinates( std::vector<Vector2> textureCoordinates )
{
  if (numberOfVertices() != textureCoordinates.size() )
  {
    return false;
  }

  for( unsigned int i=0; i<numberOfVertices();++i)
  {
    Vector2* uv = new Vector2(textureCoordinates[i][0],textureCoordinates[i][1]);
    (getVertex(i))->setTexture(uv);
  }

  return true;
}




bool Mesh::setTriangles( std::vector<unsigned int> triangles )
{
  unsigned int n= numberOfVertices();

  for( unsigned int i=0; i<(triangles.size()/3.0);i++)
  {

    MeshVertex* v0=getVertex(triangles[i*3]);
    MeshVertex* v1=getVertex(triangles[i*3 + 1]);
    MeshVertex* v2=getVertex(triangles[i*3 + 2]);

    MeshTriangle* t= new MeshTriangle(this,v0,v1,v2);
    addTriangle(t);
  }

  return true;
}
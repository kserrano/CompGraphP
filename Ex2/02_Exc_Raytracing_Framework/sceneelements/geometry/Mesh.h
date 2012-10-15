/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#ifndef _MESH_H
#define _MESH_H

#include <vector>
#include <utils/Vector2.h>
#include <utils/Vector3.h>
#include <utils/Vector4.h>
#include <utils/Material.h>

class Scene;
class MeshVertex;
class MeshTriangle;

class Mesh {

public:
	Mesh(Scene* _scene, int n_vertices, int n_triangles);
	~Mesh(void);

	void addTriangle(MeshTriangle *m);
	void addVertex(MeshVertex *v);

	unsigned int numberOfVertices()
	{
		return (unsigned int)vertices.size();
	}

	unsigned int numberOfFaces()
	{
		return (unsigned int)triangles.size();
	}

	MeshVertex *getVertex(int i);

	MeshTriangle * getFace(int i)
	{
		return triangles[i];
	}

  bool setVertexPositions(std::vector<Vector3> positions );
  bool setVertexNormals(std::vector<Vector3> normals );
  bool setVertexTextureCoordinates(std::vector<Vector2> textureCoordinates );
  bool setVertexUV(std::vector<Vector2> uvs){return setVertexTextureCoordinates(uvs);};

  //The fist 3 integers in triangles are the indices to the vertices of the first triangle, and so.
  bool setTriangles( std::vector<unsigned int> triangles );

	void setTexture(Vector2 *texture) { 
	this->texture = texture; 
}

private:
	Mesh(void) {};
	std::vector<MeshTriangle*> triangles;
	std::vector<MeshVertex*> vertices;
	Vector2* texture;
  Scene* scene;
};

#endif
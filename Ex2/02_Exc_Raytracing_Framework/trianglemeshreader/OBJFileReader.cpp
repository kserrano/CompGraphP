/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#include "OBJFileReader.h"
#include "../sceneelements/geometry/Mesh.h"
#include "../sceneelements/geometry/MeshVertex.h"
#include "../sceneelements/geometry/MeshTriangle.h"
#include "../Scene.h"

#include <../utils/Vector2.h>
#include <../utils/Vector3.h>
#include <../utils/Vector4.h>
#include <../utils/Material.h>


#include <../utils/Image.h>

#include <limits>

void readOBJFile(const std::string &filename, Mesh * _mesh, Scene * _scene, bool & _readVertexNormals,bool & _readTexture) {
	std::vector<Vector3 * > vertexNormalList;
	std::vector<Vector2 * > vertexTextureList;
	vertexNormalList.clear();
	vertexTextureList.clear();
  // Load the mesh.  This routine supports a simplified version of the
  // .obj file format.  Lines begin with either '#' to indicate a comment,
  // 'v' to indicate a vertex, or 'f' to indicat a face.  Comments are
  // ignored.  ** Vertex indices (in 'f' lines) are one based, so they 
  // start with one and not zero. **  Faces can only have three indices --
  // so they must be triangles.  Any other tag in the file is ignored.

  printf("Loading mesh \"%s\".\n", filename.c_str());

  // Load a simplified version of the .obj file format.

  // Open the file.
  FILE *stream = fopen(filename.c_str(), "r");
  
  if (stream == NULL) {
    printf("Error opening file \"%s\" for reading.\n", filename.c_str());
    exit(-1);
  }

  // Read the contents.

  bool unknownWarning = false;
  char str[256];
  double x, y, z;
	double tx,ty;
  int i0, i1, i2;
	int it0, it1, it2;
	int in0, in1, in2;
  int v;
	printf("starting\n");
  while (fscanf(stream, "%s", str) == 1) {

    if (str[0] == '#') {

      // Comment
      // Read until the next newline.
      
      while (1) {
        char c;
        v = fscanf(stream, "%c", &c);
        if ((c == '\n') || (v != 1))
          break;
      }

    } else if (strcmp(str, "vn") == 0) {
		/*
      v = fscanf(stream, "%lf", &nx);
      v = fscanf(stream, "%lf", &ny);
      v = fscanf(stream, "%lf", &nz);
			Vector3 * newNormal = new Vector3(nx, ny, nz);
			vertexNormalList.push_back(newNormal);
		*/
    } else if (strcmp(str, "vt") == 0) {
      
      v = fscanf(stream, "%lf", &tx);
      v = fscanf(stream, "%lf", &ty);
			Vector2 * newTexture = new Vector2(tx, ty);
			vertexTextureList.push_back(newTexture);

    }else if (strcmp(str, "v") == 0) {
      
      // Vertex
      // Read three doubles and add the vertex.

      v = fscanf(stream, "%lf", &x);
      v = fscanf(stream, "%lf", &y);
      v = fscanf(stream, "%lf", &z);
			MeshVertex *mv = new MeshVertex(Vector3(x, y, z));
      _mesh->addVertex(mv);
			//printf("x:%f,y:%f,z:%f\n",x,y,z);
    } else if (strcmp(str, "f") == 0) {
      
      // Face 
      // Read three vertex indices and add the triangle.

			char c;

      v = fscanf(stream, "%d", &i0);
				v = fscanf(stream, "%c", &c);
				v = fscanf(stream, "%d", &it0); 
				v = fscanf(stream, "%c", &c);
				v = fscanf(stream, "%d", &in0); 
      v = fscanf(stream, "%d", &i1);
				v = fscanf(stream, "%c", &c);
				v = fscanf(stream, "%d", &it1); 
				v = fscanf(stream, "%c", &c);
				v = fscanf(stream, "%d", &in1); 
      v = fscanf(stream, "%d", &i2);
				v = fscanf(stream, "%c", &c);
				v = fscanf(stream, "%d", &it2); 
				v = fscanf(stream, "%c", &c);
				v = fscanf(stream, "%d", &in2); 

      // Since the .obj file format is one-based, the indices start
      // at one rather than at zero.  So, we must subtract one from
      // each index.
      i0--; i1--; i2--;
      
      //_triangles.push_back(Tri(i0, i1, i2));
			
       MeshTriangle *mt = new MeshTriangle(_mesh,	_mesh->getVertex(i0),
																									_mesh->getVertex(i1),
																									_mesh->getVertex(i2));

			 _mesh->addTriangle(mt);
			 _scene->addElement(mt);
			 
			 //printf("i0:%d,i1:%d,i2:%d\n",i0,i1,i2);

    } else {
      
      if (!unknownWarning) {
        printf("Unknown token \"%s\" encountered.  (Additional warnings surpressed.)\n", str);
        unknownWarning = true;
      }

      // Read until the next newline.
      while (1) {
        char c;
        v = fscanf(stream, "%c", &c);
        if ((c == '\n') || (v != 1))
          break;
      }
    }
    
    if (v != 1) {
      printf("Error: Premature end of file while reading \"%s\".", filename.c_str());
      exit(-1);
    }
  }
  
  fclose(stream);

  //printf("File loaded with %d vertices and %d triangles.\n", NumVertices(), NumTriangles());
	// add vertex normals

	/*
	for(unsigned int i=0;i<vertexNormalList.size();i++)
	{
		if(i<_mesh->numberOfVertices())
		{
		_readVertexNormals = true;
		_mesh->getVertex(i)->setNormal(vertexNormalList[i]);
		}
		else
		{
			 printf("warning more vertex normals than vertices\n");
		}
	}
	*/
	printf("done\n");
	for(unsigned int i=0;i<vertexTextureList.size();i++)
	{
		if(i<_mesh->numberOfVertices())
		{
			_readTexture = true;
			_mesh->getVertex(i)->setTexture(vertexTextureList[i]);
		}
		else
		{
			 //printf("warning more texture coordinates than vertices\n");
		}
	}
	
}

void preprocessing(Mesh * _mesh,double _newRadius,Vector3 & _translate)
{
	// compute bounding box
		Vector3 minPosition;
		Vector3 maxPosition;
		Vector3 centerPosition;
		double radius=0.0;
		maxPosition[0]=std::numeric_limits<double>::min();
		maxPosition[1]=std::numeric_limits<double>::min();
		maxPosition[2]=std::numeric_limits<double>::min();

		minPosition[0]=std::numeric_limits<double>::max();
		minPosition[1]=std::numeric_limits<double>::max();
		minPosition[2]=std::numeric_limits<double>::max();

		for(unsigned int i=0;i<_mesh->numberOfVertices();i++)
		{
			Vector3 point = *_mesh->getVertex(i)->getPosition();
			if(point[0] < minPosition[0])
			{
				minPosition[0] = point[0];
			}
			if(point[1] <minPosition[1])
			{
				minPosition[1] = point[1];
			}
			if(point[2] <minPosition[2])
			{
				minPosition[2] = point[2];
			}

			if(point[0] >maxPosition[0])
			{
				maxPosition[0] = point[0];
			}
			if(point[1] >maxPosition[1])
			{
				maxPosition[1] = point[1];
			}
			if(point[2] >maxPosition[2])
			{
				maxPosition[2] = point[2];
			}

		}
// compute center position
		centerPosition[0] = (maxPosition[0] + minPosition[0])/2.0;
		centerPosition[1] = (maxPosition[1] + minPosition[1])/2.0;
		centerPosition[2] = (maxPosition[2] + minPosition[2])/2.0;

		// compute radius
		radius =	(maxPosition[0]-centerPosition[0])*(maxPosition[0]-centerPosition[0]) +
							(maxPosition[1]-centerPosition[1])*(maxPosition[1]-centerPosition[1])	+
							(maxPosition[2]-centerPosition[2])*(maxPosition[2]-centerPosition[2]);

	// normalize size and translate to origin
		
		for (unsigned int i=0; i < _mesh->numberOfVertices(); i++) {
			 Vector3 coord = *_mesh->getVertex(i)->getPosition();
			 coord[0] = (((coord[0]-centerPosition[0])/radius)*_newRadius)+_translate[0];
			 coord[1] = (((coord[1]-centerPosition[1])/radius)*_newRadius)+_translate[1];
			 coord[2] = (((coord[2]-centerPosition[2])/radius)*_newRadius)+_translate[2];

			 _mesh->getVertex(i)->setPosition(coord);
		}
		
}

void calcVertexNormals(Mesh * _mesh)
{
	// Calculate per-vertex normals.
  
	std::vector<Vector3> vertexNormalList;
	vertexNormalList.clear();
	vertexNormalList.resize(_mesh->numberOfVertices());
  // Iterate over all triangles.
	
  for (unsigned int i = 0; i < _mesh->numberOfFaces(); i++) {

    MeshTriangle * triangle = _mesh->getFace(i);

    // For each triangle, calculate it's face normal.

		Vector3 point1 = *(triangle->getVertex(0)->getPosition());
		Vector3 point2 = *(triangle->getVertex(1)->getPosition());
		Vector3 point3 = *(triangle->getVertex(2)->getPosition());

    Vector3 vec1 = point2 - point1;
    Vector3 vec2 = point3 - point1;
		Vector3 faceNormal = vec1.cross(vec2);
		//printf("%f, %f, %f\n",vec1[0],vec1[1],vec1[2]);
    // Add this face normal to the normal vector for each of the
    // triangle's three indices.
		
		vertexNormalList[triangle->getVertex(0)->getIndex()] += faceNormal;
		vertexNormalList[triangle->getVertex(1)->getIndex()] += faceNormal;
		vertexNormalList[triangle->getVertex(2)->getIndex()] += faceNormal;
	
  }

  // Finally, normalize all of the normals.
  for (unsigned int i = 0; i < _mesh->numberOfVertices(); i++)
	{
		vertexNormalList[i].normalize();
		//printf("%f, %f, %f\n",vertexNormalList[i][0],vertexNormalList[i][1],vertexNormalList[i][2]);
		Vector3* normal = new Vector3(vertexNormalList[i][0],vertexNormalList[i][1],vertexNormalList[i][2]);
		_mesh->getVertex(i)->setNormal(normal);
	}	
}
/****************************************************************************
|*  Raytracer Framework
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/



#ifndef _OBJ_FILE_READER_H
#define _OBJ_FILE_READER_H

class Mesh;
class Scene;
class Vector3;
# include <string>

void readOBJFile(const std::string &filename, Mesh * _mesh, Scene * _scene,bool & _readVertexNormals, bool & _readTexture);

void preprocessing(Mesh * _mesh,double _newRadius,Vector3 & _translate);

void calcVertexNormals(Mesh * _mesh);

#endif

/****************************************************************************
|*  IntersectionData.h
|*
|*  Intersection Data represents the information about the intersection 
|*  point of a Ray and an IElement.
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#ifndef _INTERSECTIONDATA_H
#define _INTERSECTIONDATA_H

#include <utils/Vector2.h>
#include <utils/Vector3.h>
#include <utils/Vector4.h>
#include <utils/Material.h>
#include <utils/textures/ITexture.h>


class IntersectionData {

public:
	IntersectionData();
	~IntersectionData();

	IntersectionData(const IntersectionData &iD);

	void operator=(const IntersectionData &iD);

	void clear(void);

public: //DATA FIELDS

	Vector3 position;     // collision position
	double t;               // parameter t of the ray-element intersection
	Vector3 normal;

	// surface
	Vector4 color; 
	Material* material;

	// texturing
	ITexture* texture;
	Vector2 textureCoords;

	// bumpmapping
	ITexture* bumpmap;
	Vector3 localX;
	Vector3 localY;
	Vector3 localZ;
	
	// reflection
	double reflectionPercentage;  
	
	// refraction
	double refractionIndex;
	double refractionPercentage;
	bool rayEntersObject;
	
	// startpoint of the ray that hit
	Vector3 sourcePosition;	
};


#endif //_INTERSECTIONDATA_H

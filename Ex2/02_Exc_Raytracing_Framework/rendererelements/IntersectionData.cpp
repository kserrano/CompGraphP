/****************************************************************************
|*  IntersectionData.cpp
|*
|*  Intersection Data represents the information about the intersection 
|*  point of a Ray and an IElement.
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#include "IntersectionData.h"


IntersectionData::IntersectionData() {
	clear();
}


IntersectionData::~IntersectionData() {
}

IntersectionData::IntersectionData(const IntersectionData &iD) {
	position = iD.position;
	normal = iD.normal;
	sourcePosition = iD.sourcePosition;

	// material
	color = iD.color;
	*(material) = *(iD.material);

	reflectionPercentage = iD.reflectionPercentage;
	refractionIndex = iD.refractionIndex;
	refractionPercentage = iD.refractionPercentage;
	rayEntersObject = iD.rayEntersObject;

	t = iD.t;

	texture = iD.texture;
	bumpmap = iD.bumpmap;
}

void IntersectionData::operator=(const IntersectionData &iD) {
	position = iD.position;
	normal = iD.normal;
	sourcePosition = iD.sourcePosition;

	color = iD.color;
	*(material) = *(iD.material);

	reflectionPercentage = iD.reflectionPercentage;
	refractionIndex = iD.refractionIndex;
	refractionPercentage = iD.refractionPercentage;
	rayEntersObject = iD.rayEntersObject;

	t = iD.t;

	texture = iD.texture;
}


void IntersectionData::clear(void) {
	//set defaults
	position = Vector3();     // collision position
	t = 3.4e38;               // parameter t of the ray-element intersection
	normal = Vector3(0,0,1);

	// surface
	color = Vector4(1,1,1,1); 
	material = 0;

	// texturing
	texture = 0;
	textureCoords = Vector2(0,0);

	// bumpmapping
	bumpmap = 0;
	localX = Vector3(1,0,0);
	localY = Vector3(0,1,0);
	localZ = Vector3(0,0,1);
	
	// reflection
	reflectionPercentage = 0.0;  
	
	// refraction
	refractionIndex = 1.0;
	refractionPercentage = 0.0;
	rayEntersObject = true;
	
	// startpoint of the ray that hit
	sourcePosition = Vector3(0,0,0);	
}
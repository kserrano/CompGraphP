/****************************************************************************
|*  Scene.h
|*
|*  Declaration of a Scene object.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

// define USE_KD_TREE 1

#ifndef _SCENE_H
#define _SCENE_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

#include <sceneelements/SimpleCamera.h>
#include <sceneelements/IElement.h>
#include <sceneelements/ILight.h>
#include <sceneelements/geometry/Mesh.h>
#include <rendererelements/IntersectionData.h>

#ifdef USE_KD_TREE
	#include <utils/KDTreeNode.h>
#endif

class Scene {

public:

	Scene(void);

	~Scene(void);


	void setCamera(ICamera* camera);
	ICamera* getCamera(void);
	
	void addElement(IElement* element);

	void addLight(ILight* light);


	//intersect scene with a ray
	IntersectionData* intersect(const Ray &ray) const;

	//test whether the ray will intersect any element in the scene (faster than intersect)
	bool fastIntersect(const Ray &ray) const;

	std::vector<ILight*> getLights(void) const;

	//get the list of lights that are visible at the specified point
	std::vector<ILight*> getNonOccludedLights(const Vector3 &point) const;

	//write sample to the cameras image buffer
	void setSample(const Sample sample);

	// more parameter
	void setBackground(Vector4 bgcolor);
	Vector4 getBackground(void) const;
	void setAmbient(Vector4 ambient);
	Vector4 getAmbient(void) const;
	void setRefractionIndex(double index);
	double getRefractionIndex() const;


	// global lists
	void addMaterial(std::string name, Material* material);
	Material* getMaterial(std::string name);
	Material* getDefaultMaterial();

	void addTexture(std::string name, ITexture* texture);
	ITexture* getTexture(std::string name);

	void addMesh(Mesh* mesh);

	// kd tree
	int buildKDTree();
	bool useKDTree() const { return m_useKDTree; };

	unsigned long numOfIntersectionTests() const { 
		return m_numOfIntersectionTests; 
	};
	

protected:


private:

	ICamera* m_camera;
	
	std::vector<ILight*> m_lightList;
	std::list<IElement*> m_elementList;
	std::vector<Mesh*> m_meshList;

	std::map<std::string, Material*> m_materialList;
	std::map<std::string, ITexture*> m_textureList;

	Vector4 m_backgroundColor;
	Vector4 m_ambient;
	double m_refractionIndex;

	// kd tree
	bool m_useKDTree;
	static unsigned long m_numOfIntersectionTests;

};

#endif //_SCENE_H

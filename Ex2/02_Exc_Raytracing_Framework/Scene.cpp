/****************************************************************************
|*  Scene.cpp
|*
|*  Represents a scene. This class represents a data structure for
|*  a camera, lights and elements. It also computes collisions
|*  of a ray with all the objects.
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/

#include "Scene.h"

unsigned long Scene::m_numOfIntersectionTests = 0;

Scene::Scene(void) {
	m_camera = 0;
	m_backgroundColor = Vector4(0.0, 0.0, 0.0, 1.0);
	m_refractionIndex = 1;

#ifdef USE_KD_TREE
	useKDTree = true;
#else
	m_useKDTree = false;
#endif

	Material* default_material = new Material();
	this->addMaterial("default_material", default_material);
}

Scene::~Scene(void){
	unsigned int i;
	// delete elements
	std::list<IElement*>::iterator elementListIt;
	for (elementListIt = m_elementList.begin(); elementListIt != m_elementList.end(); elementListIt++) {
		delete(*elementListIt);
	}

	// delete lights
	for (i=0; i<m_lightList.size(); i++)
		delete(m_lightList[i]);
	m_lightList.clear();

	// delete meshes
	for (i=0; i<m_meshList.size(); i++) 
		delete(m_meshList[i]);
	m_meshList.clear();

	// delete materials
	std::map<std::string, Material*>::iterator it;
	for (it=m_materialList.begin(); it!=m_materialList.end(); it++)
		delete(it->second);
	m_materialList.clear();

	// delete textures
	std::map<std::string, ITexture*>::iterator it_t;
	for (it_t=m_textureList.begin(); it_t!=m_textureList.end(); it_t++)
		delete(it_t->second);
	m_textureList.clear();

	// delete camera aswell
	delete(m_camera);

}


void Scene::setCamera(ICamera*camera) {
	m_camera = camera;
}
ICamera* Scene::getCamera(void) {
	return m_camera;
}
	
void Scene::addElement(IElement* element) {
	m_elementList.push_back(element);
}

void Scene::addLight(ILight* light) {
	m_lightList.push_back(light);
}

//intersect scene with a ray
IntersectionData* Scene::intersect(const Ray &ray) const {

	IntersectionData* current = 0;

		bool intersected = false;
		
		IntersectionData* iData = new IntersectionData();
		// test intersection with objects
		if (m_elementList.size() > 0) {
			std::list<IElement*>::const_iterator element;
			for (element = m_elementList.begin(); element != m_elementList.end(); element++) {
				if ((*element)->intersect(ray,iData)) intersected = true;
			}
		}

		// see if iData is valid
		if (intersected) {
			return iData;
		} else {
			delete iData;
			iData = NULL;
			return 0;
		}

}

//test whether the ray will intersect any element in the scene (faster than intersect)
bool Scene::fastIntersect(const Ray &ray) const {
	bool intersection = false;

  IntersectionData* iData = new IntersectionData();
	if (m_elementList.size() > 0) {
		std::list<IElement*>::const_iterator element;
		for (element = m_elementList.begin(); element != m_elementList.end(); element++) {
			if ((*element)->intersect(ray,iData)) {
				// intersection found
				return true;
			}
		}
	}
  delete iData;
  iData = NULL;
	return false;

}

//get the list of lights that are visible at the specified point
std::vector<ILight*> Scene::getNonOccludedLights(const Vector3 &point) const{

  std::vector<ILight*> nonOccludedLights;
  std::vector<ILight*> Lights = getLights();
  //===EXERCISE 2.2.1 ===
	for (std::vector<ILight*>::const_iterator l = Lights.cbegin(); l != Lights.cend(); ++l) {
		if(!fastIntersect((*l)->generateRay(point))){
			nonOccludedLights.push_back(*l);
		}
	}
	return nonOccludedLights;
}

std::vector<ILight*> Scene::getLights(void) const{
	return m_lightList;
}


void Scene::setSample(const Sample sample) {
	m_camera->setSample(sample);
}


void Scene::setBackground(Vector4 bgcolor) {
	m_backgroundColor = bgcolor;
}
Vector4 Scene::getBackground(void) const {
	return m_backgroundColor;
}


void Scene::setAmbient(Vector4 ambient){
	m_ambient = ambient;
}

Vector4 Scene::getAmbient(void) const{
	return m_ambient;
}

void Scene::setRefractionIndex(double index) {
	m_refractionIndex = index;
}

double Scene::getRefractionIndex() const {
	return m_refractionIndex;
}


// global lists
///////////////////////////////////////////////////////////////////

// material list
void Scene::addMaterial(std::string name, Material* material) {
	m_materialList[name] = material;
}

Material* Scene::getMaterial(std::string name){
	return m_materialList[name];
}

Material* Scene::getDefaultMaterial(void){
	return m_materialList["default_material"];
}


// texture list

void Scene::addTexture(std::string name, ITexture* texture) {
	m_textureList[name] = texture;
}

ITexture* Scene::getTexture(std::string name) {
	return m_textureList[name];
}

void Scene::addMesh(Mesh* mesh) {
	m_meshList.push_back(mesh);
}

// kdtree

int Scene::buildKDTree() {
	return 0;
}
/****************************************************************************
|*  Renderer.cpp
|*
|*  Definition of a Simple renderer. The renderer takes a pointer to a
|*  scene and renders it. The resulting image is stored in the camera
|*	of the scene itself. 
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#include <Renderer.h>


Renderer::Renderer() {
  m_shader = 0;
  m_sampler = 0;
}


Renderer::~Renderer(void){
  if (m_shader) {
	  delete(m_shader);
  }
  if (m_sampler) {
	  delete(m_sampler);
  }
}


//main renderloop that raytraces the given scene
void Renderer::render(Scene* scene){
	if (scene) {
		// Initialize Sampler
		Point p = scene->getCamera()->getResolution();
		m_sampler->init(p.x, p.y);

		// Initialize fields
		Ray ray;
		std::vector<Ray> shadowRays;
		IntersectionData* iData = 0;
		Sample* sample = new Sample(0,0);

		//reset film in camera
		sample->setSize( (p.x > p.y? p.x : p.y) );
		scene->setSample(*sample);
		scene->getCamera()->initFilm();

		// Renderloop
		while (m_sampler->getNextSample(sample)) {
			// generate camera ray and intersect it with the scene
			ray = scene->getCamera()->generateRay(*sample);
		
			sample->setColor(traceColor(ray, scene,0));
		
			// write back the sample color
			scene->setSample(*sample);

			// observer update
		  if (m_sampler->cycleComplete())
			  notifyObservers();
		  }

		//cleanup
		delete sample;
	}
}


void Renderer::setShader(IShader* shader) {
	m_shader = shader;
} 


void Renderer::setSampler(ISampler* sampler) {
	m_sampler = sampler;
}


void Renderer::setRecursiondepth(unsigned int depth) {
	m_recursionDepth = depth;
}


double Renderer::status() {
  return m_sampler->percentageOfGeneratedSamples();
}


//trace the ray and find out the color at its intersection point with the scene
Vector4 Renderer::traceColor(Ray ray, Scene* scene, unsigned int recDepth) {
	Vector4 color;
	
	IntersectionData* iData = scene->intersect(ray);
	
	if (iData) { // sucessful intersection test

      //EXERCISE 2.2.3 & 2.2.4 ===

      color = m_shader->shade(iData, scene);

	} else {
		color = scene->getBackground(); // background color
	}


	// clean
	if (iData!=NULL){
		delete(iData);
	}

	return color.clamp01();
}

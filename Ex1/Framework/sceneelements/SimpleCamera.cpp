/****************************************************************************
|*  SimpleCamera.cpp
|*
|*  Definition of a SimpleCamera object. It provides the buffer to store an
|*	image. It also generates a ray for a given sample (see Sample.h).
|*
|*
|*  Thomas Oskam, Michael Eigensatz, Hao Li, Bálint Miklós, Raphael Hoever - Applied Geometry Group ETH Zurich, Computer Vision Laboratory
|*  oskamt@student.ethz.ch, eigensatz@inf.ethz.ch, hli@inf.ethz.ch, balint@inf.ethz.ch, hoever@vision.ee.ethz.ch
\***********************************************************/


#include "SimpleCamera.h"


SimpleCamera::SimpleCamera(const int res_x, const int res_y) {
	m_pos = Vector3(0.0,0.0,0.0);
	setOrientation(Vector3(0.0, 0.0, 1.0), Vector3(0.0, 1.0, 0.0));

	m_openingAngle = 30;
	m_resolutionX = res_x;
	m_resolutionY = res_y;
	
	m_film = new float[3 * res_x * res_y];
	initFilm();
}


SimpleCamera::SimpleCamera(Vector3 pos, Vector3 dir, Vector3 up,
	       float openingAngle, int res_x, int res_y) 
: 	m_pos(pos),
	m_openingAngle(openingAngle),
	m_resolutionX(res_x), 
	m_resolutionY(res_y)
{
	setOrientation(dir, up);
	m_film = new float[3 * res_x * res_y];
}


SimpleCamera::~SimpleCamera(void) {
	delete[] m_film;
}


Point SimpleCamera::getResolution(void) {
	return Point(m_resolutionX, m_resolutionY);
}


//generate ray out of a image sample
Ray SimpleCamera::generateRay(Sample sample) {

  //=== EXERCISE 1.3 ===
  //Replace this orthographic camera with a perspective one:

  //Fixed orthographic camera:
	//Note that the camera is pointing in x direction. Read scene description file for more details
  double pixel_length= tan((m_openingAngle*2*PI)/360)/(0.5*m_resolutionY);
  //Ray r;
  //r.point = Vector3(0.0,0.0,0.0);
  //r.point.x = -pixel_length*(sample.getPosX() - 0.5*(m_resolutionX-1.0));
  //r.point.y = pixel_length*(sample.getPosY() - 0.5*(m_resolutionY-1.0));
  //r.direction = Vector3(0.0,0.0,1.0);
  //return r;
	Ray r;
	r.point = m_pos;
	
	r.direction = Vector3(0.0,0.0,1.0);
	//Vector4 rotationMatrix = (cos(m_openingAngle),sin(m_openingAngle),-sin(m_openingAngle), cos(m_openingAngle));
	r.direction.x = pixel_length*(sample.getPosX() - 0.5*(m_resolutionX-1.0));
	r.direction.y = pixel_length*(sample.getPosY() - 0.5*(m_resolutionY-1.0));
	r.direction = m_camToWorld * r.direction;
	return r;
}


//write sample to image buffer
void SimpleCamera::setSample(Sample s) {
  int pos;

  for (unsigned long j = 0; j < s.getSize(); j++) {
		for (unsigned long i = 0; i < s.getSize(); i++) {
			if ( (s.getPosX()+i) < (unsigned long) m_resolutionX && (s.getPosY()+j) < (unsigned long) m_resolutionY) {
        pos = m_resolutionX*3 * (s.getPosY()+j) + (s.getPosX()+i) *3;
        m_film[pos+0] = (float) (m_film[pos+0] * s.getOldColorRenderWeight() +  s.getColor().x * s.getRenderWeight());
				m_film[pos+1] = (float) (m_film[pos+1] * s.getOldColorRenderWeight() +  s.getColor().y * s.getRenderWeight());
				m_film[pos+2] = (float) (m_film[pos+2] * s.getOldColorRenderWeight() +  s.getColor().z * s.getRenderWeight());
			}
		}
	}
}

//get image buffer
float * SimpleCamera::getFilm(void) {
	return m_film;
}

//get color on image pixel
Vector3 SimpleCamera::getPixelColor(int pos_x, int pos_y) {
	Vector3 color;
	color.x = m_film[m_resolutionX*3*pos_y + pos_x*3];
	color.y = m_film[m_resolutionX*3*pos_y + pos_x*3+1];
	color.z = m_film[m_resolutionX*3*pos_y + pos_x*3+2];

	return color;
}



// setter & getter
void SimpleCamera::setPosition(Vector3 position) {
	m_pos = position;
}

Vector3 SimpleCamera::getPosition(void){
	return m_pos;
}

void SimpleCamera::setOrientation(Vector3 direction, Vector3 up) {
	m_originalUp = up.normalize();
	m_dir = direction.normalize();
	m_right = (m_dir.cross(m_originalUp)).normalize();
	// compute up as the second base vector of the camera system
	m_up = (m_right.cross(m_dir)).normalize();

	m_camToWorld = Matrix4(m_right, m_up, m_dir);
}



void SimpleCamera::setOpeningAngle(float a) {
	m_openingAngle = a;
}


// clear image buffer
void SimpleCamera::initFilm(void) {
	for (int i=0; i<3*m_resolutionX * m_resolutionY; i++) m_film[i] = 0;
}


//=============================================================================
//                                                                            
//   Exercise code for Introduction to Computer Graphics
//   LGG - EPFL
//   Thibaut Weise, Yuliy Schwartzburg
//                                                                            
//=============================================================================
//=============================================================================
//
//   CLASS CubeViewer
//
//=============================================================================


#ifndef CUBE_VIEWER_HH
#define CUBE_VIEWER_HH


//== INCLUDES =================================================================

#include <string>
#include <vector>

#include "../../gl/TrackballViewer.h"
#include "../../gl/shader.h"
#include "../../gl/Mesh3D.h"

//== CLASS DEFINITION =========================================================




/*
 A simple OpenGL viewer for the first OpenGL assignment.
 */
class CubeViewer : public TrackballViewer
{
public:
    CubeViewer(const char* _title, int _width, int _height);
    ~CubeViewer();
    
protected:
    Mesh3D *createCube();
	
protected:
    
	// overloaded GUI function
    virtual void init();
    virtual void keyboard(int key, int x, int y);
    virtual void special(int key, int x, int y);
    
    virtual void draw_scene(DrawMode _draw_mode);
    
    
protected:
	
	Shader m_cubeShader;
	
	// meshes
    std::vector< Mesh3D* > m_meshes;
	
	void draw_mesh(Mesh3D *mesh);
};


//=============================================================================
#endif // CUBE_VIEWER_HH defined
//=============================================================================

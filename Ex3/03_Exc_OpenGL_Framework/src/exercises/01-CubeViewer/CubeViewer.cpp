//=============================================================================
//                                                                            
//   Exercise code for Introduction to Computer Graphics
//   LGG - EPFL
//   Thibaut Weise, Yuliy Schwartzburg
//                                                                            
//=============================================================================
//=============================================================================
//
//   CLASS CubeViewer - IMPLEMENTATION
//
//=============================================================================

//== INCLUDES =================================================================

#include "CubeViewer.h"

//== IMPLEMENTATION ===========================================================


CubeViewer::
CubeViewer(const char* _title, int _width, int _height)
: TrackballViewer(_title, _width, _height)
{
    // initialize cubes
    init();
}

CubeViewer::
~CubeViewer()
{
    // clean up any existing cubes
    for (std::vector<Mesh3D*>::iterator mIt = m_meshes.begin(); mIt != m_meshes.end(); ++mIt)
    {
        delete *mIt;
    }
    m_meshes.clear();
}

//-----------------------------------------------------------------------------

void 
CubeViewer::
init()
{
    // initialize parent
    TrackballViewer::init();

	// create uniform cube
    m_meshes.push_back(createCube());
    m_meshes.push_back(createCube());
    m_meshes.push_back(createCube());

	
	// move cube to (0,0,1)
	m_meshes[0]->scaleObject( Vector3(2,2,2) );
	m_meshes[0]->translateWorld( Vector3(0,0,1) );
    
    // make second smaller cube
    m_meshes[1]->rotateObject(Vector3(0,-1,0), M_PI);
	m_meshes[1]->translateWorld( Vector3(-1,1,0) );
    m_meshes[1]->scaleObject( Vector3(0.6,0.6,0.6) );
    
    // make a third even smaller cube
    m_meshes[2]->rotateAroundAxisObject(Vector3(0.2,0.4,-0.3), Vector3(0.6,0.4,1).normalize(), 5*M_PI/6);
	m_meshes[2]->translateObject( Vector3(-1,1,1) );

	// set camera to look at world coordinate center
    set_scene_pos(Vector3(0.0, 0.0, 0.0), 2.0);
	
	// load cube shader
	m_cubeShader.create("cube.vs", "cube.fs");
}

//-----------------------------------------------------------------------------

Mesh3D* 
CubeViewer::
createCube()
{
    // initialize Mesh3D
    Mesh3D *cube = new Mesh3D();
    
	// setup uniform cube with side length 0.5 and center of cube being (0,0,0)
	std::vector< Vector3 > cubeVertices;
	std::vector< Vector3 > cubeNormals;
	std::vector< Vector3 > cubeColors;
	std::vector< unsigned int > cubeIndices;
	float d = 0.25;
    
	
	// front
	cubeVertices.push_back(Vector3(-d,-d, d));
	cubeVertices.push_back(Vector3( d,-d, d));
	cubeVertices.push_back(Vector3( d, d, d));
	cubeVertices.push_back(Vector3(-d, d, d));
	for(int k = 0; k < 4; k++) cubeNormals.push_back(Vector3(0,0,1));
	for(int k = 0; k < 4; k++) cubeColors.push_back(Vector3(0.8,0.3,0.3));
	cubeIndices.push_back(0);
	cubeIndices.push_back(1);
	cubeIndices.push_back(2);
	cubeIndices.push_back(0);
	cubeIndices.push_back(2);
	cubeIndices.push_back(3);
	
	
	// right
	cubeVertices.push_back(Vector3( d,-d,-d));
	cubeVertices.push_back(Vector3( d,-d, d));
	cubeVertices.push_back(Vector3( d, d, d));
	cubeVertices.push_back(Vector3( d, d,-d));
	for(int k = 0; k < 4; k++) cubeNormals.push_back(Vector3(1,0,0));
	for(int k = 0; k < 4; k++) cubeColors.push_back(Vector3(0.3,0.8,0.3));
	cubeIndices.push_back(4);
	cubeIndices.push_back(5);
	cubeIndices.push_back(6);
	cubeIndices.push_back(4);
	cubeIndices.push_back(6);
	cubeIndices.push_back(7);
	
	
	// back
	cubeVertices.push_back(Vector3( d,-d,-d));
	cubeVertices.push_back(Vector3(-d,-d,-d));
	cubeVertices.push_back(Vector3(-d, d,-d));
	cubeVertices.push_back(Vector3( d, d,-d));
	for(int k = 0; k < 4; k++) cubeNormals.push_back(Vector3(0,0,-1));
	for(int k = 0; k < 4; k++) cubeColors.push_back(Vector3(0.3,0.3,0.8));
	cubeIndices.push_back(8);
	cubeIndices.push_back(9);
	cubeIndices.push_back(10);
	cubeIndices.push_back(8);
	cubeIndices.push_back(10);
	cubeIndices.push_back(11);
	
    
	// left
	cubeVertices.push_back(Vector3(-d,-d, d));
	cubeVertices.push_back(Vector3(-d,-d,-d));
	cubeVertices.push_back(Vector3(-d, d,-d));
	cubeVertices.push_back(Vector3(-d, d, d));
	for(int k = 0; k < 4; k++) cubeNormals.push_back(Vector3(-1,0,0));
	for(int k = 0; k < 4; k++) cubeColors.push_back(Vector3(0.8,0.8,0.3));
	cubeIndices.push_back(12);
	cubeIndices.push_back(13);
	cubeIndices.push_back(14);
	cubeIndices.push_back(12);
	cubeIndices.push_back(14);
	cubeIndices.push_back(15);
	
    
	// top
	cubeVertices.push_back(Vector3(-d, d,-d));
	cubeVertices.push_back(Vector3( d, d,-d));
	cubeVertices.push_back(Vector3( d, d, d));
	cubeVertices.push_back(Vector3(-d, d, d));
	for(int k = 0; k < 4; k++) cubeNormals.push_back(Vector3(0,1,0));
	for(int k = 0; k < 4; k++) cubeColors.push_back(Vector3(0.8,0.3,0.8));
	cubeIndices.push_back(16);
	cubeIndices.push_back(17);
	cubeIndices.push_back(18);
	cubeIndices.push_back(16);
	cubeIndices.push_back(18);
	cubeIndices.push_back(19);
	
    
	// bottom
	cubeVertices.push_back(Vector3( d,-d,-d));
	cubeVertices.push_back(Vector3(-d,-d,-d));
	cubeVertices.push_back(Vector3(-d,-d, d));
	cubeVertices.push_back(Vector3( d,-d, d));
	for(int k = 0; k < 4; k++) cubeNormals.push_back(Vector3(0,-1,0));
	for(int k = 0; k < 4; k++) cubeColors.push_back(Vector3(0.3,0.8,0.8));
	cubeIndices.push_back(20);
	cubeIndices.push_back(21);
	cubeIndices.push_back(22);
	cubeIndices.push_back(20);
	cubeIndices.push_back(22);
	cubeIndices.push_back(23);
	
	
	cube->setIndices(cubeIndices);
	cube->setVertexPositions(cubeVertices);
	cube->setVertexNormals(cubeNormals);
	cube->setVertexColors(cubeColors);
    
    return cube;
}

//-----------------------------------------------------------------------------

void
CubeViewer::
keyboard(int key, int x, int y)
{
	double scale = 0.01;
	
	switch (key)
	{			
		case 'h': 
			printf("'h'\t-\thelp\n");
			printf("'r'\t-\treset camera\n");
			printf("'c'\t-\tcut clippling planes\n");
			printf("'+/-'\t-\tmove clipping planes\n");
			printf("up/down\t-\trotate cube in world coordinates\n");
			printf("left/right\t-\trotate cube in camera coordinates\n");
			break;
		case 'r':
			// reset camera position
			m_camera.setIdentity();
            
            // delete existing cubes
            for (std::vector<Mesh3D*>::iterator mIt = m_meshes.begin(); mIt != m_meshes.end(); ++mIt)
            {
                delete *mIt;
            }
            m_meshes.clear();
            
            // reinitialize
            init();
			break;
		case 'c': {
			// setup clipping plane for object
			// project world coordinate into camera and get depth (-1 due to negative direction)
			Vector3 pt = m_camera.getTransformation().Inverse() * Vector3(0,0,0);
			double depth = -pt.z;
			m_camera.setClippingPlanes(depth-scale, depth+scale);
			break;
		}
		case '-':
			// decrease clipping planes
			m_camera.setClippingPlanes(m_camera.getNearPlane()-scale, m_camera.getFarPlane()-scale);
			break;
		case '+':
			// increase clipping planes
			m_camera.setClippingPlanes(m_camera.getNearPlane()+scale, m_camera.getFarPlane()+scale);
			break;
		default:
			TrackballViewer::keyboard(key, x, y);
			break;
	}
	
	glutPostRedisplay();
}

//-----------------------------------------------------------------------------

void
CubeViewer::
special(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            for (std::vector<Mesh3D*>::iterator mIt = m_meshes.begin(); mIt != m_meshes.end(); ++mIt)
            {
                Mesh3D *cube = *mIt;
                cube->rotateWorld( Vector3(0,1,0), -10.0 / 180.0 * M_PI );
            }
            break;
        case GLUT_KEY_DOWN:
            for (std::vector<Mesh3D*>::iterator mIt = m_meshes.begin(); mIt != m_meshes.end(); ++mIt)
            {
                Mesh3D *cube = *mIt;
                cube->rotateWorld( Vector3(0,1,0),  10.0 / 180.0 * M_PI );
            }
            break;
        case GLUT_KEY_LEFT:
            for (std::vector<Mesh3D*>::iterator mIt = m_meshes.begin(); mIt != m_meshes.end(); ++mIt)
            {
                Mesh3D *cube = *mIt;
                cube->rotateObject( Vector3(0,1,0), -10.0 / 180.0 * M_PI );
            }
            break;
        case GLUT_KEY_RIGHT:
            for (std::vector<Mesh3D*>::iterator mIt = m_meshes.begin(); mIt != m_meshes.end(); ++mIt)
            {
                Mesh3D *cube = *mIt;
                cube->rotateObject( Vector3(0,1,0), 10.0 / 180.0 * M_PI );
            }
            break;
        default:
            TrackballViewer::special(key, x, y);
            break;
    }
	
	glutPostRedisplay();
}


//-----------------------------------------------------------------------------

void
CubeViewer::
draw_mesh(Mesh3D *mesh)
{	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer( 3, GL_DOUBLE, 0, mesh->getVertexPointer() );
	glNormalPointer( GL_DOUBLE, 0, mesh->getNormalPointer() );
	glColorPointer( 3, GL_DOUBLE, 0, mesh->getColorPointer() );
	
	glDrawElements( GL_TRIANGLES, mesh->getNumberOfFaces()*3, GL_UNSIGNED_INT, mesh->getVertexIndicesPointer() );
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

//-----------------------------------------------------------------------------

void 
CubeViewer::
draw_scene(DrawMode _draw_mode)
{
	// clear screen
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_CULL_FACE);
	
    // first bind the shader
	m_cubeShader.bind(); 
	
	// set parameters to send to the shader
	m_cubeShader.setMatrix4x4Uniform("WorldCameraTransform", m_camera.getTransformation().Inverse());
	m_cubeShader.setMatrix3x3Uniform("WorldCameraNormalTransform", m_camera.getTransformation().Transpose());
	m_cubeShader.setMatrix4x4Uniform("ProjectionMatrix", m_camera.getProjectionMatrix());

    for (std::vector<Mesh3D*>::iterator mIt = m_meshes.begin(); mIt != m_meshes.end(); ++mIt)
    {
        Mesh3D *cube = *mIt;
        
        // besides during we can apply transformations just before rendering:
        // save the original transformation of the cube
        Matrix4 originalTransformation = cube->getTransformation();
        
        // rotate the cube before rendering
        cube->rotateObject(Vector3(0,1,0), M_PI/4);
        
        // send the model parameters to the shader
        m_cubeShader.setMatrix4x4Uniform("ModelWorldTransform", cube->getTransformation() );
        m_cubeShader.setMatrix3x3Uniform("ModelWorldNormalTransform", cube->getTransformation().Inverse().Transpose());
        
        // render the cube
        draw_mesh(cube);
        
        // ((( Exercise 3.6 )))
        
        // then reset the original transformation
        cube->setTransformation( originalTransformation );
    }
	
    // for illustration render a small sphere at the world center
	Matrix4 ident;
	ident.loadIdentity();
	m_cubeShader.setMatrix4x4Uniform("ModelWorldTransform", ident );
	m_cubeShader.setMatrix3x3Uniform("ModelWorldNormalTransform", ident );
	
	glColor3f(1.0,1.0,1.0); // set sphere color to white
	glutSolidSphere( 0.05, 10, 10 );
	
	// finally, unbind the shader
	m_cubeShader.unbind();
		
}

//=============================================================================

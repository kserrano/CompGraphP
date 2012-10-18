//=============================================================================
//                                                                            
//   Exercise code for Introduction to Computer Graphics
//   LGG - EPFL
//   Thibaut Weise, Yuliy Schwartzburg
//                                                                            
//=============================================================================

#include "CubeViewer.h"



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	
	CubeViewer window("Cube Viewer", 800, 800);
	
	glutMainLoop();
}

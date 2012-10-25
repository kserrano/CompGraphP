//=============================================================================
//                                                                            
//   Exercise code for the lecture
//                                                                            
//=============================================================================

#include "SolarViewer.h"



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	
	SolarViewer window("Solar Viewer", 800, 800);
	
	if(argc > 1)
	{
		window.load_mesh(argv[1], STARS);
	}
	if(argc > 2)
	{
		window.load_mesh(argv[2], SUN);
	}
	if(argc > 3)
	{
		window.load_mesh(argv[3], EARTH);
	}
	if(argc > 4)
	{
		window.load_mesh(argv[4], MOON);
	}
	for(int i = 5; i < argc; i++)
		window.load_mesh(argv[i], MeshType( MERCURY+(i-5) ));
	
	glutMainLoop();
}

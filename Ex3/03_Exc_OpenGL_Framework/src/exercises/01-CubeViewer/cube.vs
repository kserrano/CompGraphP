uniform mat4 ModelWorldTransform;
uniform mat4 WorldCameraTransform;
uniform mat4 ProjectionMatrix;

uniform mat3 WorldCameraNormalTransform;
uniform mat3 ModelWorldNormalTransform;

varying vec3 normal;
varying vec4 color;



void main()
{
	// Exercise 3.2.5 and 3.3.1
	// right now this renders everything explicitely set to be within the unit cube
	gl_Position = gl_Vertex;

	// need this line so OpenGL doesn't optimize out the variables -- remove in your solution
    // {
	ModelWorldTransform; WorldCameraTransform; ProjectionMatrix; WorldCameraNormalTransform; ModelWorldNormalTransform; normal; color;
    // }
}
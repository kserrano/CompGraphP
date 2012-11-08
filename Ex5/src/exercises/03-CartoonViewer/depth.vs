uniform mat4 modelworld;
uniform mat4 worldcamera;
uniform mat4 projection;

uniform float near; // near plane
uniform float far; // far plane

varying float depth; // The varying that need to be set to the linear depth re-scaled between 0 and 1 

void main()
{	  
	// transform vertex to camera coordinates
	vec3 vertex = vec3( worldcamera * modelworld * gl_Vertex );
	 
	// compute the linear depth - store depth between 0 and 1
	depth = 0.0;
	
	// project the point into the camera
	gl_Position = projection * vec4( vertex, 1.0 );
	
}

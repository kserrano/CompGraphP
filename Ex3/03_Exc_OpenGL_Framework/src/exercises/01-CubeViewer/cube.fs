varying vec4 color;
varying vec3 normal;



void main()
{
	// Exercise 3.3.2
    gl_FragColor = vec4(0.3, 0.3, 0.6, 1.0);
	
	// need this line so OpenGL doesn't optimize out the variables -- remove in your solution
    // {
	normal; color;
    // }
}
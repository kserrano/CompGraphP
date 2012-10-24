varying vec4 color;
varying vec3 normal;



void main()
{
	// Exercise 3.3.2
    if(-dot((0.0,0.0,-1.0),normal)>0.0){
        gl_FragColor = color*(-dot((0.0,0.0,-1.0),normal));
	} else {
        gl_FragColor = (0.0,0.0,0.0,1.0);
    }
	// need this line so OpenGL doesn't optimize out the variables -- remove in your solution
    // {
	//normal; color;
    // }
}
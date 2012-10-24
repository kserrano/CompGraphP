varying vec4 color;
varying vec3 normal;



void main()
{
    //gl_FragColor = vec4(0.3,0.3,0.6,1.0);
	// Exercise 3.3.2
    vec3 lightVector = vec3(0,0,-1);
    float dotProduct = -dot(lightVector,normal);
    vec4 black = (0.0,0.0,0.0,0.0);
    if(dotProduct >= 0.0){
        gl_FragColor = color*dotProduct;
	} else {
        gl_FragColor = black;
    }

	// need this line so OpenGL doesn't optimize out the variables -- remove in your solution
    // {
	//normal; color;
    // }
}
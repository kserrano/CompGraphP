varying vec4 color;
varying vec3 normal;



void main()
{
	// Exercise 3.3.2
    vec3 lightVector = vec3(0,0,-1);
    float dotProduct = -dot(lightVector,normal);
    vec4 black = (0.0,0.0,0.0,1.0);
    if(dotProduct > 0.0){
        gl_FragColor = color*dotProduct;
	} else {
        gl_FragColor = black;
    }
//    vec3 lightDir = vec3(0,0,-1);
//    float scale = -dot(lightDir, normal);
//    if(scale < 0.0)
//        scale = 0.0;
//    gl_FragColor.rgb = color.rgb*scale;
//    gl_FragColor.a = color.a;
	// need this line so OpenGL doesn't optimize out the variables -- remove in your solution
    // {
	//normal; color;
    // }
}
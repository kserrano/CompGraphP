varying vec3 normal, lightDir, indirectLightDir;

uniform int useTexture;
uniform sampler2D texture;
uniform vec3 diffuseColor;
uniform float specularExp;
uniform vec3 indirectlightcolor;
uniform vec3 lightcolor;
		
void main()
{	
	//Exercise 4.4: Calculate the reflected intensities for the direct sun light (using lightDir and lightcolor) 
	//and indirect light (using indirectLightDir and indirectlightcolor)	
	vec4 finalcolor = vec4(0.0);
	
    vec3 color;
    vec3 indcolor;
    if(useTexture==0){
	    color = diffuseColor;
	    indcolor = diffuseColor;
	} else {
        color = diffuseColor*texture;
	    indcolor = diffuseColor*texture;
    }

    float Isun = lightcolor*color*(dot(normal, lightDir));
    float Iind = indirectlightcolor*indcolor*(dot(normal, indirectLightDir));
	//also add a small ambient term
	finalcolor += vec4(color, Isun) + vec4(indcolor, Iind) + vec4(color, Isun)*0.1;	

	gl_FragColor = finalcolor;	
	
	// need this line so OpenGL doesn't optimize out the variables -- remove in your solution
	//useTexture; texture; lightcolor; indirectlightcolor; specularExp;
}
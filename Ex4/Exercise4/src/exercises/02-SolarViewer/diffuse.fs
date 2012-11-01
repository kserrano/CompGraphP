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
	
    vec3 tex = texture2D(texture, gl_TexCoord[0].xy).xyz;
    vec3 color;
    vec3 indcolor;
    if(useTexture==0){
	    color = diffuseColor;
	    indcolor = diffuseColor;
	} else {
        color = diffuseColor*tex;
	    indcolor = diffuseColor*tex;
    }

    if(-dot(normal, lightDir)){
        color = lightcolor*color*(-dot(normal, lightDir));
    } else {
        color = 0.0;
    }
    if(-dot(normal, indirectLightDir)){
        indcolor = indirectlightcolor*indcolor*(-dot(normal, indirectLightDir));
    } else {
        indcolor = 0.0;
    }

	//also add a small ambient term
	finalcolor += vec4(color, 1.0) + vec4(indcolor, 1.0) + vec4(color, 1.0)*0.1;	

	gl_FragColor = finalcolor;	
	
	// need this line so OpenGL doesn't optimize out the variables -- remove in your solution
	//useTexture; texture; lightcolor; indirectlightcolor; specularExp;
}
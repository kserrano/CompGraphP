uniform sampler2D texture; //the depth texture that need to be post processed with the sobel operator

uniform float dx; //use this uniform to move 1 pixel in x
uniform float dy; //use this uniform to move 1 pixel in y
		
float value(int x, int y){
    return texture2D(texture, gl_TexCoord[0].xy + vec2(x * dx, y * dy)).x;
}

void main()
{	
	//
	// calculate sobel edges
	//               -1  0  1
	// x derivative: -2  0  2
	//               -1  0  1
	// 
	//                1  2  1
	// y derivative:  0  0  0
	//               -1 -2 -1
	//

	float Gx = -value(-1,-1) + value(1,-1) - 2.0*value(-1,0) + 2.0*value(1,0) - value(-1,1) + value(1,1);
    float Gy = value(-1,-1) + 2.0*value(0,-1) + value(1,-1) - value(-1,1) - 2.0*value(0,1) - value(1,1);

	gl_FragColor = 1.0 - 10.0*sqrt(Gx*Gx + Gy*Gy);
	
}
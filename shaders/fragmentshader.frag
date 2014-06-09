#version 400
 
//this is the output of our fragment shader - four component color
layout(location = 0) out vec4 FragColor; 

//per-pixel normals (as computed per vertex in vertex shader)
in vec3 f_normal; 


//fragment shaders operate on "all" active fragments (pixels) in parallel 
//(i.e., all fragments that are being drawn while the shader is active)

void main(void)	
{
	float d = abs(dot(f_normal,vec3(0.0,0.0,-0.8))); 	//basic, fake lighting based on dot product of normal and arbitrary "light vector"
        FragColor = vec4(d,d,d,1.0);				//sets color of current pixel
}

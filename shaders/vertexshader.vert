#version 400
 
//input of vertex shader: vertex positions and normals
in vec3 in_position;
in vec3 in_normal;

//output of vertex shader: one transformed normal per vertex
out vec3 f_normal;

//modelview and projection matrix
uniform mat4 m_mvp; 
//matrix for transformation of normals
uniform mat4 m_normalmatrix; 


//vertex shader operates on all vertices in parallel
void main(void)
{

	//modelview and projection transformation is applied to position
	//rotates, translates, and projects positions - note 1.0 w component for positions
	gl_Position = m_mvp * vec4(in_position, 1.0);  	    

	
	//rotate normals - note 0.0 w component for directions
	//f_normal values will be available per-pixel in the fragment shader
        f_normal = vec3(m_normalmatrix*vec4(in_normal,0.0));	
  
}
#define GLFW_INCLUDE_GLU
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include "cube.hpp"
#include <iostream>


/*
 Construct cube - initialize vertex buffer object.
 
 Buffers replace old obsolete glBegin/glEnd fixed function pipeline drawing techniques.
 */
Cube::Cube(const int pos_attribute_location, const int normal_attribute_location)
{
    //vertex and normal data for VBO
    //this array holds position values (first half) of vertices and normal data for vertices (second half)
    float data[] = {
    //vertices
    //Bottom face
    -1,-1,-1,
    1,-1,-1,
    1,-1,1,
    -1,-1,-1,
    1,-1,1,
    -1,-1,1,
	
    // Top 
    -1,1,-1,
    -1,1,1,
    1,1,1,
    -1,1,-1,
    1,1,1,
    1,1,-1,
	
    // Front 
    -1,-1,1,
    1,-1,1,
    1,1,1,
    -1,-1,1,
    1,1,1,
    -1,1,1,
	
    // Back 
    -1,-1,-1,
    -1,1,-1,
    1,1,-1,
    -1,-1,-1,
    1,1,-1,
    1,-1,-1,
    
    // Right 
    1,-1,-1,
    1,1,-1,
    1,1,1,
    1,-1,-1,
    1,1,1,
    1,-1,1,
	
    // Left 
    -1,-1,-1,
    -1,-1,1,
    -1,1,1,
    -1,-1,-1,
    -1,1,1,
    -1,1,-1,
        
    //normals
    //bottom face
    0,-1,0,
    0,-1,0,
    0,-1,0,
    0,-1,0,
    0,-1,0,
    0,-1,0,
        
    // Top 
    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0,
        
    // Front 
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
        
    // Back 
    0,0,-1,
    0,0,-1,
    0,0,-1,
    0,0,-1,
    0,0,-1,
    0,0,-1,
    
    // Right 
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
        
    // Left 
    -1,0,0,
    -1,0,0,
    -1,0,0,
    -1,0,0,
    -1,0,0,
    -1,0,0};
    
    glGenVertexArrays(1,&m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vertexbuffer);               //generate a vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);  //bind buffer to be active
    glBufferData(GL_ARRAY_BUFFER, 216*sizeof(float), data, GL_STATIC_DRAW); //set buffer data
   
    
    glEnableVertexAttribArray(pos_attribute_location); //point to position attribute in shader
    glVertexAttribPointer(pos_attribute_location, 3, GL_FLOAT, GL_FALSE, 0, 0); //indicates array data of position attribute
   
    glEnableVertexAttribArray(normal_attribute_location); //point to normal attribute in shader
    glVertexAttribPointer(normal_attribute_location, 3, GL_FLOAT, GL_FALSE, 0, (void*)(108*sizeof(float))); //indicates array data of normal attribute in shader
   
    
}

/*
 Destroy Cube - clean up geometry
 */
Cube::~Cube()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);       //unbind current buffer
    glDeleteBuffers(1, &m_vertexbuffer);    //delete buffer data
    glDeleteVertexArrays(1,&m_vao);
}


/*
 Draw Cube
 */
void Cube::draw()
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

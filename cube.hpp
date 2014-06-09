#ifndef _CUBE_HPP_
#define _CUBE_HPP_

/*
 Cube class
 */
class Cube
{
private:
    unsigned int m_vertexbuffer;     //points to vertex buffer object
    unsigned int m_vao;             //points to vertex array object
  
public:
    Cube(const int pos_attribute_location, const int normal_attribute_location);
    ~Cube();
    void draw();
};




#endif


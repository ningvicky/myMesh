#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <vector>


struct Triangle
{
	int p[3];	//indices of vertices
	Triangle(int a, int b, int c)
	{
		p[0] = a;
		p[1] = b;
		p[2] = c;
	}
	Triangle(const Triangle &t)
	{
			p[0] = t.p[0];
			p[1] = t.p[1];
			p[2] = t.p[2];
			

	}
	Triangle & operator=(const Triangle &t)
	{
		if(this != &t)
		{
			p[0] = t.p[0];
			p[1] = t.p[1];
			p[2] = t.p[2];
			
		}
		return *this;
	}
};

struct Vector
{
	float x,y,z;
    Vector(float _x,float _y,float _z)
    {
        x = _x; y = _y; z = _z;
        
    }
};


class Mesh
{
    private:
        std::vector<Vector> vertices;
        std::vector<Vector> normals;
        std::vector<Triangle> triangles;
        void createVBO();
	public:
        void readMesh(const char *filename);
        void draw();

};


#endif
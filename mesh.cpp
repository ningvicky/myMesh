#include "mesh.hpp"
#include <list>
#include <fstream>
#include <iostream>
using namespace std;

/*
 Read obj mesh file - note: only simple basic format supported at the moment
 */
void Mesh::readMesh(const char* filename)
{
    //use lists for fast append during read
    list<Triangle> trilist;
    list<Vector> vertlist;
    list<Vector> normlist;
    
    ifstream infile(filename);
    if(!infile)
    {
        cout << "File " << filename << " does not exist.";
        return;
    }
    
    char tag[2];
    char line[128];
    while(!infile.eof())
    {
        infile >> tag;
        
        if(infile.eof())
            break;
        if(tag[0] == '#') //this is a comment line - skip line
            infile.getline(line,127); //read and ignore line
        else if(tag[0] == 'v')
        {
            if(tag[1] == 'n') //normal
            {
                float nx,ny,nz;
                infile >> nx >> ny >> nz;
                normlist.push_back(Vector(nx,ny,nz));
            }
            else if(tag[1] == 't') //texture coordinate
            {
              
                float s,t;
                infile >> s >> t;
                //TODO: save this as well
            }
            else//vertex position
            {
                float x,y,z;
                infile >> x >> y >> z;
                vertlist.push_back(Vector(x,y,z));
            }
        }
        else if(tag[0] == 'f') //triangle
        {
            int i,j,k;
            infile >> i >> j >> k;
            trilist.push_back(Triangle(i-1,j-1,k-1));
        }
    }
    
    infile.close();
    
    //copy into vectors for fast access
    vertices = vector<Vector>(vertlist.begin(),vertlist.end());
    normals = vector<Vector>(normlist.begin(),normlist.end());
    triangles = vector<Triangle>(trilist.begin(),trilist.end());
    
    cout << "Loaded: " << vertices.size() << " vertices and " << triangles.size() << " triangles." << endl;
    
    createVBO();
}


/*
 Creates Vertex Buffer Object for drawing
 */
void Mesh::createVBO()
{
    //TODO: create Vertex Buffer Object from mesh data
    
    
}


/*
 Draws the surface
 */
void Mesh::draw()
{
    
    
    
}

#define GLFW_INCLUDE_GLU
#include <OpenGL/gl3.h>
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <GLFW/glfw3.h>
#include "shader_utils.hpp"
#include "bitmap/bitmap.h" //Bitmap loader by Benjamin Kalytta http://www.kalytta.com/bitmap.h
#include "cube.hpp"
#include <iostream>

//shaders
unsigned int m_program;
unsigned int m_vertexsh;
unsigned int m_fragmentsh;

unsigned int m_pos_attribute_location;
unsigned int m_normal_attribute_location;
unsigned int m_mvp_location;
unsigned int m_normalmatrix_location;

//buffers - for geometry
unsigned int m_fps = 0;
unsigned int m_frames = 0;

Cube *cube = NULL; //the cube object that we want to draw


//for texturing
//unsigned int m_texture; //id of texture
//unsigned int m_texture_location; //location of texture uniform in shader

/*
 Loads a texture and stores it in m_texture for use
 */
/*void loadTextures()
 {
 
 /*CBitmap image("texture.bmp");               //read bitmap image
 
 glGenTextures(1,&m_texture);                //allocate 1 texture
 glBindTexture(GL_TEXTURE_2D, m_texture);    //bind this texture to be active
 glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image.GetWidth(),image.GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.GetBits()); //load data into texture
 
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //specify minificaton filtering
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //specify magnificaton filtering
 
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    //specify texture coordinate treatment
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    //specify texture coordinate treatment
 glEnable(GL_TEXTURE_2D);    //enable texturing
 
 }*/




/*
    Read and compile shaders. Also sets up locations of attributes and uniforms.
 */
void makeShaders()
{
    m_program = glCreateProgram();

    char *shadercode = readShader("shaders/vertexshader.vert");	//reads shader code (you can edit shader code with a text editor)
    m_vertexsh = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexsh, 1, (const GLcharARB **)&shadercode,NULL);
    delete[] shadercode;
    glCompileShader(m_vertexsh);    //compiles shader
    printInfoLog(m_vertexsh);       //prints errors during shader compilation


    shadercode = readShader("shaders/fragmentshader.frag");     //reads shader code (you can edit shader code with a text editor)
    m_fragmentsh = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentsh, 1, (const GLcharARB **)&shadercode,NULL);
    delete[] shadercode;
    glCompileShader(m_fragmentsh);  //compiles shader
    printInfoLog(m_fragmentsh);     //prints errors during shader compilation

    glAttachShader(m_program,m_vertexsh);
    glAttachShader(m_program,m_fragmentsh);

    glLinkProgram(m_program);   //compiles fragment and vertex shader into a shader program
    printInfoLog(m_program);    //prints errors during program compilation

    glUseProgram(m_program);
    m_pos_attribute_location = glGetAttribLocation(m_program,"in_position");  //get pointer to "in_position" attribute of vertex shader
    m_normal_attribute_location = glGetAttribLocation(m_program,"in_normal");  //get pointer to "in_normal" attribute of vertex shader
    
    m_mvp_location = glGetUniformLocation(m_program,"m_mvp");   //get pointer to m_mvp attribute
    m_normalmatrix_location = glGetUniformLocation(m_program,"m_normalmatrix");

    glUseProgram(0);
}


/*
 Clean up shaders - after use
 */
void cleanupShaders()
{
    glDetachShader(m_program,m_vertexsh);
	glDetachShader(m_program,m_fragmentsh);
    
    glDeleteProgram(m_program);
	glDeleteShader(m_vertexsh);
	glDeleteShader(m_fragmentsh);
}





/*
 Handle keyboard input
 */
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_R && action == GLFW_PRESS) //reload shaders - this allows you to modify shaders and test, without recompiling/restarting everything
    {
        cleanupShaders();
        makeShaders();
    }
    
}



/*
 Draw stuff
 */
void drawData()
{
    glUseProgram(m_program);
    
    if(cube)
        cube->draw(); //draw a cube
    
    glUseProgram(0);
}



/*
 Initialize Window
*/
GLFWwindow* initGLFW()
{
    if (!glfwInit())
        return NULL;
    
    glfwWindowHint(GLFW_SAMPLES, 4);        //anti aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  //get OpenGL 4 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 800, "Mesh", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback); //define keyboard input function
    
    return window;
}



/*
 Initialize OpenGL
 */
void initGL()
{
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    makeShaders();
    
    //create Cube
    cube = new Cube(m_pos_attribute_location,m_normal_attribute_location);
    
    glClearColor(1,1,1,1);
    const GLubyte *a= glGetString(GL_VERSION);
    std::cout << "OpenGL Version String: " << a << std::endl;
    
    //loadTextures();
}




int main(void)
{
    GLFWwindow* window;
    if(!(window = initGLFW()))
        return -1;
    initGL();
   
    
    //the main loop
    double lasttime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        //do some frame counting to output FPS
        double curtime = glfwGetTime();
        if ( curtime - lasttime >= 1.0 )
        {
            std::cout <<  "Fps: " << m_fps << std::endl; //output frames per second
            m_fps = 0;
            while(lasttime+1.0 < curtime)
                lasttime += 1.0;
        }
        m_fps++;
        m_frames++;
        
        
        //set viewport, projection, etc
        int width,height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //set up matrices for viewing
        glm::mat4 projection = glm::perspective(45.0f, (float)width/(float)height, 0.1f, 100.f); //projection matrix
        glm::mat4 view = glm::lookAt(glm::vec3(0.0,0,8.0), glm::vec3(0.0,0,0.0), glm::vec3(0.0,1.0,0.0) ); //set up camera position
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), m_frames/2.0f, glm::vec3(0.0f,1.0f,0.0) ); //rotate the object
        glm::mat4 mvp = view * model; //now mvp = modelview matrix
        glm::mat4 normalmatrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(mvp)))); //create normalmatrix
        mvp = projection*mvp;   //now mvp = modelview-projection matrix
        
        glUseProgram(m_program); //update matrix values in shader
        glUniformMatrix4fv(m_normalmatrix_location, 1, GL_FALSE, &normalmatrix[0][0]);
        glUniformMatrix4fv(m_mvp_location, 1, GL_FALSE, &mvp[0][0]);
        glUseProgram(0);
        
        
        
        
        drawData(); //actually draw stuff
        
        
        
        
        glfwSwapBuffers(window); //put results on screen
        glfwPollEvents(); //see if we have any inout events (for example: keyboard)
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    cleanupShaders();
    delete cube;
    
    return 0;
}
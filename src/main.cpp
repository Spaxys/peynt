#include <iostream>
#include <ctime>
#include <stdlib.h>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

//**********************
//Global variables
//*********************

//Mouse positions
static double xpos = 0, ypos = 0, xposOld = 0, yposOld = 0;
static float ratio = 1;
static int width = 800, height = 600;
//Do redraw?
static int do_redraw = 1;

void render();
void update();

/**
    - sleep function -
    Cross platform sleep implementation
*/
void _sleep(double ms)
{
    double st = clock();
    if (ms <= 0)
        ms = 10;
    while (clock() < (st + ms));
}



/*****************
	Special init function
	http://r3dux.org/2010/11/2d-c-openglglfw-basecode/
****************/
void initGL(GLFWwindow* window, int width, int height)
{
	// ----- Window and Projection Settings -----
 
	// Set the window title
	glfwSetWindowTitle(window, "GLFW Basecode");
 
	// Setup our viewport to be the entire size of the window
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
 
	// Change to the projection matrix, reset the matrix and set up orthagonal projection (i.e. 2D)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;  
	//glOrtho(0, width, height, 0, 0, 1); // Paramters: left, right, bottom, top, near, far
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	//glMatrixMode(GL_MODELVIEW);
 
	// ----- OpenGL settings -----
	glfwSwapInterval(1); 		// Lock to vertical sync of monitor (normally 60Hz, so 60fps)
	glEnable(GL_SMOOTH);		// Enable (gouraud) shading
	glDisable(GL_DEPTH_TEST); 	// Disable depth testing
	glEnable(GL_BLEND);		// Enable blending (used for alpha) and blending function to use
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(5.0f);		// Set a 'chunky' line width
	glEnable(GL_LINE_SMOOTH);	// Enable anti-aliasing on lines
	glPointSize(5.0f);		// Set a 'chunky' point size
	glEnable(GL_POINT_SMOOTH);	// Enable anti-aliasing on points
}

static float absToRelCoords(float absC, int axis, int width, int height)
{
	if(axis == 0) //x
	{
		if(absC < width/2)
			return -1 / absC;
	}
			
}

/**
    - Render function -
    Used to draw objects to the screen.
*/
void render(GLFWwindow* window)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Colour to clear the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
	
	
    // TODO: Draw stuff here!    
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
	glfwSwapBuffers(window);
}

/**
    - Update function -
    Updates objects. States, locations, etc
*/
void update()
{
    // TODO: Update objects here
}

/**
	input functions
*/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

//========================================================================
// Mouse position callback function
//========================================================================

static void cursorPosFun(GLFWwindow* window, double x, double y)
{

    // Remember cursor position
	xposOld = xpos;
	yposOld = ypos;
    xpos = x;
    ypos = y;
}


/**
    - main function -
    Program entry point
*/
int main(int argc, char** argv)
{
    std::cout << "Loading peynt" << std::endl;
	GLFWwindow* window;

//    glfwInit(); // Initialise GLFW
//
//    // Create glfw window
//    if (glfwOpenWindow(800, 600, 5, 6, 5, 0, 8, 0, GLFW_WINDOW) != GL_TRUE)
//        std::cout << "Error creating window!" << std::endl;

   // Initialise GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Open OpenGL window
    window = glfwCreateWindow(width, height, "peynt", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to open GLFW window!" << std::endl;

        glfwTerminate();
        exit(EXIT_FAILURE);
    }

	glfwMakeContextCurrent(window);
	initGL(window, width, height);

	//set callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursorPosFun);

    // Start main game loop
    // This calls the functions which update objects and render them to screen
    while (true)
    {
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float) height;

		glViewport(0,0,width,height);
		
        update();
		if(do_redraw)
	        render(window);
		
		if(xposOld != xpos || yposOld != ypos)
			std::cout << "Mouse position x: " << xpos << ", y: " << ypos << std::endl;

    //    glfwSwapBuffers(window); // Switch buffers (double buffering)
        _sleep(10); // Let a bit of CPU time for other processes
		glfwWaitEvents();

		//check if window should be closed
		if(glfwWindowShouldClose(window))
			break;
    }    
	glfwTerminate();

    exit(EXIT_SUCCESS);
}


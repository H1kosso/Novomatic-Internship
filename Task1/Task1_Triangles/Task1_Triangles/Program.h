#pragma once
#include "Triangle.h"

class Program {

public:
	//The constructor initializes GLFW, creates window, sets they key callback function, 
	//and loads all OpenGL functions pointers using GLAD
	//It also sets the vertices
  Program();

	//The destructor deallocates all OpenGL resources, including VAO, VBO and shader program
	//Also terminates GLFW
  ~Program();

	//This method runs the main loop that continuously renders the two triangles and checks if they are colliding. 
	//If the triangles are colliding, the background color is set to red, otherwise, it is set to green.
  void runMainLoop();

	//Moves triangle in given direction: Left, Up, Right, Down
  void moveTriangle2(int direction);

private:
  GLFWwindow *window;
  const unsigned int SCR_WIDTH = 800;
  const unsigned int SCR_HEIGHT = 600;

  static const int LEFT = 263;
  static const int UP = 265;
  static const int RIGHT = 262;
  static const int DOWN = 264;

  unsigned int vertexShader;
  unsigned int fragmentShader;
  unsigned int shaderProgram;
  unsigned int VBO;
  unsigned int VAO;
  float vertices[18];
  triangle triangle1{};
  triangle triangle2{};


  void glfwInitialization();
  void createWindow();

  //Checks if user pressed ESC on keyboard and close window
  void processInput(GLFWwindow *window);

  void loadShaders();

  //Updates the vertex buffer object with new vertices for the two triangles.
  void updateVertices();

  void bindVertexes();
  
};

#include <glad.h> 
#include <glfw3.h>
#include "../Program.h"
#include "../Shader.h"
#include "../Triangle.h"
#include <iostream>
#include <stdlib.h>

Program *program;

// glfw: when size of window is changged this function is called
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// whenever key is pressed this function is called
void keyCallback(GLFWwindow *window, int key, int scanCode, int action,
                 int mods);

Program::Program() {
  program = this;
  glfwInitialization();
  createWindow();
  glfwSetKeyCallback(window, keyCallback);
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    abort();
  }
  triangle1.points[0] = {-0.45f, -0.25f};
  triangle1.points[1] = {-0.0f, -0.25f};
  triangle1.points[2] = {-0.225f, 0.25f};

  triangle2.points[0] = {0.0f, -0.25f};
  triangle2.points[1] = {0.45f, -0.25f};
  triangle2.points[2] = {0.225f, 0.25f};
  updateVertices();
  loadShaders();
  bindVertexes();
}
Program::~Program() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
}

void Program::runMainLoop() {
  // render loop
  while (!glfwWindowShouldClose(window)) {
    // input
    processInput(window);

    // render
    isColliding(triangle1, triangle2) ? glClearColor(1.0f, 0.3f, 0.3f, 1.0f)
                                      : glClearColor(0.5f, 0.9f, 0.5f, 1.0f);
    

    glClear(GL_COLOR_BUFFER_BIT);

    bindVertexes();

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // glfw: swap buffers and poll IO events 
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void Program::glfwInitialization() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void Program::createWindow() {
  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangles collision", NULL,
                            NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    abort();
  }
}

void Program::loadShaders() {
  // vertex shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // fragment shader
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // link shaders
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Program::updateVertices() {
  unsigned int index = 0;
  for (int i = 0; i < 3; i++) {
    vertices[index++] = triangle1.points[i].x;
    vertices[index++] = triangle1.points[i].y;
    vertices[index++] = 0.0f;
  }
  for (int i = 0; i < 3; i++) {
    vertices[index++] = triangle2.points[i].x;
    vertices[index++] = triangle2.points[i].y;
    vertices[index++] = 0.0f;
  }
}

void Program::moveTriangle2(int direction) {
  const float MOVE_DISTANCE = 0.05f;
  switch (direction) {
  case LEFT:
    triangle2.points[0].x -= MOVE_DISTANCE;
    triangle2.points[1].x -= MOVE_DISTANCE;
    triangle2.points[2].x -= MOVE_DISTANCE;
    break;
  case UP:
    triangle2.points[0].y += MOVE_DISTANCE;
    triangle2.points[1].y += MOVE_DISTANCE;
    triangle2.points[2].y += MOVE_DISTANCE;
    break;
  case RIGHT:
    triangle2.points[0].x += MOVE_DISTANCE;
    triangle2.points[1].x += MOVE_DISTANCE;
    triangle2.points[2].x += MOVE_DISTANCE;
    break;
  case DOWN:
    triangle2.points[0].y -= MOVE_DISTANCE;
    triangle2.points[1].y -= MOVE_DISTANCE;
    triangle2.points[2].y -= MOVE_DISTANCE;
    break;
  }
  updateVertices();
}

void Program::bindVertexes() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}


void Program::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow *window, int key, int scanCode, int action,
                 int mods) {
  if (action == GLFW_PRESS || action == GLFW_REPEAT)
    program->moveTriangle2(key);
}

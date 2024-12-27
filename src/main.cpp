#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <iostream>


const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
    
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

   
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
#endif

    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Futuristic Emerald Isle", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    
    glfwSwapInterval(1);

    
    glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    
    glViewport(0, 0, WIDTH, HEIGHT);

    
    Shader ourShader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    
    GLfloat vertices[] = {
         0.0f,  0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f  
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO);      

    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); 

    
    while (!glfwWindowShouldClose(window))
    {
        
        glfwPollEvents();

        
        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        ourShader.use();

        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        
        glfwSwapBuffers(window);
    }

    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    
    glfwTerminate();
    return 0;
}

#include <GL/glew.h>
#include <GLFW/glfw3.h>
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

    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Futuristic Emerald Isle", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    
    glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    
    glViewport(0, 0, WIDTH, HEIGHT);

    
    while (!glfwWindowShouldClose(window))
    {
        
        glfwPollEvents();

        
        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        glfwSwapBuffers(window);
    }

    
    glfwTerminate();
    return 0;
}

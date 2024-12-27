

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "camera.h" 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


const GLuint WIDTH = 800, HEIGHT = 600;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);


Camera camera;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;


float deltaTime = 0.0f;	
float lastFrame = 0.0f;

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

    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    
    glfwSwapInterval(1);

    
    glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    
    glViewport(0, 0, WIDTH, HEIGHT);

    
    glEnable(GL_DEPTH_TEST);

    
    Shader ourShader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    
    GLfloat vertices[] = {
        
        
        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 
         0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 
         0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 
         0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 
        -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 
        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 

        
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 
         0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f, 

        
        -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, 
        -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, 
        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, 
        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f, 
        -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, 
        -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f, 

        
         0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f, 
         0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f, 
         0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f, 
         0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f, 
         0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f, 
         0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f, 

        
        -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, 
         0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, 
         0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, 
         0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, 
        -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, 
        -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, 

        
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, 
         0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, 
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, 
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, 
        -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, 
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f  
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO);      

    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); 

    
    GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
    GLint viewLoc  = glGetUniformLocation(ourShader.Program, "view");
    GLint projLoc  = glGetUniformLocation(ourShader.Program, "projection");
    GLint lightPosLoc = glGetUniformLocation(ourShader.Program, "lightPos");
    GLint lightColorLoc = glGetUniformLocation(ourShader.Program, "lightColor");
    GLint viewPosLoc = glGetUniformLocation(ourShader.Program, "viewPos");
    GLint objectColorLoc = glGetUniformLocation(ourShader.Program, "objectColor");

    
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    glm::vec3 objectColor(0.4f, 0.6f, 0.9f);

    
    while (!glfwWindowShouldClose(window))
    {
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        
        processInput(window);

        
        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        ourShader.use();

        
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), 
            (GLfloat)glfwGetTime() * glm::radians(50.0f), 
            glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 
            (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.Position));
        glUniform3fv(objectColorLoc, 1, glm::value_ptr(objectColor));

        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        
        glfwSwapBuffers(window);
    }

    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    
    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    
    glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

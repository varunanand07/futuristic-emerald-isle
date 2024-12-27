
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "camera.h"
#include "model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <cmath>

const GLuint WIDTH = 800, HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

Camera camera(glm::vec3(0.0f, 5.0f, 20.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float modelStartX = -50.0f;
float modelEndX = 50.0f;
float modelSpeed = 10.0f;

std::vector<glm::vec3> buildingPositions = {
    glm::vec3(-30.0f, 0.0f, -20.0f),
    glm::vec3(-10.0f, 0.0f, -25.0f),
    glm::vec3(10.0f, 0.0f, -15.0f),
    glm::vec3(25.0f, 0.0f, -30.0f),
    glm::vec3(40.0f, 0.0f, -10.0f)
};

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

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Toward a Futuristic Emerald Isle", NULL, NULL);
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

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    std::cout << "Viewport set to " << WIDTH << "x" << HEIGHT << ".\n";

    glEnable(GL_DEPTH_TEST);
    std::cout << "Depth testing enabled.\n";

    Shader ourShader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    std::cout << "Shaders compiled and linked.\n";

    Model myModel("../models/futuristic_model.obj");

    GLuint modelTexture;
    glGenTextures(1, &modelTexture);
    glBindTexture(GL_TEXTURE_2D, modelTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int texWidth, texHeight, texChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image = stbi_load("../textures/model_texture.jpg", &texWidth, &texHeight, &texChannels, 0);
    if (image)
    {
        GLenum format;
        if (texChannels == 1)
            format = GL_RED;
        else if (texChannels == 3)
            format = GL_RGB;
        else if (texChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Model texture loaded successfully.\n";
    }
    else
    {
        std::cerr << "Failed to load model texture.\n";
    }
    stbi_image_free(image);

    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.Program, "texture1"), 0);

    GLuint groundTexture;
    glGenTextures(1, &groundTexture);
    glBindTexture(GL_TEXTURE_2D, groundTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int groundWidth, groundHeight, groundNrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *groundData = stbi_load("../textures/ground_texture.jpg", &groundWidth, &groundHeight, &groundNrChannels, 0);
    if (groundData)
    {
        GLenum format;
        if (groundNrChannels == 1)
            format = GL_RED;
        else if (groundNrChannels == 3)
            format = GL_RGB;
        else if (groundNrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, groundWidth, groundHeight, 0, format, GL_UNSIGNED_BYTE, groundData);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Texture loaded successfully: ground_texture.jpg\n";
    }
    else
    {
        std::cerr << "Failed to load ground texture\n";
    }
    stbi_image_free(groundData);

    GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
    GLint viewLoc  = glGetUniformLocation(ourShader.Program, "view");
    GLint projLoc  = glGetUniformLocation(ourShader.Program, "projection");
    GLint lightPosLoc = glGetUniformLocation(ourShader.Program, "lightPos");
    GLint lightColorLoc = glGetUniformLocation(ourShader.Program, "lightColor");
    GLint viewPosLoc = glGetUniformLocation(ourShader.Program, "viewPos");
    GLint objectColorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
    GLint fogColorLoc = glGetUniformLocation(ourShader.Program, "fogColor");
    GLint fogDensityLoc = glGetUniformLocation(ourShader.Program, "fogDensity");
    GLint isGroundLoc = glGetUniformLocation(ourShader.Program, "isGround");

    if(modelLoc == -1 || viewLoc == -1 || projLoc == -1 ||
       lightPosLoc == -1 || lightColorLoc == -1 ||
       viewPosLoc == -1 || objectColorLoc == -1 ||
       fogColorLoc == -1 || fogDensityLoc == -1 ||
       isGroundLoc == -1)
    {
        std::cerr << "Error: One or more uniform locations not found.\n";
    }

    glm::vec3 lightPos(2.0f, 4.0f, 2.0f);
    glm::vec3 lightColor(0.0f, 1.0f, 0.0f);
    glm::vec3 objectColor(0.0f, 1.0f, 0.0f);
    glm::vec3 fogColor(0.05f, 0.2f, 0.1f);
    float fogDensity = 0.05f;

    GLfloat groundVertices[] = {
        -50.0f, -1.0f, -50.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         50.0f, -1.0f, -50.0f,  0.0f, 1.0f, 0.0f,  50.0f, 0.0f,
         50.0f, -1.0f,  50.0f,  0.0f, 1.0f, 0.0f,  50.0f, 50.0f,

         50.0f, -1.0f,  50.0f,  0.0f, 1.0f, 0.0f,  50.0f, 50.0f,
        -50.0f, -1.0f,  50.0f,  0.0f, 1.0f, 0.0f,  0.0f, 50.0f,
        -50.0f, -1.0f, -50.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f
    };

    GLuint groundVBO, groundVAO;
    glGenVertexArrays(1, &groundVAO);
    glGenBuffers(1, &groundVBO);

    glBindVertexArray(groundVAO);

    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    std::cout << "Ground VAO and VBO set up.\n";


    GLfloat cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f
    };

    GLuint buildingVBO, buildingVAO;
    glGenVertexArrays(1, &buildingVAO);
    glGenBuffers(1, &buildingVBO);

    glBindVertexArray(buildingVAO);

    glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    std::cout << "Building VAO and VBO set up.\n";

    GLuint buildingTexture;
    glGenTextures(1, &buildingTexture);
    glBindTexture(GL_TEXTURE_2D, buildingTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char *buildingImage = stbi_load("../textures/ground_texture.jpg", &groundWidth, &groundHeight, &groundNrChannels, 0);
    if (buildingImage)
    {
        GLenum format;
        if (groundNrChannels == 1)
            format = GL_RED;
        else if (groundNrChannels == 3)
            format = GL_RGB;
        else if (groundNrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, groundWidth, groundHeight, 0, format, GL_UNSIGNED_BYTE, buildingImage);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Building texture loaded successfully.\n";
    }
    else
    {
        std::cerr << "Failed to load building texture.\n";
    }
    stbi_image_free(buildingImage);

    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.Program, "texture1"), 0);
    glUniform1i(glGetUniformLocation(ourShader.Program, "texture3"), 2);


    ourShader.use();
    glUniform3fv(objectColorLoc, 1, glm::value_ptr(objectColor));
    glUniform3fv(fogColorLoc, 1, glm::value_ptr(fogColor));
    glUniform1f(fogDensityLoc, fogDensity);

    std::cout << "Entering main loop.\n";
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(fogColor.r, fogColor.g, fogColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 
            static_cast<GLfloat>(WIDTH) / static_cast<GLfloat>(HEIGHT), 0.1f, 100.0f);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.Position));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, modelTexture);

        glUniform1i(isGroundLoc, GL_FALSE);

        float xPos = modelStartX + fmod(currentFrame * modelSpeed, modelEndX - modelStartX);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(xPos, 5.0f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        myModel.Draw(ourShader);


        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, buildingTexture);

        glUniform1i(isGroundLoc, GL_FALSE);

        glBindVertexArray(buildingVAO);

        for (const auto& pos : buildingPositions)
        {
            glm::mat4 buildingModel = glm::mat4(1.0f);
            buildingModel = glm::translate(buildingModel, pos);
            buildingModel = glm::scale(buildingModel, glm::vec3(2.0f, 5.0f, 2.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(buildingModel));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);


        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, groundTexture);
        glUniform1i(glGetUniformLocation(ourShader.Program, "texture2"), 1);

        glUniform1i(isGroundLoc, GL_TRUE);

        glm::mat4 groundModel = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(groundModel));
        glBindVertexArray(groundVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "Exiting main loop.\n";

    glDeleteTextures(1, &modelTexture);
    glDeleteTextures(1, &groundTexture);
    glDeleteTextures(1, &buildingTexture);
    glDeleteVertexArrays(1, &groundVAO);
    glDeleteBuffers(1, &groundVBO);
    glDeleteVertexArrays(1, &buildingVAO);
    glDeleteBuffers(1, &buildingVBO);

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
    std::cout << "Framebuffer resized to " << width << "x" << height << "\n";
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - lastX;
    float yoffset = lastY - static_cast<float>(ypos);

    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// src/main.cpp

#define GLEW_STATIC // Define if using static linking
#include <GL/glew.h>  // Include GLEW before GLFW
#include <GLFW/glfw3.h>

#include "shader.h"
#include "camera.h"
#include "model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <cmath> // For fmod

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// Camera
Camera camera(glm::vec3(0.0f, 5.0f, 20.0f)); // Elevated camera position for better view
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;

// Model 1 movement parameters
float model1StartX = -50.0f;  // Starting X position
float model1EndX = 50.0f;     // Ending X position
float model1Speed = 10.0f;    // Speed of movement (units per second)

// Model 2 movement parameters (flying in opposite direction)
float model2StartX = 50.0f;   // Starting X position (opposite side)
float model2EndX = -50.0f;    // Ending X position
float model2Speed = 8.0f;     // Speed of movement (units per second)

// Paths for models to loop
float model1Distance = model1EndX - model1StartX;
float model2Distance = model2StartX - model2EndX;

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Configure GLFW for OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS compatibility
#endif

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Toward a Futuristic Emerald Isle", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Register callback functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Capture the mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);
    std::cout << "Viewport set to " << WIDTH << "x" << HEIGHT << ".\n";

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    std::cout << "Depth testing enabled.\n";

    // Build and compile our shader program
    Shader ourShader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    std::cout << "Shaders compiled and linked.\n";

    // Load the first spaceship model
    Model myModel1("../models/futuristic_model.obj"); // Ensure the path is correct

    // Load and create the first model's texture
    GLuint modelTexture1;
    glGenTextures(1, &modelTexture1);
    glBindTexture(GL_TEXTURE_2D, modelTexture1); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image, create texture and generate mipmaps
    int texWidth1, texHeight1, texChannels1;
    // Flip the image on load
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image1 = stbi_load("../textures/model_texture1.jpg", &texWidth1, &texHeight1, &texChannels1, 0);
    if (image1)
    {
        GLenum format1;
        if (texChannels1 == 1)
            format1 = GL_RED;
        else if (texChannels1 == 3)
            format1 = GL_RGB;
        else if (texChannels1 == 4)
            format1 = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format1, texWidth1, texHeight1, 0, format1, GL_UNSIGNED_BYTE, image1);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Model 1 texture loaded successfully.\n";
    }
    else
    {
        std::cerr << "Failed to load model 1 texture.\n";
    }
    stbi_image_free(image1);

    // Load the second spaceship model
    Model myModel2("../models/futuristic_model_2.obj"); // Ensure the path is correct

    // Load and create the second model's texture
    GLuint modelTexture2;
    glGenTextures(1, &modelTexture2);
    glBindTexture(GL_TEXTURE_2D, modelTexture2); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image, create texture and generate mipmaps
    int texWidth2, texHeight2, texChannels2;
    // Flip the image on load
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image2 = stbi_load("../textures/model_texture2.jpg", &texWidth2, &texHeight2, &texChannels2, 0);
    if (image2)
    {
        GLenum format2;
        if (texChannels2 == 1)
            format2 = GL_RED;
        else if (texChannels2 == 3)
            format2 = GL_RGB;
        else if (texChannels2 == 4)
            format2 = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format2, texWidth2, texHeight2, 0, format2, GL_UNSIGNED_BYTE, image2);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Model 2 texture loaded successfully.\n";
    }
    else
    {
        std::cerr << "Failed to load model 2 texture.\n";
    }
    stbi_image_free(image2);

    // Tell OpenGL for each sampler to which texture unit it belongs to (only needs to be done once)
    ourShader.use(); // Activate the shader before setting uniforms!
    glUniform1i(glGetUniformLocation(ourShader.Program, "texture1"), 0); // texture1 -> GL_TEXTURE0
    glUniform1i(glGetUniformLocation(ourShader.Program, "texture2"), 1); // texture2 -> GL_TEXTURE1

    // Load and create the ground texture
    GLuint groundTexture;
    glGenTextures(1, &groundTexture);
    glBindTexture(GL_TEXTURE_2D, groundTexture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load ground texture image, create texture and generate mipmaps
    int groundWidth, groundHeight, groundNrChannels;
    // Flip the image on load
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

    // Get the uniform locations for lighting and fog
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

    // Check for invalid uniform locations
    if(modelLoc == -1 || viewLoc == -1 || projLoc == -1 ||
       lightPosLoc == -1 || lightColorLoc == -1 ||
       viewPosLoc == -1 || objectColorLoc == -1 ||
       fogColorLoc == -1 || fogDensityLoc == -1 ||
       isGroundLoc == -1)
    {
        std::cerr << "Error: One or more uniform locations not found.\n";
    }

    // Define light and object properties
    glm::vec3 lightPos(2.0f, 4.0f, 2.0f); // Elevated light position
    glm::vec3 lightColor(0.0f, 1.0f, 0.0f); // Green light
    glm::vec3 objectColor(0.0f, 1.0f, 0.0f); // Green object
    glm::vec3 fogColor(0.05f, 0.2f, 0.1f); // Dark green fog
    float fogDensity = 0.05f;

    // Ground Plane Setup
    // Define ground plane vertices (large square ground)
    GLfloat groundVertices[] = {
        // Positions          // Normals           // Texture Coords
        // Ground plane (X and Z vary, Y is constant)
        -50.0f, -1.0f, -50.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         50.0f, -1.0f, -50.0f,  0.0f, 1.0f, 0.0f,  50.0f, 0.0f,
         50.0f, -1.0f,  50.0f,  0.0f, 1.0f, 0.0f,  50.0f, 50.0f,

         50.0f, -1.0f,  50.0f,  0.0f, 1.0f, 0.0f,  50.0f, 50.0f,
        -50.0f, -1.0f,  50.0f,  0.0f, 1.0f, 0.0f,  0.0f, 50.0f,
        -50.0f, -1.0f, -50.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f
    };

    // Setup VAO and VBO for ground plane
    GLuint groundVBO, groundVAO;
    glGenVertexArrays(1, &groundVAO);
    glGenBuffers(1, &groundVBO);

    glBindVertexArray(groundVAO);

    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Texture Coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO

    std::cout << "Ground VAO and VBO set up.\n";

    // Set object and fog colors
    ourShader.use();
    glUniform3fv(objectColorLoc, 1, glm::value_ptr(objectColor));
    glUniform3fv(fogColorLoc, 1, glm::value_ptr(fogColor));
    glUniform1f(fogDensityLoc, fogDensity);

    // Main loop
    std::cout << "Entering main loop.\n";
    while (!glfwWindowShouldClose(window))
    {
        // Per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Process user input
        processInput(window);

        // Clear the color and depth buffer
        glClearColor(fogColor.r, fogColor.g, fogColor.b, 1.0f); // Use fog color as background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader program
        ourShader.use();

        // Camera/View transformation
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // Projection
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 
            static_cast<GLfloat>(WIDTH) / static_cast<GLfloat>(HEIGHT), 0.1f, 100.0f);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Set lighting uniforms
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.Position));

        // -------------------- Render First Spaceship --------------------
        // Bind first model's texture to GL_TEXTURE0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, modelTexture1);

        // Set "isGround" uniform to false for the first model
        glUniform1i(isGroundLoc, GL_FALSE);

        // Calculate the current X position of the first model to simulate flying across the sky
        float xPos1 = model1StartX + fmod(currentFrame * model1Speed, model1Distance);

        // Draw the first loaded model
        glm::mat4 model1 = glm::mat4(1.0f); // Identity matrix
        // Apply transformations:
        model1 = glm::translate(model1, glm::vec3(xPos1, 5.0f, 0.0f)); // Translate model along X-axis
        model1 = glm::rotate(model1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate 90 degrees left
        model1 = glm::scale(model1, glm::vec3(0.005f, 0.005f, 0.005f)); // Scale the model down by 0.005f
        // Removed dynamic rotation to stop the spaceship from rotating
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
        myModel1.Draw(ourShader);

        // -------------------- Render Second Spaceship --------------------
        // Bind second model's texture to GL_TEXTURE1
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, modelTexture2);

        // Set "isGround" uniform to false for the second model
        glUniform1i(isGroundLoc, GL_FALSE);

        // Calculate the current X position of the second model to simulate flying in the opposite direction
        float xPos2 = model2StartX + fmod(currentFrame * model2Speed, model2Distance);

        // Draw the second loaded model
        glm::mat4 model2 = glm::mat4(1.0f); // Identity matrix
        // Apply transformations:
        model2 = glm::translate(model2, glm::vec3(xPos2, 8.0f, 0.0f)); // Translate model along X-axis and elevate Y-axis
        model2 = glm::rotate(model2, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate -90 degrees to face opposite direction
        model2 = glm::scale(model2, glm::vec3(0.006f, 0.006f, 0.006f)); // Scale the model down by 0.006f (slightly different size)
        // Removed dynamic rotation to stop the spaceship from rotating
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
        myModel2.Draw(ourShader);

        // -------------------- Render Ground Plane --------------------
        // Bind ground texture to GL_TEXTURE2
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, groundTexture);
        glUniform1i(glGetUniformLocation(ourShader.Program, "texture2"), 2); // Ensure shader uses 'texture2'

        // Set "isGround" uniform to true for ground
        glUniform1i(isGroundLoc, GL_TRUE);

        // Draw the ground plane
        glm::mat4 groundModel = glm::mat4(1.0f); // Identity matrix
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(groundModel));
        glBindVertexArray(groundVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "Exiting main loop.\n";

    // Cleanup
    glDeleteTextures(1, &modelTexture1);
    glDeleteTextures(1, &modelTexture2);
    glDeleteTextures(1, &groundTexture);
    glDeleteVertexArrays(1, &groundVAO);
    glDeleteBuffers(1, &groundVBO);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
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

// Callback whenever the window size changed (by OS or user resize)
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << "Framebuffer resized to " << width << "x" << height << "\n";
    glViewport(0, 0, width, height);
}

// Callback whenever the mouse moves
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - lastX;
    float yoffset = lastY - static_cast<float>(ypos); // Reversed since y-coordinates range from bottom to top

    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// Callback whenever the mouse scroll wheel scrolls
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

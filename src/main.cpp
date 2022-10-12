#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.hpp"
#include "resource_manager.hpp"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// settings
const unsigned int SCR_WIDTH = 480;
const unsigned int SCR_HEIGHT = 640;

Game Centipede(SCR_WIDTH, SCR_HEIGHT);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Centipede", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // OpenGL config
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Centipede.Init();

    double deltaTime = 0.0;
    double lastFrame = 0.0;

    double lastSecond = 0;
    int frameCount = 0;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;

        if (deltaTime >= 1.0 / 60.0)
        {
            lastFrame = currentTime;
            glfwPollEvents();

            // user input
            Centipede.ProcessInput(deltaTime);

            Centipede.Update(deltaTime);

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            Centipede.Render();

            glfwSwapBuffers(window);


            frameCount++;

            if (currentTime - lastSecond >= 1)
            {
                std::cout << frameCount << std::endl;
                frameCount = 0;
                lastSecond = glfwGetTime();
            }
        }
    }

    ResourceManager::Clear();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            if (Centipede.Keys[key] == 0)
                Centipede.Keys[key] = 1;
            else
                Centipede.Keys[key] = 2;
        else if (action == GLFW_RELEASE)
            Centipede.Keys[key] = 0;

        std::cout << Centipede.Keys[key];
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
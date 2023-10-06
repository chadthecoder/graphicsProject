#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <cmath>

#include "../include/Errors.hpp"
#include "../include/VertexBuffer.hpp"
#include "../include/IndexBuffer.hpp"
#include "../include/Sound.hpp"
#include "../include/VertexArray.hpp"
#include "../include/Shader.hpp"
#include "../include/Renderer.hpp"

bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos)
{
    //std::cout << xPos << " : " << yPos << "\n";
}

int main(void)
{
    //glfw window and cursor stuff

    GLFWwindow *window;
    // unsigned int gScaleLocation;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetCursorPosCallback(window, cursorPositionCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(10);

    // Init glew
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error\n";
    }

    //get opengl version
    std::cout << glGetString(GL_VERSION) << "\n";

    //temp scope to prevent errors
    {

    //positions and indices

    float positions[] = {
        -0.5f,
        -0.5f, // 0
        0.5f,
        -0.5f, // 1
        0.5f,
        0.5f, // 2
        -0.5f,
        0.5f, // 3
    };

    unsigned int indices[]{
        0, 1, 2,
        2, 3, 0};

    //buffer and array stuff

    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    //get shader from text

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    //add get uniform locations from shader
    //better way to do multiple uniforms?

    float red = 0.6f, green = 0.0f, blue = 1.0f, alpha = 1.0f;
    float incRed = -0.05f, incGreen = 0.05f, incBlue = -0.05f;
    bool inc = true;

    shader.SetUniform4f("u_Color", red, green, blue, alpha);

    static float Scale = 0.0f;
    static float scaleDelta = 0.05f;
    shader.SetUniform1f("u_gScale", Scale);

    static float incLoc = 0.0f;
    static float incDelta = 0.1f;
    shader.SetUniform1f("u_incLoc", incLoc);

    double mouseX, mouseY;
    shader.SetUniform2f("u_mouse", mouseX, mouseY);

    int resolutionWidth, resolutionHeight;
    shader.SetUniform2f("u_resolution", resolutionWidth, resolutionHeight);

    //unbind stuff
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    //setup engine for playing sound
    Sound sndEngine;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        //test
        shader.Bind();
        shader.SetUniform4f("u_Color", red, green, blue, alpha);

        //get cursor position from GLFW
        glfwGetCursorPos(window, &mouseX, &mouseY);
        shader.SetUniform2f("u_mouse", mouseX, mouseY);

        //get window resolution from GLFW
        glfwGetWindowSize(window, &resolutionWidth, &resolutionHeight);
        shader.SetUniform2f("u_resolution", resolutionWidth, resolutionHeight);

        Scale += scaleDelta;
        //std::cout << "\n\n\n\n\n";
        if(Scale <= -1.0f) std::cout << "\n\n\n\n\n\n\n\n\n hi \n\n\n\n\n\n\n\n"; //ma_engine_play_sound(&sndEngine, "res/snd/sound.mp3", NULL);
        //std::cout <<  Scale << "\n\n\n\n\n";
        if ((Scale >= 1.0f) || (Scale <= -1.0f))
        {
            scaleDelta *= -1.0f;
            sndEngine.Play("res/snd/sound.mp3");
        }
        shader.SetUniform1f("u_gScale", Scale);

        incLoc += incDelta;
        if ((incLoc >= 1.0f) || (incLoc <= -1.0f))
        {
            incDelta *= -1.0f;
        }
        shader.SetUniform1f("u_incLoc", incLoc);

        //draw
        renderer.Draw(va, ib, shader);

        //change green value
        if (green > 1.0f)
        {
            incGreen = -0.05f;
            //std::cout << "green dec\n";
        }
        else if (green < 0.0f)
        {
            incGreen = 0.05f;
            //std::cout << "green inc\n";
        }

        green += incGreen;
        //std::cout << "Green Value: " << green << "\n";

        //change blue value
        if (blue < 0.0f)
        {
            incBlue = 0.05f;
            //std::cout << "blue inc\n";
        }
        else if (blue > 1.0f)
        {
            incBlue = -0.05f;
            //std::cout << "blue dec\n";
        }

        blue += incBlue;
        //std::cout << "Blue Value: " << blue << "\n";

        //change red color
        if (red < 0.0f)
        {
            incRed = 0.05f;
            //std::cout << "red inc\n";
        }
        else if (red > 1.0f)
        {
            incRed = -0.05f;
            //std::cout << "red dec\n";
        }

        red += incRed;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //victor gordon youtube, uncomment next line when done with other vertex buffer info
    //glDeleteTextures(1, &texture);

    //end of temp scope to prevent errors
    }

    glfwTerminate();
    return 0;
}
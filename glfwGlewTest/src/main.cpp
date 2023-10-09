#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <cmath>

/* #include "../include/Errors.hpp"
#include "../include/VertexBuffer.hpp"
#include "../include/IndexBuffer.hpp"
#include "../include/Sound.hpp"
#include "../include/VertexArray.hpp"
#include "../include/Shader.hpp"
#include "../include/Renderer.hpp"
#include "../include/Texture.hpp" */
#include "Errors.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Sound.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos)
{
    //std::cout << xPos << " : " << yPos << "\n";
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
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
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //make so window is not resizable

    /* Create a windowed mode window and its OpenGL context */
    GLFWmonitor* monitor = glfwGetPrimaryMonitor(); 
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    //window = glfwCreateWindow(mode->width, mode->height, "Hello World", glfwGetPrimaryMonitor(), NULL);
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetKeyCallback(window, keyCallback);

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

    //get shader from text

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    
    //set shader uniform for resolution

    int resolutionWidth, resolutionHeight;
    shader.SetUniform2f("u_resolution", resolutionWidth, resolutionHeight);

    //get window resolution from GLFW
    shader.Bind();
    glfwGetWindowSize(window, &resolutionWidth, &resolutionHeight);
    shader.SetUniform2f("u_resolution", resolutionWidth, resolutionHeight);

    //positions and indices

    float positions[] = {
        (float)(resolutionWidth/4), (float)(resolutionWidth/4), 0.0f, 0.0f, // 0
        (float)(3*resolutionWidth/4), (float)(resolutionWidth/4), 1.0f, 0.0f, // 1
        (float)(3*resolutionWidth/4), (float)(3*resolutionWidth/4), 1.0f, 1.0f, // 2
        (float)(resolutionWidth/4), (float)(3*resolutionWidth/4), 0.0f, 1.0f // 3

        /* -0.5f, -0.5f, 0.0f, 0.0f, // 0
        0.5f, -0.5f, 1.0f, 0.0f, // 1
        0.5f, 0.5f, 1.0f, 1.0f, // 2
        -0.5f, 0.5f, 0.0f, 1.0f // 3 */
    };

    unsigned int indices[]{
        0, 1, 2,
        2, 3, 0};

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), __FILE__, __LINE__);
    GLCall(glEnable(GL_BLEND), __FILE__, __LINE__);

    //buffer and array stuff

    int floatsPerVertex = 4;
    VertexArray va;
    VertexBuffer vb(positions, 4 * floatsPerVertex * sizeof(float));

    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 2);
    layout.Push(GL_FLOAT, 2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    //model view projection matrix

    shader.Bind();
    glm::mat4 proj = glm::ortho(0.0f, (float)resolutionWidth, 0.0f, (float)resolutionHeight, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 mvp = proj * view;
    shader.SetUniformMat4f("u_MVP", mvp);

    //texture stuff, cpp logo
    Texture texture("res/img/cpp.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    //add get uniform locations from shader
    //better way to do multiple uniforms?

    float red = 0.6f, green = 0.0f, blue = 1.0f, alpha = 1.0f;
    float incRed = -0.05f, incGreen = 0.05f, incBlue = -0.05f;
    bool inc = true;
    shader.Bind();
    shader.SetUniform4f("u_Color", red, green, blue, alpha);

    float Scale = 0.0f;
    float scaleDelta = 0.05f;
    shader.Bind();
    shader.SetUniform1f("u_gScale", Scale);

    static float incLoc = 0.0f;
    static float incDelta = 0.1f;
    shader.Bind();
    shader.SetUniform1f("u_incLoc", incLoc);

    double mouseX, mouseY;
    shader.Bind();
    shader.SetUniform2f("u_mouse", mouseX, mouseY);

    //unbind stuff
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    //shader.Unbind();

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

        //get window resolution from GLFW
        glfwGetWindowSize(window, &resolutionWidth, &resolutionHeight);
        shader.SetUniform2f("u_resolution", resolutionWidth, resolutionHeight);
        glm::mat4 proj = glm::ortho(0.0f, (float)resolutionWidth, 0.0f, (float)resolutionHeight, -1.0f, 1.0f);
        shader.SetUniformMat4f("u_MVP", proj);

        shader.SetUniform4f("u_Color", red, green, blue, alpha);

        //get cursor position from GLFW
        glfwGetCursorPos(window, &mouseX, &mouseY);
        shader.SetUniform2f("u_mouse", mouseX, mouseY);

        Scale += scaleDelta;
        if ((Scale > 0.5f) || (Scale < 0.0f))
        {
            scaleDelta *= -1.0f;
            //sndEngine.Play("res/snd/sound.mp3");
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
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

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
//#include "imgui/backends/imgui_impl_opengl3_loader.h"
#include "imgui/backends/imgui_impl_opengl3.h"

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
    //glsl_version currently only used for imgui code
    const char* glsl_version = "#version 330"; //if 3.3, then 330 and same for newer versions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //make so window is not resizable
    glfwWindowHint(GLFW_SAMPLES, 4);

    /* Create a windowed mode window and its OpenGL context */
    GLFWmonitor* monitor = glfwGetPrimaryMonitor(); 
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    window = glfwCreateWindow(mode->width, mode->height, "Hello World", glfwGetPrimaryMonitor(), NULL);
    //window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
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
        /* (float)(resolutionWidth/4), (float)(resolutionWidth/4), 0.0f, 0.0f, // 0
        (float)(3*resolutionWidth/4), (float)(resolutionWidth/4), 1.0f, 0.0f, // 1
        (float)(3*resolutionWidth/4), (float)(3*resolutionWidth/4), 1.0f, 1.0f, // 2
        (float)(resolutionWidth/4), (float)(3*resolutionWidth/4), 0.0f, 1.0f // 3 */

        /* 200.0f, 200.0f, 0.0f, 0.0f, // 0
        400.0f, 200.0f, 1.0f, 0.0f, // 1
        400.0f, 400.0f, 1.0f, 1.0f, // 2
        200.0f, 400.0f, 0.0f, 1.0f // 3 */

        /* -0.5f, -0.5f, 0.0f, 0.0f, // 0
        0.5f, -0.5f, 1.0f, 0.0f, // 1
        0.5f, 0.5f, 1.0f, 1.0f, // 2
        -0.5f, 0.5f, 0.0f, 1.0f // 3 */

        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
    };

    unsigned int indices[]{
        /* 0, 1, 2,
        2, 3, 0 */
        
        0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
        };

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), __FILE__, __LINE__);
    GLCall(glEnable(GL_BLEND), __FILE__, __LINE__);

    //buffer and array stuff

    int floatsPerVertex = 4;
    VertexArray va;
    //VertexBuffer vb(positions, 4 * floatsPerVertex * sizeof(float));
    VertexBuffer vb(positions, sizeof(positions));

    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 3);
    layout.Push(GL_FLOAT, 3);
    layout.Push(GL_FLOAT, 2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 18);

    //time stuff
    float rotation = 0.0f;
	double prevTime = glfwGetTime();


    //model view projection matrix

    shader.Bind();
    /* glm::mat4 proj = glm::ortho(0.0f, (float)resolutionWidth, 0.0f, (float)resolutionHeight, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
    glm::mat4 mvp = proj * view * model;
    shader.SetUniformMat4f("u_MVP", mvp); */

    //texture stuff, cpp logo
    Texture texture("res/img/brick.png");
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

    //imgui stuff
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    //change font to google font
    io.Fonts->AddFontFromFileTTF("res/fonts/kellyFont/KellySlab-Regular.ttf", 16.0f);

    //imgui variables
    static float rotationAngle = 0.0f;
    static int counter = 0;
    bool timed = true;
    //end imgui stuff

    //timed rotation stuff
        double crntTime = glfwGetTime();

        //std::cout << crntTime-prevTime << "\n";

		if (crntTime - prevTime >= 1 / 60)
		{
			//rotation += 0.5f;
            rotation -= 2.0f;
			prevTime = crntTime;
		}

		// Initializes matrices so they are not the null matrix
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

    // Assigns different transformations to each matrix
	view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
	proj = glm::perspective(glm::radians(45.0f), ((float)mode->width/(float)mode->height), 0.1f, 100.0f);
    glm::vec3 modelTranslation(0.0f, 0.0f, 0.0f);

    //setup engine for playing sound
    Sound sndEngine;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //translate and rotate model

        //checkbox option
        if(timed)
        {
            //rotates each frame
            model = glm::translate(model, modelTranslation);
            //timed rotation option
            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else
        {
            //translates based on variable
            model = glm::translate(glm::mat4(1.0f), modelTranslation);
            //untimed slider rotation
            model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        }

        //calculate mvp
        glm::mat4 mvp = proj * view * model;
        shader.SetUniformMat4f("u_MVP", mvp);

        //test
        shader.Bind();

        //get window resolution from GLFW
        glfwGetWindowSize(window, &resolutionWidth, &resolutionHeight);
        shader.SetUniform2f("u_resolution", resolutionWidth, resolutionHeight);
        //glm::mat4 proj = glm::ortho(0.0f, (float)resolutionWidth, 0.0f, (float)resolutionHeight, -1.0f, 1.0f);

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

        //imgui options
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Timed rotation or nah?", &timed);
            if(!timed) ImGui::SliderFloat("Rotation Angle", &rotationAngle, 0.0f, 100.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat3("Translation Test", &modelTranslation.x, -1.0f, 1.0f);
            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        

        //imgui rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //victor gordon youtube, uncomment next line when done with other vertex buffer info
    //glDeleteTextures(1, &texture);

    //end of temp scope to prevent errors
    }

    //imgui Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
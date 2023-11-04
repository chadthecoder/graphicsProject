//glew and glfw includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//C and C++ std lib includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <cmath>

//glm includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

//imgui includes
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
//#include <imgui/backends/imgui_impl_opengl3_loader.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "Errors.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Sound.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "RenderAPI.hpp"
#include "Vertex.hpp"

bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos)
{
    // (1) ALWAYS forward mouse data to ImGui! This is automatic with default backends. With your own backend:
    //ImGuiIO& io = ImGui::GetIO();

    // (2) ONLY forward mouse data to your underlying app/game.
    //if (!io.WantCaptureMouse) std::cout << xPos << " : " << yPos << "\n";
    //my_game->HandleMouseData(...);
}

static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    
    
    // (1) ALWAYS forward mouse data to ImGui! This is automatic with default backends. With your own backend:
    /* ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, action); */

    // (2) ONLY forward mouse data to your underlying app/game.
    //if (!io.WantCaptureMouse) std::cout << button << " : " << action << " : " << mods << "\n";
    //my_game->HandleMouseData(...);
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
    //window = glfwCreateWindow(mode->width, mode->height, "Hello World", glfwGetPrimaryMonitor(), NULL);
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
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
    //std::cout << glGetString(GL_VERSION) << "\n";

    //temp scope to prevent errors
    {

    //get shader from text

    //Shader shader("res/shaders/Basic.shader");
    //shader.Bind();

    //positions and indices

    std::vector<float> vertices {
        -0.5f, -0.5f, 0.0f,    0.83f, 0.70f, 0.44f,     0.0f, 0.0f, // 0
        0.5f, -0.5f, 0.0f,     0.83f, 0.70f, 0.44f,     1.0f, 0.0f, // 1
        0.5f, 0.5f, 0.0f,      0.83f, 0.70f, 0.44f,     1.0f, 1.0f, // 2
        -0.5f, 0.5f, 0.0f,     0.92f, 0.86f, 0.76f,     0.0f, 1.0f // 3
    };

    float incBy = 1.0f;

/*     std::vector<float> verticesPyramid {

        0.0f, 0.5f,  1.0f,     0.83f, 0.70f, 0.44f,	    0.0f, 0.0f,
	    0.0f, 0.5f, 0.0f,     0.83f, 0.70f, 0.44f,	    5.0f, 0.0f,
	    1.0f, 0.5f, 0.0f,     0.83f, 0.70f, 0.44f,	    0.0f, 0.0f,
	    1.0f, 0.5f,  1.0f,     0.83f, 0.70f, 0.44f,	    5.0f, 0.0f,
	    0.5f, 1.0f,  0.5f,     0.92f, 0.86f, 0.76f,	    2.5f, 5.0f,

        0.0f+incBy, 0.5f,  1.0f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	    0.0f+incBy, 0.5f, 0.0f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	    1.0f+incBy, 0.5f, 0.0f,     0.83f, 0.70f, 0.44f,	    0.0f, 0.0f,
	    1.0f+incBy, 0.5f,  1.0f,     0.83f, 0.70f, 0.44f,	    5.0f, 0.0f,
	    0.5f+incBy, 1.0f,  0.5f,     0.92f, 0.86f, 0.76f,	    2.5f, 5.0f
    }; */


    std::vector<unsigned int> indices {
        0, 1, 2,
        2, 3, 0 };

    std::vector<unsigned int> indicesPyramid {        
        0, 1, 2,
	    0, 2, 3,
	    0, 1, 4,
	    1, 2, 4,
	    2, 3, 4,
	    3, 0, 4,

        0, 1, 2,
	    0, 2, 3,
	    0, 1, 4,
	    1, 2, 4,
	    2, 3, 4,
	    3, 0, 4

        /* 5, 6, 7,
	    5, 7, 8,
	    5, 6, 9,
	    6, 7, 9,
	    7, 8, 9,
	    8, 5, 9 */
        };

        std::vector<unsigned int> indicesCube {        
        /* 4, 5, 6,
        6, 5, 7,
        0, 4, 5,
        4, 5, 1,
        0, 1, 2,
        1, 2, 3,
        7, 6, 2,
        6, 2, 3,
        4, 7, 3,
        7, 3, 0,
        5, 6, 2,
        6, 2, 1 */

        4, 5, 6,
        4, 6, 7,
        1, 5, 4,
        1, 4, 0,
        1, 0, 3,
        1, 3, 2,
        3, 7, 6,
        3, 6, 2,
        0, 4, 7,
        0, 7, 3,
        2, 6, 5,
        2, 5, 1

        /* 4, 5, 6,
        4, 6, 7,
        1, 5, 4,
        1, 4, 0,
        1, 0, 3,
        1, 3, 2,
        3, 7, 6,
        3, 6, 2,
        0, 4, 7,
        0, 7, 3,
        2, 6, 5,
        2, 5, 1 */
        };

        //changes the second half of the indices to be the same pattern but for the new vertices
        int stride = indicesPyramid.size()/2;
        //std::cout << "Stride Pyramid: " << stride << "\n";
        for(int i=stride; i<(stride+stride); i++)
        {
            //std::cout << "Index " << i << " is " << indicesPyramid[i] << "\n";
            indicesPyramid[i] = (indicesPyramid[i]+5);
            //std::cout << "Index " << i << " is now " << indicesPyramid[i] << "\n";
        }

        //changes the second half of the indices to be the same pattern but for the new vertices
        const unsigned int numCube = 20; //memory leak causes less to be able to be drawn w/o creating a segfault?
        const unsigned int vertPerCube = 8;
        const unsigned int numIndexPerCube = 36;
        const unsigned int strideC = numIndexPerCube;
        //std::cout << "Stride Cube: " << strideC << "\n";

        //add indices for cubes
        for(unsigned int i=strideC; i<(strideC * numCube); i++)
        {
            //std::cout << "Index " << i << " is " << indicesCube[i] << "\n";
            indicesCube.push_back(indicesCube[i-numIndexPerCube]+vertPerCube);
            //std::cout << "Index " << i << " is now " << indicesCube[i] << "\n";
        }

    //time stuff
    float rotation = 0.0f;
	double prevTime = glfwGetTime();

    //texture stuff, cpp logo
    //Texture texture("res/img/brick.png", "3D");
    //texture.Bind();
    
    Renderer renderer("3D", sizeof(openglStuff::Vertex) * 1000, indicesCube.data(),
        indicesCube.size(), "res/shaders/Basic.shader", "res/img/brick.png");
    
    //renderer.SetUniform1i("u_Texture", 0);

    //create pyramids
    auto q0 = renderer.Pyramid(0.0f, 0.0f, 0.0f);
    auto q1 = renderer.Pyramid(1.0f, 0.0f, 0.0f);
    openglStuff::Vertex verticesPyramid[10];
    memcpy(verticesPyramid, q0.data(), q0.size()*sizeof(openglStuff::Vertex));
    memcpy(verticesPyramid+q0.size(), q1.data(), q1.size()*sizeof(openglStuff::Vertex));

    //create vertex buffer for numCubes, can change Cube function to change color and texture of cubes
    openglStuff::Vertex verticesCube[vertPerCube*numCube];
    for(int i = 0; i < numCube; i++)
    {
        auto q = renderer.Cube(0.0f, (float)i, -(float)i);
        memcpy(verticesCube+(q.size()*i), q.data(), q.size()*sizeof(openglStuff::Vertex));
         std::cout << "sizey: " << verticesCube+(q.size()*i) << " : " << i << " : "
            << q.size() << " : " << verticesCube << " : " << verticesCube+0x8 << "\n"; 
    }

    /* auto q2 = renderer.Cube(0.0f, 0.0f, 0.0f);
    auto q3 = renderer.Cube(1.0f, 0.0f, 0.0f);
    auto q4 = renderer.Cube(2.0f, 0.0f, 0.0f);
    auto q5 = renderer.Cube(3.0f, 0.0f, 0.0f);
    auto q6 = renderer.Cube(4.0f, 0.0f, 0.0f);
    
    //openglStuff::Vertex verticesCube[16];
    memcpy(verticesCube, q2.data(), q2.size()*sizeof(openglStuff::Vertex));
    memcpy(verticesCube+q2.size(), q3.data(), q3.size()*sizeof(openglStuff::Vertex));
    memcpy(verticesCube+q2.size()+q3.size(), q4.data(), q4.size()*sizeof(openglStuff::Vertex));
    memcpy(verticesCube+q2.size()+q3.size()+q4.size(), q5.data(), q5.size()*sizeof(openglStuff::Vertex));
    memcpy(verticesCube+q2.size()+q3.size()+q4.size()+q5.size(), q6.data(), q6.size()*sizeof(openglStuff::Vertex)); */

    //std::cout << q0.size() << "\n";

    //imgui stuff
    // Setup Dear ImGui context
    /* IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version); */

    //change font to google font
    //io.Fonts->AddFontFromFileTTF("res/fonts/kellyFont/KellySlab-Regular.ttf", 16.0f);

    //imgui variables
    static float rotationAngle1 = 0.0f;
    static float rotationAngle2 = 45.0f;
    static int counter = 0;
    bool timed = true;
    //end imgui stuff

    //timed rotation stuff
    double crntTime = glfwGetTime();

    //3d victor gordon matrices
	// Initializes matrices so they are not the null matrix
	glm::mat4 model1 = glm::mat4(1.0f);
    glm::mat4 model2 = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
    glm::mat4 mvp;

    // Assigns different transformations to each matrix
	view = glm::translate(view, glm::vec3(0.0f, -0.5f, -3.0f));
	proj = glm::perspective(glm::radians(45.0f), ((float)mode->width/(float)mode->height), 0.1f, 100.0f);
    glm::vec3 modelTranslation1(-0.5f, 0.0f, 0.0f);
    glm::vec3 modelTranslation2(0.5f, 0.0f, 0.0f);

    //setup engine for playing sound
    Sound sndEngine;

    //setup camera
    Camera camera(mode->width, mode->height, glm::vec3(0.8f, 0.8f, 3.0f));
    

    //renderer.Bind();

    clock_t current_ticks, delta_ticks;
clock_t fps = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        current_ticks = clock();

       

        

        /* Render here */
        renderer.Clear();
        //shader.Bind();

        //get inputs and set camera shader
        //if (!io.WantCaptureMouse) camera.MnKInputs(window);
        camera.MnKInputs(window);
        camera.Matrix(45.0f, 0.1f, 100.f, renderer.GetShader(), "u_camMatrix");
        
        /* ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame(); */

        //draw
        //std::cout << "size: " << sizeof(verticesCube)/sizeof(openglStuff::Vertex) << "\n";
        //std::cout << "size: " << verticesCube << "\n";
        std::cout << "size: " << sizeof(float) << "\n";
        renderer.Draw(verticesCube, sizeof(verticesCube) * sizeof(float));
        //std::cout << "size: " << sizeof(float) << "\n";
        

        //imgui options
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        /* {
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("Translate and rotate two identical pyramids at will!");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Timed rotation or nah?", &timed);
            if(!timed)
            {
                ImGui::SliderFloat("Model 1 Rotation Angle", &rotationAngle1, 0.0f, 360.0f);
                ImGui::SliderFloat("Model 2 Rotation Angle", &rotationAngle2, 0.0f, 360.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            }
            ImGui::SliderFloat3("Translate Model 1", &modelTranslation1.x, -1.0f, 1.0f);
            ImGui::SliderFloat3("Translate Model 2", &modelTranslation2.x, -1.0f, 1.0f);
            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        

        //imgui rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
    if(delta_ticks > 0)
        fps = CLOCKS_PER_SEC / delta_ticks;
    //std::cout << "fps: " << fps << std::endl;
    }

    //victor gordon youtube, uncomment next line when done with other vertex buffer info
    //glDeleteTextures(1, &texture);
    //shader.Unbind();
    //end of temp scope to prevent errors
    }

    //imgui Cleanup
    /* ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(); */

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
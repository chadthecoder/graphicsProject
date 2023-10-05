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

bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos)
{
    //std::cout << xPos << " : " << yPos << "\n";
}

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &filepath)
{

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr), __FILE__, __LINE__);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
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

    std::cout << glGetString(GL_VERSION) << "\n";

    // float move = -0.49f;
    // int frame = 1;

    //temp scope to prevent errors
    {

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

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao), __FILE__, __LINE__);
    GLCall(glBindVertexArray(vao), __FILE__, __LINE__);

    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");

    std::cout << "VERTEX" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << source.FragmentSource << std::endl;

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(shader), __FILE__, __LINE__);

    float red = 0.6f, green = 0.0f, blue = 1.0f, alpha = 1.0f;
    //  change colors following the cherno video
    float incRed = -0.05f, incGreen = 0.05f, incBlue = -0.05f;
    bool inc = true;
    int colorLocation;
    colorLocation = GLCall2(glGetUniformLocation(shader, "u_Color"), __FILE__, __LINE__);
    //  ASSERT(colorLocation != -1);

    // gScaleLocation = glGetUniformLocation(shader, gScale);
    unsigned int gScaleLocation;
    gScaleLocation = glGetUniformLocation(shader, "u_gScale");
    static float Scale = 0.0f;
    static float scaleDelta = 0.05f;

    unsigned int incLocation;
    incLocation = glGetUniformLocation(shader, "u_incLoc");
    static float incLoc = 0.0f;
    static float incDelta = 0.1f;

    double mouseX, mouseY;
    unsigned int mouseLocation;
    mouseLocation = glGetUniformLocation(shader, "u_mouse");

    int resolutionWidth, resolutionHeight;
    unsigned int resolutionLocation;
    resolutionLocation = glGetUniformLocation(shader, "u_resolution");

    // int location = glGetUniformLocation(shader, "u_Green");
    // glUniform1f(location, green); // red, green, blue, alpha);

    //test
    GLCall(glBindVertexArray(0), __FILE__, __LINE__);
    GLCall(glUseProgram(0), __FILE__, __LINE__);
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,  0), __FILE__, __LINE__);
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0), __FILE__, __LINE__);

    //texture, following victor gordon youtube, also has line in end to need uncomment, need to change buffers to add rest of code and in shader
    /* int imgWidth, imgHeight, numColCh;
    unsigned char* bytes = stbi_load("../res/img/cpp.png", &imgWidth, &imgHeight, &numColCh, 0);
    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0); */

    //ma_result sndResult;
    //ma_engine sndEngine;

    /* sndResult = ma_engine_init(NULL, &sndEngine);
    if (sndResult != MA_SUCCESS)
    {
        printf("Failed to initialize audio engine.");
        return -1;
    } */

    //ma_engine_play_sound(&sndEngine, "res/snd/sound.mp3", NULL);    

    Sound sndEngine;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT), __FILE__, __LINE__);

        //test
        GLCall(glUseProgram(shader), __FILE__, __LINE__);

        GLCall(glUniform4f(colorLocation, red, green, blue, alpha), __FILE__, __LINE__);

        //get cursor position from GLFW
        glfwGetCursorPos(window, &mouseX, &mouseY);
        //normalize variables, should be done in shader, need to pass resolution as uniform first
        //mouseX /= 800;
        //mouseY /= 600;
        //cout variables
        //std::cout << mouseX << " : " << mouseY << "\n";
        //set shader mouse positions
        GLCall(glUniform2f(mouseLocation, (float)mouseX, (float)mouseY), __FILE__, __LINE__);

        //get window resolution from GLFW
        glfwGetWindowSize(window, &resolutionWidth, &resolutionHeight);
        //normalize variables, should be done in shader, need to pass resolution as uniform first
        //mouseX /= 800;
        //mouseY /= 600;
        //cout variables
        //std::cout << resolutionWidth << " : " << resolutionHeight << "\n";
        //set shader window resolution
        GLCall(glUniform2f(resolutionLocation, (float)resolutionWidth, (float)resolutionHeight), __FILE__, __LINE__);
        
        
        va.Bind();
        ib.Bind();

        // glUniform1f(location2, red, green, blue, alpha);

        Scale += scaleDelta;
        //std::cout << "\n\n\n\n\n";
        if(Scale <= -1.0f) std::cout << "\n\n\n\n\n\n\n\n\n hi \n\n\n\n\n\n\n\n"; //ma_engine_play_sound(&sndEngine, "res/snd/sound.mp3", NULL);
        //std::cout <<  Scale << "\n\n\n\n\n";
        if ((Scale >= 1.0f) || (Scale <= -1.0f))
        {
            scaleDelta *= -1.0f;
            //ma_engine_play_sound(&sndEngine, "res/snd/sound.mp3", NULL);
            sndEngine.Play("res/snd/sound.mp3");
        }
        GLCall(glUniform1f(gScaleLocation, Scale), __FILE__, __LINE__);

        incLoc += incDelta;
        if ((incLoc >= 1.0f) || (incLoc <= -1.0f))
        {
            incDelta *= -1.0f;
        }

        GLCall(glUniform1f(incLocation, incLoc), __FILE__, __LINE__);

        //GLClearError();
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr), __FILE__, __LINE__);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        //ASSERT(GLLogCall());

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
        //std::cout << "Red Value: " << red << "\n";

        /* if (inc == true)
        {
            if (green >= 1.0f)
            {
                inc = false;
                green -= 0.05f;
            }
            green += 0.05f;
            std::cout << green << " inc\n";
        }
        else
        {
            if (green <= 0.0f)
            {
                inc = true;
                green += 0.05f;
            }
            green -= 0.05f;
            std::cout << green << " dec\n";
        }
 */
        // using legacy opengl to draw a triangle with animation
        /*         if (move <= 0.49f)
                {
                    if ((frame % 2) == 0)
                    {
                        move += .01;
                    }
                }

                frame++;

                std::cout << "Frame: " << frame << " Move: " << move << "Ans: " << (frame % 10) << "\n";

                glBegin(GL_TRIANGLES);
                glVertex2f(-0.5f, -0.5f);
                glVertex2f(0.0f, move); // 0.5f
                glVertex2f(0.5f, -0.5f);
                glEnd(); */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //victor gordon youtube, uncomment next line when done with other vertex buffer info
    //glDeleteTextures(1, &texture);
    
    GLCall(glDeleteProgram(shader), __FILE__, __LINE__);

    //ma_engine_uninit(&sndEngine);

    //end of temp scope to prevent errors
    }

    glfwTerminate();
    return 0;
}
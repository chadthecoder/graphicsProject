#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <csignal>

#define ASSERT(x){ if(!x)\
raise(SIGTRAP); } //__builtin_debugtrap(); //instead of raise(SIGTRAP) for windows

static void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

static bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "GL Error(Hex: "
            << std::hex
            << error
            << ")\nError in File: "
            << __FILE__
            << "\nError in Line: "
            <<  __LINE__
            << "\nError in Function: "
            << function
            << "\n\n";
        return false;
    }
    return true;
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
    glShaderSource(id, 1, &src, nullptr);
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

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1366, 768, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

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

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");

    std::cout << "VERTEX" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << source.FragmentSource << std::endl;

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(shader));

    float red = 0.6f, green = 0.0f, blue = 1.0f, alpha = 1.0f;
    //  change colors following the cherno video
    float incRed = -0.05f, incGreen = 0.05f;
    bool inc = true;
    int location;
    location = glGetUniformLocation(shader, "u_Color");
    //  ASSERT(location != -1);

    // gScaleLocation = glGetUniformLocation(shader, gScale);
    unsigned int gScaleLocation;
    gScaleLocation = glGetUniformLocation(shader, "u_gScale");
    static float Scale = 0.0f;
    static float scaleDelta = 0.05f;

    unsigned int incLocation;
    incLocation = glGetUniformLocation(shader, "u_incLoc");
    static float incLoc = 0.0f;
    static float incDelta = 0.1f;

    // int location = glGetUniformLocation(shader, "u_Green");
    // glUniform1f(location, green); // red, green, blue, alpha);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUniform4f(location, red, green, blue, alpha));
        // glUniform1f(location2, red, green, blue, alpha);

        Scale += scaleDelta;
        if ((Scale >= 1.0f) || (Scale <= -1.0f))
        {
            scaleDelta *= -1.0f;
        }
        GLCall(glUniform1f(gScaleLocation, Scale));

        incLoc += incDelta;
        if ((incLoc >= 1.0f) || (incLoc <= -1.0f))
        {
            incDelta *= -1.0f;
        }

        GLCall(glUniform1f(incLocation, incLoc));

        //GLClearError();
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        //ASSERT(GLLogCall());

        //change green value
        if (green > 1.0f)
        {
            incGreen = -0.05f;
            std::cout << "green dec\n";
        }
        else if (green < 0.0f)
        {
            incGreen = 0.05f;
            std::cout << "green inc\n";
        }

        green += incGreen;
        std::cout << "Green Value: " << green << "\n";

        //change red color
        if (red < 0.0f)
        {
            incRed = 0.05f;
            std::cout << "red inc\n";
        }
        else if (red > 1.0f)
        {
            incRed = -0.05f;
            std::cout << "red dec\n";
        }

        red += incRed;
        std::cout << "Red Value: " << red << "\n";

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

    GLCall(glDeleteProgram(shader));

    glfwTerminate();
    return 0;
}
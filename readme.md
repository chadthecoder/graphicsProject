# Graphics Project with SDL2, ASIO, OpenGL using GLEW, and GLM

This is a graphics project written in C++ that utilizes SDL2 and OpenGL using GLEW and GLM libraries to create graphical applications. The project aims to provide a starting point for learning graphics programming in C++. The pong game has been moved to https://github.com/chadthecoder/NetworkPongGame as it is now its own project to work on using what I have learned while experimenting in this repo.

Here are two drawings I made to show how the cube should be rendered using my current plan.
![Alt text](readmeStuff/cube1.jpeg?raw=true "Cube1")
![Alt text](readmeStuff/cube2.jpeg?raw=true "Cube2")

## Prerequisites

Before you begin, ensure you have the following dependencies installed on your system:

- SDL2

- OpenGL

- GLEW

- GLM

- Makefile (for building)

## Getting Started

1. Clone this repository to your local machine:

   ```bash

   git clone https://github.com/yourusername/graphics-project.git

   cd graphics-project

   ```

2. Build the project using CMake:

   ```bash

   cd pingPong

   make lin (make win for Windows)

   ```

3. Run the compiled executable:

   ```bash

   make runLin (make runWin for Windows)

   ```

4. Clean the compiled executable (If needed):

   ```bash

   make cleanLin (make cleanWin for Windows)

   ```

## Project Structure

- `asioGraphicsNetwork/`: Contains a simple UDP file for multiplayer game later.

- `2dgameengine/`: Contains header files for your project.

- `imageTest/`: Contains imageTest for SDL2.

- `sdlGlewTest/`: Contains test of using SDL2 and GLEW together for learning.

- `webgl/`: Contains webgl test for learning.

## In Each Project Structure

- `linux/`: Contains linux .o files and binaries.

- `windows/`: Contains windows .o files and .exe files.

## Resources

Here are some resources to help you learn more about the libraries used in this project:

- [SDL2 Documentation](https://wiki.libsdl.org/)

- [OpenGL Documentation](https://www.opengl.org/documentation/)

- [GLFW Documentation](https://www.glfw.org/documentation.html)

- [GLEW Documentation](http://glew.sourceforge.net/)

- [GLM Documentation](https://glm.g-truc.net/0.9.9/index.html)

## Contributing

If you'd like to contribute to this project, feel free to submit pull requests or open issues.

Replace `"https://github.com/yourusername/graphics-project.git"` with the actual URL of your project's repository.

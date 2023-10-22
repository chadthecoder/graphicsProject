# graphicsProject

Graphics project using SDL2 and OPENGL with GLEW. Following multiple tutorials to learn how to code graphics in C++.

Meant to be cross platform for Windows and Linux. Only works on Windows right now.

# Resources:

pong icon by Icons8 (icons8.com)

Game Programming in C++ by Sanjay Madhav  
 https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2  
 https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx  
 https://stackoverflow.com/questions/708238/how-do-i-add-an-icon-to-a-mingw-gcc-compiled-executable

# install packages on ubunbtu

sudo apt-get install libglew-dev

if building glfw from source
must have doxygen and cmake installed for curent process for glfw build
"make buildDeps"
otherwise must install glfw using apt install on Debian, unsupported on non-Debian may work
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev

not using glad right now but maybe in future
git clone https://github.com/Dav1dde/glad.git
cd glad
cmake ./
make
sudo cp -a include /usr/local/

# Read Makefile in order to install on Linux

make lin
make runLin
make cleanLin

# Read Makefilw in order to install on Windows

make win
make runWin
make cleanWin

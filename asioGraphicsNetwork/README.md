# graphicsProject

Graphics project using SDL2 and OPENGL with GLEW. Following multiple tutorials to learn how to code graphics in C++.

Meant to be cross platform for Windows and Linux. Only works on Windows right now.

# Resources:

pong icon by Icons8 (icons8.com)

https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T

Game Programming in C++ by Sanjay Madhav  
 https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2  
 https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx  
 https://stackoverflow.com/questions/708238/how-do-i-add-an-icon-to-a-mingw-gcc-compiled-executable

# install packages on ubunbtu

sudo apt-get install libglew-dev
sudo apt install libsdl2-dev libsdl2-2.0-0 -y
sudo apt-get install libboost-all-dev
sudo apt-get install g++

# Read Makefilw in order to install on Linux

Currently has issue where binds up port 1024, find asio fix using https://stackoverflow.com/questions/34596638/boost-asio-so-reuseport ?

g++ server.cpp -o server
g++ client.cpp -o client

(on one terminal) ./server
(on another terminal) ./client 127.0.0.1

# Read Makefilw in order to install on Windows

unsupported so far

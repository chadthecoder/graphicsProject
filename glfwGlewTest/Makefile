cc = g++

programName = "openGL"

main = src/main.cpp

includes = -Iinclude/

# need to add to linksWin?
openGL = -lGLEW -lglfw -lGL 

miniaudioLinks = -lpthread -lm -ldl

linksWin = -lglew32 -lglfw3 -lgdi32 -lopengl32 -lmingw32

linksLin = $(openGL) $(miniaudioLinks)

includeDepsWin = -I "libsWin\glew\include" -I "libsWin\glfw\include"

includeDepsLin = -I "libsLin\glew\include" -I "libsLin\glfw\include"

linkingDepsWin = -L "libsWin\glew\lib\Release\Win32" -L "libsWin\glfw\lib-mingw"

linkingDepsLin = -L "libsLin\glew\lib\Release\Win32" -L "libsLin\glfw\lib-mingw"

libsWin = $(includeDepsWin) $(linkingDepsWin) $(linksWin)

libsLin = $(includeDepsLin) $(linkingDepsLin) $(linksLin)

dotOWin = windows/main.o windows/Game.o

dotOLin = bin/Links.o bin/Errors.o bin/VertexBuffer.o bin/IndexBuffer.o
dotOLin +=  bin/VertexBufferLayout.o bin/VertexArray.o bin/Shader.o
dotOLin += bin/Renderer.o bin/Texture.o bin/Sound.o bin/main.o

iconO = windows/windows.res

outputWin = -o "windows/Rocket League"

outputLin = -o "bin/$(programName)"

win: $(dotOWin)
	windres windows/windows.rc -O coff -o $(iconO)
	$(cc) $(outputWin) $(dotOWin) $(iconO) $(libsWin)

windows/main.o: $(main)
	$(cc) -c $(main) -o windows/main.o

windows/Game.o: Game.cpp
	$(cc) -c Game.cpp -o windows/Game.o

runWin:
	"windows/Rocket League"

lin: $(dotOLin)
	$(cc) $(outputLin) $(dotOLin) $(libsLin) 

bin/main.o: $(main)
	$(cc) $(includes) -c $(main) -o bin/main.o

bin/Errors.o: src/Errors.cpp
	$(cc) -c src/Errors.cpp -o bin/Errors.o

bin/VertexBuffer.o: src/VertexBuffer.cpp
	$(cc) -c src/VertexBuffer.cpp -o bin/VertexBuffer.o

bin/IndexBuffer.o: src/IndexBuffer.cpp
	$(cc) -c src/IndexBuffer.cpp -o bin/IndexBuffer.o

bin/VertexBufferLayout.o: src/VertexBufferLayout.cpp
	$(cc) -c src/VertexBufferLayout.cpp -o bin/VertexBufferLayout.o

bin/VertexArray.o: src/VertexArray.cpp
	$(cc) -c src/VertexArray.cpp -o bin/VertexArray.o

bin/Shader.o: src/Shader.cpp
	$(cc) -c src/Shader.cpp -o bin/Shader.o

bin/Renderer.o: src/Renderer.cpp
	$(cc) -c src/Renderer.cpp -o bin/Renderer.o

bin/Texture.o: src/Texture.cpp
	$(cc) -c src/Texture.cpp -o bin/Texture.o

bin/Sound.o: src/Sound.cpp
	$(cc) -c src/Sound.cpp -o bin/Sound.o

bin/Links.o: src/Links.cpp
	$(cc) $(includes) -c src/Links.cpp -o bin/Links.o

runLin:
	./bin/"$(programName)"

cleanWin:
	rm windows/*.o
	rm windows/*.exe

cleanLin:
	rm bin/*.o
	rm bin/"$(programName)"
cc = g++

main = main.cpp

includeDeps = -I "..\libs\glew\include" -I "..\libs\glfw\include" -I "..\libs\SDL2\i686-w64-mingw32\include"

linkingDeps = -L "..\libs\glew\lib\Release\Win32" -L "..\libs\glfw\lib-mingw" -L "..\libs\SDL2\i686-w64-mingw32\lib"

links = -lglew32 -lglfw3 -lgdi32 -lopengl32 -lmingw32 -lSDL2main -lSDL2

libs = $(includeDeps) $(linkingDeps) $(links)

output = -o "windows/Rocket League"

dotO = windows/main.o windows/Game.o

iconO = windows/windows.res

win: $(dotO)
	windres windows/windows.rc -O coff -o $(iconO)
	$(cc) $(output) $(dotO) $(iconO) $(libs)

windows/main.o: main.cpp
	$(cc) -c main.cpp -o windows/main.o

windows/Game.o: Game.cpp
	$(cc) -c Game.cpp -o windows/Game.o

run:
	"windows/Rocket League"

clean:
	rm windows/*.o
	rm windows/*.exe

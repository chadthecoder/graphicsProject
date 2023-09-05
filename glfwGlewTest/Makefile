cc = g++

main = main.cpp

# need to add to linksWin?
openGL = -lGLEW -lglfw -lGL 

linksWin = -lglew32 -lglfw3 -lgdi32 -lopengl32 -lmingw32

linksLin = $(openGL)

includeDepsWin = -I "libsWin\glew\include" -I "libsWin\glfw\include"

includeDepsLin = -I "libsLin\glew\include" -I "libsLin\glfw\include"

linkingDepsWin = -L "libsWin\glew\lib\Release\Win32" -L "libsWin\glfw\lib-mingw"

linkingDepsLin = -L "libsLin\glew\lib\Release\Win32" -L "libsLin\glfw\lib-mingw"

libsWin = $(includeDepsWin) $(linkingDepsWin) $(linksWin)

libsLin = $(includeDepsLin) $(linkingDepsLin) $(linksLin)

dotOWin = windows/main.o windows/Game.o

dotOLin = linux/main.o #linux/Game.o

iconO = windows/windows.res

outputWin = -o "windows/Rocket League"

outputLin = -o "linux/Rocket League"

win: $(dotOWin)
	windres windows/windows.rc -O coff -o $(iconO)
	$(cc) $(outputWin) $(dotOWin) $(iconO) $(libsWin)

windows/main.o: main.cpp
	$(cc) -c main.cpp -o windows/main.o

windows/Game.o: Game.cpp
	$(cc) -c Game.cpp -o windows/Game.o

runWin:
	"windows/Rocket League"

lin: $(dotOLin)
	$(cc) $(outputLin) $(dotOLin) $(libsLin)

linux/main.o: main.cpp
	$(cc) -c main.cpp -o linux/main.o

#linux/Game.o: Game.cpp
#	$(cc) -c Game.cpp -o linux/Game.o

runLin:
	./linux/"Rocket League"

cleanWin:
	rm windows/*.o
	rm windows/*.exe

cleanLin:
	rm linux/*.o
	rm linux/"Rocket League"
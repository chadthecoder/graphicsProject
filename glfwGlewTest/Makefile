cc = g++-10

programName = openGL

main = src/main.cpp

includes = -Iinclude/ -Iinclude/glfw/include

#sudo apt-get install doxygen, must have doxygen and cmake installed for curent process
BUILDDEPS = mkdir include/glfw/build;
BUILDDEPS += cmake -S include/glfw -B include/glfw/build -D BUILD_SHARED_LIBS=ON;
BUILDDEPS += cd include/glfw/build;
BUILDDEPS += make;

IMGUI_DIR = include/imgui

# need to add to linksWin?
openGL = -lGLEW -lglfw -lGL 

miniaudioLinks = -lpthread -lm -ldl


linksLin = $(openGL) $(miniaudioLinks)


includeDepsLin = -I "libsLin\glew\include" -I "libsLin\glfw\include" -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

#linkingDepsLin = -L "libsLin\glew\lib\Release\Win32" -L "libsLin\glfw\lib-mingw"
#-L "include\glfw\build\src"
linkingDepsLin = -L./include/glfw/build/src

libsLin = $(includeDepsLin) $(linkingDepsLin) $(linksLin)

SOURCES = src/main.cpp src/Links.cpp src/Errors.cpp src/VertexBuffer.cpp src/IndexBuffer.cpp
SOURCES += src/VertexBufferLayout.cpp src/VertexArray.cpp src/Shader.cpp
SOURCES += src/Texture.cpp src/Renderer.cpp src/Sound.cpp src/Camera.cpp src/RenderAPI.cpp
#SOURCES += src/Object.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp
SOURCES += $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

OBJS = $(SOURCES:src/%.cpp=bin/%.o)

#OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

outputLin = -o "bin/$(programName)"

bin/%.o:src/%.cpp
	$(cc) $(includes) $(libsLin) -c -o $@ $<

bin/%.o:$(IMGUI_DIR)/%.cpp
	$(cc) $(libsLin) -c -o $@ $<

bin/%.o:$(IMGUI_DIR)/backends/%.cpp
	$(cc) $(libsLin) -c -o $@ $<

buildDeps:
	echo $(BUILDDEPS)

lin: bin/$(programName)
	@echo Build complete for Linux

bin/$(programName): $(OBJS)
	$(cc) $(includes) -o $@ $^ $(libsLin)

runLin:
	LD_LIBRARY_PATH=include/glfw/build/src ./bin/"$(programName)"

cleanLin:
	rm bin/*.o
	rm bin/"$(programName)"
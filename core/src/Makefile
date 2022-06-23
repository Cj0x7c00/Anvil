CFLAGS = -std=c++17 -w    							  # compiler flags
LDFLAGS = -lglfw -lvulkan    						  # libraries
LIMGUI = include/imgui/libimgui.a					  # Dear ImGui
LIMGUIBACKENDS = include/imgui/backends/libbackends.a # Dear ImGui Backends
PATH_TO_SHADERS = shaders/
BUILD_PATH = ../AppleBundle/AnvilEngine.app/Contents/MacOS/

run: *.cpp *.hpp 
	$(info ========= Build Started =========)
	clang++ $(CFLAGS) -o main *.cpp $(LDFLAGS) $(LIMGUI) $(LIMGUIBACKENDS)
	make shaders 
	make test 
	make clean

.PHONY: test clean

shaders: main
	$(info ======= Compiling shaders =======)
	-$(PATH_TO_SHADERS)glslc $(PATH_TO_SHADERS)shader.frag -o $(PATH_TO_SHADERS)fshader.spv
	-$(PATH_TO_SHADERS)glslc $(PATH_TO_SHADERS)shader.vert -o $(PATH_TO_SHADERS)vshader.spv
	

test: main
	$(info =========    Running    =========)   
	-./main

clean: 
	rm main
	rm $(PATH_TO_SHADERS)*.spv
	
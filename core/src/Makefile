CFLAGS = -std=c++17 -w -O2  							  # compiler flags
LDFLAGS = -lglfw -lvulkan                                 # libraries

SRC_FILES = \
./anvApplication.cpp \
./Layer/anvLayer.cpp \
./Layer/anvLayerStack.cpp \
./anvpch.cpp \
./Vulkan/Model/anvModel.cpp \
./Vulkan/anvDevice.cpp \
./Vulkan/anvPipeline.cpp \
./Vulkan/anvRenderer.cpp \
./Vulkan/anvSwapChain.cpp \
./Vulkan/simpleRenderSystem.cpp \
./Util/Time/anvTimestep.cpp \
./Window/window_manager.cpp \
./sandbox.cpp \
./sandboxApp.cpp \

PATH_TO_SHADERS = shaders/
BUILD_PATH = ../../AppleBundle/AnvilEngine.app/Contents/MacOS/

run: *.cpp *.hpp 											
	$(info ========= Build Started =========)
	clang++ $(CFLAGS) $(SRC_FILES) -o main.bin $(LDFLAGS) -O2
	make shaders 
	make test 
	make clean

.PHONY: test clean

shaders: main.bin
	$(info ======= Compiling shaders =======)
	-$(PATH_TO_SHADERS)glslc $(PATH_TO_SHADERS)shader.frag -o $(PATH_TO_SHADERS)fshader.spv
	-$(PATH_TO_SHADERS)glslc $(PATH_TO_SHADERS)shader.vert -o $(PATH_TO_SHADERS)vshader.spv
	
test: 
	$(info =========    Running    =========)   
	-./main.bin

clean: 
	rm main.bin
	rm shaders/*.spv
	
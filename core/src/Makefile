CFLAGS = -std=c++17 -w # compiler flags
LDFLAGS = -lglfw -lvulkan # libraries
LIMGUI = include/imgui/libimgui.a
LIMGUIBACKENDS = include/imgui/backends/libbackends.a
a.out: *.cpp *.hpp 
	$(info ========= Build started =========)
	clang++ $(CFLAGS) -o main *.cpp $(LDFLAGS) $(LIMGUI) $(LIMGUIBACKENDS)
	make test
	make clean

.PHONY: test clean

test: main
	./main

clean: 
	rm main
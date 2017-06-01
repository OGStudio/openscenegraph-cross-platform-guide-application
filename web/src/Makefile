CC = ~/emsdk-portable/emscripten/1.37.9/em++
all: main.cpp
	$(CC) main.cpp -O2 -s USE_SDL=2 --preload-file box.osgt -o main.html

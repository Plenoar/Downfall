
build:
	gcc -I C:/SDL3/x86_64-w64-mingw32/include -L C:/SDL3/x86_64-w64-mingw32/lib main.c game_functions.c game_physics.c camera.c -lSDL3  -o build/newbuild.exe

run:
	./newbuild.exe




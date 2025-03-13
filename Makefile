
compile:
	gcc -I C:/SDL3/x86_64-w64-mingw32/include -L C:/SDL3/x86_64-w64-mingw32/lib src/main.c src/game_functions.c src/game_physics.c src/camera.c -lSDL3  -o build/newbuild.exe

run:
	./build/newbuild.exe






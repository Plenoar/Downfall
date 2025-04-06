build:
	gcc main.c camera.c processinput.c processuser.c world.c \
	    -I C:/libraries/SDL3-3.2.8/x86_64-w64-mingw32/include \
	    -L C:/libraries/SDL3-3.2.8/x86_64-w64-mingw32/lib -lSDL3 \
	    -o main.exe
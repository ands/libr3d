CC = clang
CFLAGS = -Wall -c `pkg-config --cflags sdl2` -I../../libs/r3d/ -I../../libs/r3dfb-sdl/ -I../meshes/ -I../textures/ -Wno-missing-braces
LDFLAGS = `pkg-config --libs sdl2` -lm
EXE = example-sdl

all: $(EXE)

$(EXE): main.o r3d.o r3dfb.o
	$(CC) $(LDFLAGS) main.o r3d.o r3dfb.o -o $@

main.o: main.c
	$(CC) $(CFLAGS) $< -o $@
	
r3d.o: ../../libs/r3d/r3d.c
	$(CC) $(CFLAGS) $< -o $@

r3dfb.o: ../../libs/r3dfb-sdl/r3dfb.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)

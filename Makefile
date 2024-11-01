CXX	:= g++
CXXFLAGS	:= -Iinclude -O2
LDFLAGS	:= `sdl2-config --libs --cflags` -lGLEW -lGL
OBJS	:= build/main.o build/Background.o build/Ball.o build/Bitmap.o build/Drawable.o build/Global.o build/Line.o build/Shader.o build/Skeleton.o build/Texture.o

all: magicz
.PHONY: all

build:
	mkdir $@

build/main.o:	main.cc build
	$(CXX) -c $(CXXFLAGS) -o $@ $<

build/%.o: src/%.cc build
	$(CXX) -c $(CXXFLAGS) -o $@ $<

magicz:	$(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm build/*.o
.PHONY: clean

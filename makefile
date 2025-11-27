all: build run

run:
	./build/output

build: clean
	mkdir -p build
	gcc src/model/*.c src/controller/*.c src/view/*.c src/main.c \
	-Isrc/view/headers -Isrc/model/headers -Isrc/controller/headers \
	-o build/output \
	-lraylib -lGL -lm -ldl -lpthread -lrt -lX11 -lXrandr -lXi

clean:
	rm -rf build

val: build
	valgrind ./build/output


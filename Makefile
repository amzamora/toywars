NAME = toywars
SRCS = src/main.c src/game.c src/ui/ui.c src/screens/title_screen.c deps/dynamic_string/dynamic_string.c

all: $(SRCS) deps/raylib/build/raylib/libraylib.a
	gcc $(SRCS) -o $(NAME) -I deps -I deps/dynamic_string -I deps/raylib/src deps/raylib/build/raylib/libraylib.a -ldl  -lpthread -lm $(FLAGS)

deps/raylib/build/raylib/libraylib.a: deps/raylib/src/*.c deps/raylib/src/*.h
	cd deps/raylib && \
	rm -rf build && \
	mkdir build && \
	cd build && \
	cmake -DBUILD_SHARED_LIBS=OFF .. && \
	make

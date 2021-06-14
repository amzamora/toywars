NAME = toywars
SRCS = src/main.c
FLAGS = -Wall -Wextra -Werror

all: $(SRCS) deps/raylib/build/raylib/libraylib.a
	gcc $(SRCS) -o $(NAME) -I deps/raylib/src deps/raylib/build/raylib/libraylib.a -ldl  -lpthread -lm $(FLAGS)

deps/raylib/build/raylib/libraylib.a: deps/raylib/src/*.c deps/raylib/src/*.h
	cd deps/raylib && \
	rm -rf build && \
	mkdir build && \
	cd build && \
	cmake -DBUILD_SHARED_LIBS=OFF .. && \
	make

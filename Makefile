all: raylib
	gcc src/main.c -o toywars -I deps/raylib/src deps/raylib/libraylib.a -ldl  -lpthread -lm

raylib:
	cd deps/raylib/src && make PLATFORM=PLATFORM_DESKTOP

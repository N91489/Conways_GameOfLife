CC := gcc

ifeq ($(shell command -v gcc >/dev/null 2>&1 && echo gcc), gcc)
	CC := gcc
else ifeq ($(shell command -v clang >/dev/null 2>&1 && echo clang), clang)
	CC := clang
else ifeq ($(shell command -v i686-w64-mingw32-gcc >/dev/null 2>&1 && echo i686-w64-mingw32-gcc), i686-w64-mingw32-gcc)
	CC := i686-w64-mingw32-gcc
else ifeq ($(shell command -v x86_64-w64-mingw32-gcc >/dev/null 2>&1 && echo x86_64-w64-mingw32-gcc), x86_64-w64-mingw32-gcc)
	CC := x86_64-w64-mingw32-gcc
else ifeq ($(shell command -v cygwin >/dev/null 2>&1 && echo cygwin), cygwin)
	CC := cygwin
endif

CFLAGS = -Iinclude
LDFLAGS = -Llib
LDLIBS = -lSDL2-2.0.0

build: Conways_GameOfLife.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o CGoL Conways_GameOfLife.c $(LDLIBS)
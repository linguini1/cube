CC = gcc
OUT = cube

### COMPILER OPTIONS ###
OPTIMIZATION = -O3

### WARNINGS ###
# (see https://gcc.gnu.org/onlinedocs/gcc-6.3.0/gcc/Warning-Options.html)
WARNINGS += -Wall -Wextra -Wshadow -Wundef -Wformat=2 -Wtrampolines -Wfloat-equal
WARNINGS += -Wbad-function-cast -Wstrict-prototypes -Wpacked
WARNINGS += -Wno-aggressive-loop-optimizations -Wmissing-prototypes -Winit-self
WARNINGS += -Wmissing-declarations -Wmissing-format-attribute -Wunreachable-code
WARNINGS += -Wshift-overflow=2 -Wduplicated-cond -Wpointer-arith -Wwrite-strings
WARNINGS += -Wnested-externs -Wcast-align -Wredundant-decls
WARNINGS += -Werror=implicit-function-declaration -Wlogical-not-parentheses
WARNINGS += -Wlogical-op -Wold-style-definition -Wcast-qual -Wdouble-promotion
WARNINGS += -Wmissing-include-dirs -Wnormalized
WARNINGS += -Wdisabled-optimization -Wsuggest-attribute=const

### COMPILER FLAGS ###
CFLAGS += $(OPTIMIZATION)

ifeq ($(OS),Windows_NT)

# Windows SDL locations
SDL_INC = C:/mingw64/SDL2-2.28.5/x86_64-w64-mingw32/include
SDL_LINK = C:/mingw64/SDL2-2.28.5/x86_64-w64-mingw32/lib

CFLAGS += -Dmain=SDL_main
CFLAGS += -I$(SDL_INC)
CFLAGS += -L$(SDL_LINK)
LINK_FLAGS = -lmingw32 -lSDL2main -lSDL2 -mwindows
else
CFLAGS += $(shell sdl2-config --cflags --libs)
LINK_FLAGS = -lSDL2_ttf -lm
endif

### SOURCE FILES ###
SRCDIR = src
SRC_FILES = $(wildcard $(SRCDIR)/*.c)
OBJ_FILES = $(patsubst %.c,%.o,$(SRC_FILES))

%.o: %.c
	$(CC) $(CFLAGS) $(WARNINGS) -o $@ -c $<

all: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LINK_FLAGS) -o $(OUT)

clean:
	@rm $(OBJ_FILES)
	@rm $(OUT)

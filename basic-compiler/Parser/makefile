CC = gcc
CFLAGS += -g -Wall -Wno-unused-variable -std=c99 -pedantic -pedantic-errors -Werror -g0 -Os \
    -fno-strict-overflow -fno-strict-aliasing \
    -Wall -Wextra \
    -pthread \
    -Wno-unused-label \
    -Wno-unused-function \
    -Wno-unused-parameter \
    -Wno-unused-variable

CPPFLAGS = -I./
LDFLAGS = -L.
LDLIBS = 
LFLAGS = -d
C_SOURCE += $(./*.c)
OBJS = $(C_SOURCE:.c=.o)
INCS=-I.  #头文件的路径
LIBS=

.PHONY: all

all: $(BIN)

$(BIN) : $(OBJS)
	$(CC) -o $(BIN) $(OBJS) $(LIBS) $(CFLAGS)

$(OBJS) : %.o: %.c
	$(CC) -c $< -o $@ $(INCS) $(CFLAGS)

# objects := $(patsubst %.c,%.o,$(wildcard *.c))
# 列出文件夹中所有的.c文件
# objects := $(wildcard *.c)

# main: $(objects)
#     $(CC) -o main $(objects) $(LIBS) $(CFLAGS)
objs=EliminateLeftRecursion.o Common.o
main: $(objs)
	gcc -o main.exe $(objs) $(LIBS) $(CFLAGS)

EliminateLeftRecursion.o: EliminateLeftRecursion.c EliminateLeftRecursion.h Common.h
	$(CC) -o EliminateLeftRecursion.o -c EliminateLeftRecursion.c $(LIBS) $(CFLAGS)

Common.o:Common.c Common.h
	$(CC) -o Common.o -c Common.c $(LIBS) $(CFLAGS)

clean:
	rm -rf ./*.o main.exe



CC = gcc
CFLAGS += -g -Wall -Wno-unused-variable -std=c99 -pedantic -pedantic-errors -Werror -g0 -Os \
    -fno-strict-overflow -fno-strict-aliasing \
    -Wall -Wextra \
    -pthread \
    -Wno-unused-label \
    -Wno-unused-function \
    -Wno-unused-parameter \
    -Wno-unused-variable
CPPFLAGS = -I.
LDFLAGS = -L.
LDLIBS = 
LFLAGS = -d
C_SOURCE += $(./*.c)
OBJS = $(C_SOURCE:.c=.o)
INCS=-I.  #头文件的路径
LIBS=

$(OBJS) : %.o: %.c
	$(CC) -c $< -o $@ $(INCS) $(CFLAGS)

$(BIN):$(OBJS)
	$(CC) -o $(BIN) $(OBJS) $(LIBS) $(CFLAGS)

all:$(BIN)


clean:
	rm -rf ./*.o main.exe

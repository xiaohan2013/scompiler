## 编译
```sh
# Generator = make
cmake .. -B build
cmake --build build
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build --trace-source=CMakeLists.txt && cd build && make
rm -rf build && cmake -D CMAKE_BUILD_TYPE=Debug -S . -B build --trace-source=CMakeLists.txt && cd build && make && cd ../ && ./build/NFA2DFA/nfa_2_dfa.exe 
# Generator = Ninja
```


## 问题
1. CMake Error: CMake was unable to find a build program corresponding to "Unix Makefiles".  CMAKE_MAKE_PROGRAM is not set.  You probably need to select a different build tool.
    - 安装 make, pacman -S make



## GCC
```sh

# 加入调试信息
gcc -g -Wall RegexpToPost.c -o RegexpToPost

gdb RegexpToPost.exe
tui enable
b 36
print 
p *pointer@10


```

### makefile
通过 foreach 和 patsubst 方法和 @、^、$< 变量来构建遍历的编译
- $@ --代表目标文件(target)
- $^ --代表所有的依赖文件(components)
- $< --代表第一个依赖文件(components中最左边的那个)。
- @ 这个符串通常用在“规则”行中，表示不显示命令本身，而只显示它的结果，例如Makefile中的内容为：
```makefile
DIR_OBJ=./obj
CMD_MKOBJDIR=if [ -d ${DIR_OBJ} ]; then exit 0; else mkdir ${DIR_OBJ}; fi

mkobjdir:
    @${CMD_MKOBJDIR}
```


```makefile
CROSS =   
CC = $(CROSS)gcc  
CXX = $(CROSS)g++  
DEBUG = -g
CFLAGS = $(DEBUG) -Wall -c -fPIC
MV = mv -f
RM = rm -rf  
LN = ln -sf  

TARGET = libhello.so 

TOP_PATH = $(shell pwd)
INC_PATH = $(TOP_PATH)/include
SRC_PATH = $(TOP_PATH)
SRC_PATH += $(TOP_PATH)/src
MOD_PATH = $(TOP_PATH)/modules
MOD_LIB_PATH = $(MOD_PATH)/lib
MOD_INC_PATH = $(MOD_PATH)/include
DIRS = $(shell find $(SRC_PATH) -maxdepth 3 -type d)
FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))

##########################################################  
# modules  
##########################################################  
modules =
MODULES_PATH = $(foreach m, $(modules), $(MOD_PATH)/$(m))  

##########################################################  
# srcs  
##########################################################  
SRCS_CPP += $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))  
SRCS_CC += $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cc))  
SRCS_C += $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))  

##########################################################  
# objs  
##########################################################  
OBJS_CPP = $(patsubst %.cpp, %.o, $(SRCS_CPP))  
OBJS_CC = $(patsubst %.cc, %.o, $(SRCS_CC))  
OBJS_C = $(patsubst %.c, %.o, $(SRCS_C))  

##########################################################  
# paths
##########################################################  
INC_PATH += -I$(MOD_INC_PATH)  
INC_PATH += -I$(MOD_PATH)  
LIB_PATH += -L$(TOP_PATH)/lib  
LIB_PATH += -L$(MOD_LIB_PATH)  

##########################################################  
# libs
##########################################################  

##########################################################  
# building
##########################################################  
all:$(TARGET)

$(TARGET) : $(OBJS_CPP) $(OBJS_CC) $(OBJS_C)  
    @ for i in $(MODULES_PATH); \  
    do \  
    make -C $$i; \  
    done  

    @ $(CXX) $^ -o $@ $(LIB_PATH) $(LIBS)  
    @ echo Create $(TARGET) ok...  

$(OBJS_CPP):%.o : %.cpp
    $(CXX) $(CFLAGS) $< -o $@ $(INC_PATH)

$(OBJS_CC):%.o : %.cc
    $(CXX) $(CFLAGS) $< -o $@ $(INC_PATH)

$(OBJS_C):%.o : %.c
    $(CXX) $(CFLAGS) $< -o $@ $(INC_PATH)

$(OBJS_C):%.o : %.c
    $(CC) $(CFLAGS) $< -o $@ $(INC_PATH)

.PHONY : clean  
clean:  
    @ $(RM) $(TARGET) $(OBJS_C)  

```
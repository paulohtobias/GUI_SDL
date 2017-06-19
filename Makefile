#Main Makefile
CC = gcc
CFLAGS = -g -Wall -MMD

DLL= #-lm -fPIC

#Binary
ifeq ($(OS),Windows_NT)
    BIN = main.exe
else
	BIN = main
endif

#Directories
IDIR = ./include
SDIR = ./src

#Paths
INCLUDE_PATHS = -I/usr/local/include -I$(IDIR)
LIBRARY_PATHS = -L/usr/local/lib

ifeq ($(OS),Windows_NT)
    LIBRARIES = -lmingw32
	ODIR = ./obj/windows
	CFLAGS+= -mno-ms-bitfields
else
	ODIR = ./obj/linux
endif

#Libraries
LIBRARIES+= -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

#Compilation line
COMPILE = $(CC) $(CFLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS)

#FILEs
#---------------Include---------------#
INCS = $(wildcard $(IDIR)/*.h) $(wildcard $(IDIR)/*/*.h)

#---------------Source----------------#
SRCS = $(wildcard $(SDIR)/*.c) $(wildcard $(SDIR)/*/*.c)

#---------------Object----------------#
OBJS = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.o)
#-------------Dependency--------------#
DEPS = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.d)

all: $(OBJS)
	$(COMPILE) $(OBJS) main.c -o $(BIN) $(LIBRARIES)

dll: $(OBJS)
	$(COMPILE) -shared -o libguisdl.so $(OBJS) $(LIBRARIES) $(DLL)

# Include all .d files
-include $(DEPS)

$(ODIR)/%.o: $(SDIR)/%.c
	$(COMPILE) -MMD -c $< -o $@ $(LIBRARIES) $(DLL)

.PHONY : clean
clean :
	-rm $(BIN) $(OBJS) $(DEPS)

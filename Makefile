# Define the C++ compiler
# CXX := clang++
CXX := g++

# Define any compile-time flags
# CXXFLAGS := --debug 
CXXFLAGS := -g 

# Define any directories containing header files other than /usr/include
INCLUDES := -I./cudoko-proj/models -I./cudoko-proj/lib -I./cudoko-proj

# Define library paths in addition to /usr/lib
LFLAGS :=

# Define any libraries to link into executable
LIBS :=

# Define the C++ source files
SRCS := cudoko-proj/main.cpp cudoko-proj/models/data.cpp cudoko-proj/lib/path.cpp cudoko-proj/cudoko.cpp cudoko-proj/lib/wordIterate.cpp cudoko-proj/lib/board.cpp cudoko-proj/lib/trajectory.cpp cudoko-proj/lib/grid.cpp

# Define the C++ object files
OBJS := $(SRCS:.cpp=.o)

# Define the executable file
MAIN := cudoko

.PHONY: clean

all:    $(MAIN)
		@echo  Compiling has been completed!

$(MAIN): $(OBJS)
		$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
		$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

clean:
		$(RM) $(OBJS) *~ $(MAIN)


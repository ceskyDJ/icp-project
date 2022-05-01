# Makefile
#
# ICP project (Class and sequence diagram editor)
#
# Author: Michal Šmahel (xsmahe01)
# Help: https://devhints.io/makefile
# Inspired by: https://www.throwtheswitch.org/build/make

# Usage:
# make          ... build main binary
# make run      ... runs the built binary
# make pack     ... create final archive
# make doxygen  ... generate Doxygen docs
# make clean    ... remove temporary files

# Used magic variables:
# $< ... first dependency
# $@ ... target

BINARY_NAME=icp_project
ARCHIVE_NAME=xsmahe01-xdvora3q

# Project sources
SRC_P=src
# Directories with build data
BIN_P=build/bin
DEP_P=build/deps
OBJ_P=build/objs

# Compiler configs
CC=g++
CFLAGS=-std=c++17 -g -pedantic -Wall -Wextra -Werror

# Get a list of all source files (ex.: SRC_P/main.cpp SRC_P/file_1.cpp)
SRC_FILES=$(wildcard $(SRC_P)/*.cpp)
# Get a list of all header files (ex.: SRC_P/file_1.h SRC_P/file_2.h)
HDR_FILES=$(wildcard $(SRC_P)/*.h)
# Transform the list of source files into a list of modules
# It's done by substitution - every *.cpp file creates one object one (*.o),
# so we can just change extension and path and we're done
MODULES=$(patsubst %.cpp, %.o, $(SRC_FILES))

# Define virtual files
.PHONY: all run pack doxygen clean cleanall

# `make` only compiles main binary
all: $(BIN_P)/$(BINARY_NAME)

# Template for compiling modules
# This is used for generated rules in dep-*.list
$(OBJ_P)/%.o: $(SRC_P)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link modules into final binary
$(BIN_P)/$(BINARY_NAME): $(DEP_P)/dep-src.list $(MODULES)
	$(CC) $(CFLAGS) $(MODULES) -o $@

#######################################
# Generate module dependencies
$(DEP_P)/dep-src.list: $(SRC_FILES) $(HDR_FILES)
	$(SRC_P)/get-dependency-list.sh $(SRC_P) $(OBJ_P) >$@

-include $(DEP_P)/dep-src.list
#######################################

# Create final archive
pack:
	tar -czvf $(ARCHIVE_NAME).tar.gz src/* examples/* README.txt Makefile

# Cleaning stuff
clean:
	rm -f $(OBJ_P)/* $(BIN_P)/* $(DEP_P)/* $(ARCHIVE_NAME).tar.gz

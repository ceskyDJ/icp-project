# Makefile
#
# ICP project (Class and sequence diagram editor)
#
# Author: Michal Šmahel (xsmahe01)
# Help: https://devhints.io/makefile

# Usage:
# make          ... build main binary
# make run      ... runs the built binary
# make pack     ... create final archive
# make doxygen  ... generate Doxygen docs
# make clean    ... remove temporary files

# Windows compatibility
# You need these EXE files in PATH:
# - qmake.exe
# - doxygen.exe

# Important constants
ifeq ($(OS),Windows_NT)
	BINARY_NAME=icp_project.exe
else
	BINARY_NAME=icp_project
endif
ARCHIVE_NAME=xsmahe01-xdvora3q

# Tools
ifeq ($(OS),Windows_NT)
	QMAKE=qmake.exe
else
	QMAKE=qmake
endif

ifeq ($(OS),Windows_NT)
	DOXYGEN=dogygen.exe
else
	DOXYGEN=doxygen
endif

# Define virtual files
.PHONY: all compile run pack doxygen clean cleanall

# `make` only compiles main binary
all: compile

# Compilation using qmake
compile:
	cd src && $(QMAKE) -makefile
	cd src && $(MAKE)

# Run built program
run: compile
	./build/bin/$(BINARY_NAME)

# Create final archive
pack:
	tar -czvf $(ARCHIVE_NAME).tar.gz $(shell ls src/*.cpp src/*.h src/*.pro examples/* README.txt Makefile 2>/dev/null)

# Generate Doxygen documentation
doxygen:
	$(DOXYGEN)

# Cleaning stuff
clean:
ifeq ($(OS),Windows_NT)
	-exist src\Makefile && cd src && $(MAKE) clean
else
	-[ -f src/Makefile ] && cd src && $(MAKE) clean
endif
	rm -rf $(ARCHIVE_NAME).tar.gz doc

cleanall: clean
	rm -rf src/Makefile src/.qmake.stash build/*

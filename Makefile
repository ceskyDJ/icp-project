# Makefile
#
# ICP project (Class and sequence diagram editor)
#
# Author: Michal Šmahel (xsmahe01)
# Help: https://devhints.io/makefile

# Usage:
# make          ... build main binary
# make run      ... runs the built binary
# make pack     ... create final archive (for Unix-like OS only)
# make doxygen  ... generate Doxygen docs
# make clean    ... remove temporary files

# Windows compatibility
# You need these EXE files in PATH (in brackets are example directories
# where could be needed binaries):
# - make.exe (C:\Program Files (x86)\GnuWin32\bin)
# - qmake.exe (C:\Qt\5.15.2\mingw81_64\bin)
# - g++.exe (C:\Qt\Tools\mingw810_64\bin)
# - doxygen.exe (C:\Program Files\doxygen\bin)

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
	DOXYGEN=doxygen.exe
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
	tar -czvf $(ARCHIVE_NAME).tar.gz $(shell ls src/*.cpp src/*.h src/*.pro examples/* resources/* README.txt Makefile Doxyfile rsc.qrc 2>/dev/null)

# Generate Doxygen documentation
doxygen:
	$(DOXYGEN)

# Cleaning stuff
clean:
ifeq ($(OS),Windows_NT)
	-if exist src\Makefile cd src && $(MAKE) clean
	-del /f "$(ARCHIVE_NAME).tar.gz"
	-rmdir /S /Q doc
else
	-[ -f src/Makefile ] && cd src && $(MAKE) clean
	rm -rf $(ARCHIVE_NAME).tar.gz doc
endif

cleanall: clean
ifeq ($(OS),Windows_NT)
	-del /f "src\Makefile"
	-del /f "src\Makefile.Debug"
	-del /f "src\Makefile.Release"
	-del /f "src\.qmake.stash"
	-rd /s /q build && mkdir build
else
	rm -rf src/Makefile src/.qmake.stash build/*
endif

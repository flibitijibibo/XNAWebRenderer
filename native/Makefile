# Makefile for XNAFileDialog
# Written by Ethan "flibitijibibo" Lee

# System information
UNAME = $(shell uname)
ARCH = $(shell uname -m)

# CEF Junk
CEF = cef_binary_3.2526.1332.gf7d9457_linux64
CEFCMD = \
	-I./$(CEF) \
	$(CEF)/flibitBuild/libcef_dll/libcef_dll_wrapper.a \
	$(CEF)/Release/libcef.$(TARGET)

# Compiler
ifeq ($(UNAME), Darwin)
	CXX = clang++ -mmacosx-version-min=10.6
	TARGET = dylib
	SUFFIX = osx
else
	CXX = g++
	TARGET = so
	ifeq ($(ARCH), x86_64)
		SUFFIX = x86_64
	else
		SUFFIX = x86
	endif
endif

all: clean
	$(CXX) -g -fpic -fPIC -shared -o libXNAWebRenderer.$(TARGET) *.cpp $(CEFCMD)
	$(CXX) -g -o cefprocess.bin.$(SUFFIX) cefprocess.cpp $(CEFCMD)

clean:
	rm -f libXNAFileDialog.$(TARGET) cefprocess.bin.$(SUFFIX)

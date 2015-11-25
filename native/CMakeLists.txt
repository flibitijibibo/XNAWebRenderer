# CMake File for XNAFileDialog
# Written by Ethan "flibitijibibo" Lee

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(XNAWebRenderer)

# OS Flags
IF(WIN32)
	# Nothing...?
ELSEIF(APPLE)
	SET(CMAKE_OSX_DEPLOYMENT_TARGET 10.6)
	SET(CMAKE_EXECUTABLE_SUFFIX ".bin.osx")
ELSEIF(CMAKE_SIZEOF_VOID_P MATCHES "8")
	SET(CMAKE_EXECUTABLE_SUFFIX ".bin.x86_64")
ELSE()
	SET(CMAKE_EXECUTABLE_SUFFIX ".bin.x86")
ENDIF()

# Chromium Directories/Files
SET(CEFFOLDER "${CMAKE_SOURCE_DIR}/cef_binary_3.2526.1332.gf7d9457_linux64")
SET(CEFWRAP "${CEFFOLDER}/flibitBuild/libcef_dll/libcef_dll_wrapper.a")
INCLUDE_DIRECTORIES(${CEFFOLDER})
LINK_DIRECTORIES("${CEFFOLDER}/Release")

# XNAWebRenderer.dll
ADD_LIBRARY(XNAWebRenderer SHARED "XNAWebRenderer.cpp")
TARGET_LINK_LIBRARIES(XNAWebRenderer ${CEFWRAP} cef)

# cefprocess.exe
ADD_EXECUTABLE(cefprocess "cefprocess.cpp")
TARGET_LINK_LIBRARIES(cefprocess ${CEFWRAP} cef)

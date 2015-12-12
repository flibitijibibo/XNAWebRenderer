# CMake File for XNAFileDialog
# Written by Ethan "flibitijibibo" Lee

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(XNAWebRenderer)

# OS Flags
IF(WIN32)
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	SET(CEFLIB "libcef")
ELSEIF(APPLE)
	SET(CMAKE_OSX_DEPLOYMENT_TARGET 10.6)
	SET(CMAKE_EXECUTABLE_SUFFIX ".bin.osx")
	SET(CEFLIB "cef") # TODO: CEF OSX name!
	# install_name_tool -change
	# "@executable_path/Chromium Embedded Framework"
	# "@executable_path/../Frameworks/Chromium Embedded Framework.framework/Chromium Embedded Framework"
	# libXNAWebRenderer.dylib
ELSEIF(CMAKE_SIZEOF_VOID_P MATCHES "8")
	SET(CMAKE_EXECUTABLE_SUFFIX ".bin.x86_64")
	SET(CEFLIB "cef")
ELSE()
	SET(CMAKE_EXECUTABLE_SUFFIX ".bin.x86")
	SET(CEFLIB "cef")
ENDIF()

# Chromium Directories/Files
SET(CEFFOLDER "${CMAKE_SOURCE_DIR}/cef_binary_3.2526.1361.g456ea5a_linux64")
SET(CEFWRAP "${CEFFOLDER}/flibitBuild/libcef_dll/libcef_dll_wrapper.a")
INCLUDE_DIRECTORIES(${CEFFOLDER})
LINK_DIRECTORIES("${CEFFOLDER}/Release")

# XNAWebRenderer.dll
ADD_LIBRARY(XNAWebRenderer SHARED "XNAWebRenderer.cpp")
TARGET_LINK_LIBRARIES(XNAWebRenderer ${CEFWRAP} ${CEFLIB})

# cefprocess.exe
IF(NOT APPLE)
	ADD_EXECUTABLE(cefprocess "cefprocess.cpp")
	TARGET_LINK_LIBRARIES(cefprocess ${CEFWRAP} ${CEFLIB})
ENDIF()

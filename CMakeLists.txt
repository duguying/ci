project(ojserver)

############################################################
# Debug support
set(CMAKE_BUILD_TYPE "Debug")
add_definitions("-D_CRT_SECURE_NO_DEPRECATE")
add_definitions("-wd4819")
# root directory
set(SRC_DIR "src/")
set(TEST_DIR "tests/")
set(DEP "deps/")
# output directory
set(EXECUTABLE_OUTPUT_PATH bin)

include_directories("src/include")
include_directories("src")
include_directories("deps")

#############################################################

set(
	CORE_LIST 
	${SRC_DIR}/ojcore.cc
	${SRC_DIR}/websocket/thread.cc
	${SRC_DIR}/websocket/socket.cc
	${SRC_DIR}/websocket/websocket.cc
	${DEP}/base64/base64.cc
	${DEP}/sha1/sha1.cc
	${SRC_DIR}/websocket/encrypt.cc
	${DEP}/regex++/regex.cc
	${DEP}/regex++/regexstate.cc
	${DEP}/fork/fork_windows.c
	${SRC_DIR}/executer/exec.cc
)

add_executable(ojs ${CORE_LIST})

if(WIN32)
	target_link_libraries(ojs ws2_32)
else(UNIX)
endif(WIN32)







cmake_minimum_required(VERSION 2.8)

project(ojserver)

############################################################
# Debug support
set(TEST true)
set(CMAKE_BUILD_TYPE "Release")
add_definitions(
	"-D_CRT_SECURE_NO_DEPRECATE"
	"-wd4819"
)

# root directory
set(SRC_DIR "src/")
set(TEST_DIR "tests/")
set(DEP "deps/")

# output directory
set(EXECUTABLE_OUTPUT_PATH bin)

include_directories("src/include")
include_directories("src")
include_directories("deps")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/pcre")

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
	${SRC_DIR}/utils/pcre.cc
	${SRC_DIR}/websocket/process.cc
	${SRC_DIR}/executer/exec.cc
)

add_executable(ojs ${CORE_LIST})

if(WIN32)
	target_link_libraries(ojs ws2_32 pcred)
else(UNIX)
endif(WIN32)



if(TEST)
	ENABLE_TESTING()
	include(tests/CMakeLists.txt)
endif(TEST)

cmake_minimum_required(VERSION 2.8)

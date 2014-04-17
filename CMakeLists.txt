project(ojserver)

############################################################
# Debug support
add_definitions("-D_CRT_SECURE_NO_DEPRECATE")
add_definitions("-wd4819")
# root directory
set(SRC_DIR "src/")
set(TEST_DIR "tests/")
set(DEP "deps/")
set(TOOLS "${CMAKE_CURRENT_SOURCE_DIR}/tools/")
if(WIN32)
	set(WGET ${TOOLS}wget.exe)
	set(UNZIP ${TOOLS}unzip.exe)
else(UNIX)
	set(WGET wget)
	set(UNZIP unzip)
endif(WIN32)
# output directory
set(EXECUTABLE_OUTPUT_PATH bin)

include_directories("src/include")
include_directories("src")
include_directories("deps")
include_directories("C:/Program Files (x86)/PCRE/include")

link_directories("C:/Program Files (x86)/PCRE/lib")
link_directories(${PCRE_PATH})

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

#
include(deps/CMakeLists.txt)
#

set(
	PCRE_TEST 
	${TEST_DIR}/pcre.cc
	${SRC_DIR}/utils/pcre.cc
)
add_executable(test_pcre ${PCRE_TEST})
target_link_libraries(test_pcre pcred)




cmake_minimum_required(VERSION 2.8)

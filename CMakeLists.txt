project(ojserver)

if(UNIX)
	set(PLTF " Unix  ")
	set(TGPF " Unix  ")
elseif(WIN32)
	set(PLTF "Windows")
	set(TGPF "Windows")
elseif(APPLE)
	set(PLTF " MacOS ")
	set(TGPF " MacOS ")
endif(UNIX)

############################################################
# gdb Debug support
set(TEST true)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_C_FLAGS "-std=c99")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -ggdb")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -s -DNDEBUG")

# root directory
set(SRC_DIR "src/")
set(TEST_DIR "tests/")
# output directory
set(EXECUTABLE_OUTPUT_PATH bin)

include_directories("src/include")
include_directories("src")

#############################################################
if(WIN32)
	set(
		CORE_LIST 
		${SRC_DIR}/ojcore.cc
		${SRC_DIR}/executer/exec.cc
		${SRC_DIR}/server/serv_win.cc
		${SRC_DIR}/websocket/socket.cc
		${SRC_DIR}/websocket/websocket.cc
	)

else(UNIX)
	set(
		CORE_LIST 
		${SRC_DIR}/ojcore.cc
		${SRC_DIR}/executer/exec.cc
		${SRC_DIR}/server/serv_unix.cc
		${SRC_DIR}/websocket/socket.cc
		${SRC_DIR}/websocket/websocket.cc
	)
endif(WIN32)


add_executable(ojcore ${CORE_LIST})

if(WIN32)
	target_link_libraries(ojcore ws2_32)
else(UNIX)
endif(WIN32)

##########################################################################

ENABLE_TESTING()

set(
	T_SOCKET_LIST
	${TEST_DIR}/socket.cc
	${SRC_DIR}/websocket/socket.cc
)

add_executable(test_socket ${T_SOCKET_LIST})

if(WIN32)
	target_link_libraries(test_socket ws2_32)
else(UNIX)
endif(WIN32)

ADD_TEST(T_CONF "./bin/test_socket")





cmake_minimum_required(VERSION 2.8)

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

set(
	CORE_LIST 
	${SRC_DIR}/ojserver.cc
	${SRC_DIR}/exec.cc
)

add_executable(ojcore ${CORE_LIST})




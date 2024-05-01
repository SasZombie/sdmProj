cmake_minimum_required(VERSION 3.10)

project(EHR)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



set(SOURCE_DIR "source")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith -Wmissing-declarations -Winline -Wundef -Wcast-qual -Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal -pedantic -ansi -fsanitize=address -fsanitize=leak")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)


file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cpp")
# message(STATUS "SOURCE FILES: ${SOURCE_FILES}")

add_executable(main main.cpp ${SOURCE_FILES})
# target_link_libraries(main raylib GL m pthread dl rt X11)

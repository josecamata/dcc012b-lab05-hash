
cmake_minimum_required(VERSION 3.14)
project(dcc012-lab4-heap)

option(CLASSROOM "Enable classroom build" OFF)
option(CPU_TIME  "Enable cputime build" ON)

set(INPUT_DIR "${PROJECT_SOURCE_DIR}/input/")
set(EXPECTED_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/tests/expected_output/")

configure_file(${PROJECT_SOURCE_DIR}/siga/config.h.in ${PROJECT_SOURCE_DIR}/siga/include/config.h) 
include_directories(${PROJECT_SOURCE_DIR}/siga/include)


add_subdirectory(siga)

enable_testing()
add_subdirectory(tests)








    
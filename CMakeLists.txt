cmake_minimum_required(VERSION 3.22)
project(isa LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(isa_core
  src/cpu.cpp
  src/decode.cpp
  src/disasm.cpp
)
target_include_directories(isa_core PUBLIC include)

add_executable(isa_cli app/main.cpp)
target_link_libraries(isa_cli PRIVATE isa_core)

# Warnings (good default)
if (MSVC)
  target_compile_options(isa_core PRIVATE /W4 /permissive-)
else()
  target_compile_options(isa_core PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()

enable_testing()
add_subdirectory(tests)
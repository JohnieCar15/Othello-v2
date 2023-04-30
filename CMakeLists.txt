cmake_minimum_required(VERSION 3.0.0)
project(Othello-v2 VERSION 0.1.0)

# we use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# helpful compiler flags for gcc/clang
add_compile_options(
  -Wall
  -Wextra
  -Werror
  -pedantic-errors
  -Wconversion
  -Wsign-conversion
  -Wdouble-promotion
  -Wcast-align
  -Wformat=2
  -Wuninitialized
  -Wnull-dereference
  -Wnon-virtual-dtor
  -Woverloaded-virtual
  -Wdeprecated-copy-dtor
  -Wold-style-cast
  #-Wzero-as-null-pointer-constant
  -Wno-self-assign-overloaded
  -Wno-self-move
  -Wsuggest-override
  -fstack-protector-strong
)

# debug builds should be compiled with sanitizers
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_EXE_LINKER_FLAGS_DEBUG_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_EXE_LINKER_FLAGS_RELWITHDEBINFO_INIT "-fsanitize=address,undefined")


# include(CTest)
# enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(SDL2 REQUIRED)
include_directories(Othello-v2 ${SDL2_INCLUDE_DIRS})
include_directories(Othello-v2 images)

add_library(othello src/othello.cpp)
link_libraries(othello)

add_executable(Othello-v2 src/main.cpp)
target_link_libraries(Othello-v2 ${SDL2_LIBRARIES})


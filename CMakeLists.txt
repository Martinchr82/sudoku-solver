cmake_minimum_required (VERSION 2.6)

# Maps to Visual Studio solution file (Tutorial.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
project (sudoku-solver)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
if(MSVC)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else(MSVC)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif(MSVC)

# Command to output information to the console
# Useful for displaying errors, warnings, and debugging
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

set(LIB_SRCS
SudokuBoard.cxx
SudokuSolverBF.cxx
)

set(LIB_HEADERS
SudokuBoard.h
SudokuSolverBF.h
)

add_library(SudokuSolver ${LIB_SRCS} ${LIB_HEADERS})

set(BENCHMARK_SRC
SudokuSolverBenchmark.cxx
)

add_executable (SudokuSolverBenchmark ${BENCHMARK_SRC})

target_link_libraries (SudokuSolverBenchmark SudokuSolver)
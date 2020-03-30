cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(validator VERSION 0.1 LANGUAGES CXX)
include(cmake/StandardProjectSettings.cmake)

add_library(project_options INTERFACE)

# CMake uses c++2a even if compiler supports c++20
# target_compile_features(project_options INTERFACE cxx_std_20)
target_compile_options(project_options INTERFACE -std=c++20)

add_library(project_warnings INTERFACE)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/Doxygen.cmake)
enable_doxygen()

include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)

option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
  target_precompile_headers(project_options INTERFACE <vector> <string> <map> <utility>)
endif()

set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

# if(CPP_STARTER_USE_SDL)
#   set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES}
#                            sdl2/2.0.10@bincrafters/stable)
#   # set(CONAN_EXTRA_OPTIONS ${CONAN_EXTRA_OPTIONS} sdl2:wayland=True)
# endif()

include(cmake/Conan.cmake)
run_conan()

if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

if(ENABLE_FUZZING)
  add_subdirectory(fuzz_test)
endif()

include(ExternalProject)
add_subdirectory(src)

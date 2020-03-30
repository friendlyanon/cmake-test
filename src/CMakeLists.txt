file(GLOB_RECURSE sources
  LIST_DIRECTORIES false CONFIGURE_DEPENDS
  *.cpp *.hpp)

download_project(
  PROJ libdawjsonlink
  PREFIX "${PROJECT_SOURCE_DIR}/third_party"
  GIT_REPOSITORY https://github.com/beached/daw_json_link.git
  GIT_TAG v1.1.0
  UPDATE_DISCONNECTED 1)

add_subdirectory(${libdawjsonlink_SOURCE_DIR} ${libdawjsonlink_BINARY_DIR})

add_executable(validator ${sources})
target_link_libraries(validator
  PRIVATE
    project_options project_warnings
    CONAN_PKG::docopt.cpp CONAN_PKG::fmt CONAN_PKG::spdlog
    daw_json_link_prj)

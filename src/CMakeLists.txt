file(GLOB_RECURSE sources
  LIST_DIRECTORIES false CONFIGURE_DEPENDS
  *.cpp *.hpp)

set(THIRD_PARTY_DIR "${PROJECT_SOURCE_DIR}/third_party")

set(DAW_JSON_ALL_DIR "${THIRD_PARTY_DIR}/daw_json_link_all")
if(NOT EXISTS "${DAW_JSON_ALL_DIR}")
  foreach(repo daw_json_link header_libraries utf_range)
    message(STATUS "Fetching ${repo}")
    execute_process(
      COMMAND git clone --depth 1 "https://github.com/beached/${repo}.git" "${DAW_JSON_ALL_DIR}/${repo}"
      OUTPUT_QUIET)
  endforeach()
endif()

option(DAW_ALLOW_SSE3 "Enable SSE3 for daw_json_link" ON)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    project_options project_warnings
    CONAN_PKG::docopt.cpp CONAN_PKG::fmt CONAN_PKG::spdlog)

target_include_directories(${PROJECT_NAME} SYSTEM
  PRIVATE
    "${DAW_JSON_ALL_DIR}/daw_json_link/include"
    "${DAW_JSON_ALL_DIR}/header_libraries/include"
    "${DAW_JSON_ALL_DIR}/utf_range/include")
